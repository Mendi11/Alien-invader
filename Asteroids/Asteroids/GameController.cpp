#include "GameController.h"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include <vector>
#include "Character.h"
#include "Player.h"
#include "Bullets.h"

GameController::GameController() :// Initialize Variabels
	m_Window(sf::VideoMode(600, 900), "My window"),
	m_Delay(0), m_ESpawn(2), m_Score(0), m_Health(10), m_BulletDelay(3),
	m_SpawnEnemie(true)
{

	// Load font
	if (!m_Font.loadFromFile("fonts/kenvector_future_thin.ttf"))
	{
		//Error 
	}
	// Setting up the text appearance
	m_Text.setFont(m_Font);
	m_Text.setColor(sf::Color::White);
	m_Text.setPosition(400, 15);
	m_TextHP.setFont(m_Font);
	m_TextHP.setColor(sf::Color::White);
	m_TextHP.setPosition(100, 15);

	// gamover Text
	m_TGameOver.setScale(2, 2);
	m_TGameOver.setPosition(150, 400);
	m_TGameOver.setFont(m_Font);


	//Load Texture for sprites
	if (!m_Background.loadFromFile("Sprites/background.png"))
	{
	}
	if (!m_PlayerTexture.loadFromFile("Sprites/player.png"))
	{
		//Error
	}
	if (!m_EnemyTexture.loadFromFile("Sprites/enemy.png"))
	{
		//Error
	}
	if (!m_BulletTexture.loadFromFile("Sprites/bullet_player.png"))
	{
		//Error
	}
	if (!m_HealtShip.loadFromFile("Sprites/player_life.png"))
	{
		//Error
	}
	if (!m_EBulletTexture.loadFromFile("Sprites/bullet_enemy.png"))
	{
		//Error
	}
	if (!m_HealthX.loadFromFile("Sprites/numeralX.png"))
	{
		//Error
	}

	// Initialize vectors
	m_Player = new Player(m_PlayerTexture);
	m_Enemie = new Enemie(m_EnemyTexture);
	m_Bullet = new Bullets(m_BulletTexture, 0, 0);
	m_Ebullet = new EBullets(m_EBulletTexture, 0, 0);
	
	
	// Create the player.
	m_Characters.push_back(m_Player);

	m_HealthSprite.setTexture(m_HealtShip);
	m_HealthSprite.setPosition(30, 20);
	m_HealthXSprite.setTexture(m_HealthX);
	m_HealthXSprite.setPosition(70, 30);

	m_Background.setRepeated(true);

	m_BackgroundSprite0.setTexture(m_Background);
	m_BackgroundSprite0.setTextureRect({ 0, 0, 600, 900
	});


}


GameController::~GameController()
{
	m_Enemie = nullptr;
	delete m_Enemie;
	m_Player = nullptr;
	delete m_Player;
	m_Ebullet = nullptr;
	delete m_Ebullet;
	m_Bullet = nullptr;
	delete m_Bullet;

}

void GameController::Run()
{
	while (m_Window.isOpen())
	{
		sf::Event event;
		while (m_Window.pollEvent(event))
		{

			// "close requested" event: we close the window
			if (event.type == sf::Event::Closed)
				m_Window.close();
		}

		Update();
		Draw();
		//Dealtatime and Countdown for different dealyes
		m_Delay -= m_Dt.asSeconds();
		m_BulletDelay -= m_Dt.asSeconds();
		m_ESpawn -= m_Dt.asSeconds();
		m_Dt = m_DeltaClock.restart();
	}
}


void GameController::Update()
{
	// Save the frame as seconds
	float DeltaTime = m_Dt.asSeconds();

	// Spawn Enemie Ship every 2 seconds
	if (m_ESpawn < 0 && m_SpawnEnemie == true)
	{
		m_ESpawn = 2;
		m_Characters.push_back(new Enemie(m_EnemyTexture));
	}
	// Spawn Bullet everytime i press/hold space. Has a dealy to not spam bullets to fast.
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && m_Delay < 0 && m_PlayerDead == false)
	{
		m_Delay = 0.7;
		GetPosition(*m_Player);
		m_Bullets.push_back(new Bullets(m_BulletTexture, m_PlayerX + 54, m_PlayerY));
	}
	for (int i = 0; i < m_Characters.size(); i++)
	{
		if (m_Characters.size() > 1)
		{
			// Spawn a bullet for the enemie ships.
			if (m_BulletDelay <= 0 && m_Characters[i]->getIsFriendly() == false)
			{
				if (m_Characters[i]->m_Position.x == 0 && m_Characters[i]->m_Position.y == 0)
				{
					m_BulletDelay = 0;
				}
				else
				{
					m_EBullets.push_back(new EBullets(m_EBulletTexture, m_Characters[i]->m_Position.x, m_Characters[i]->m_Position.y));
					m_BulletDelay = 0.7;
				}
				
			}
		}
		// Update Characters update functions
		m_Characters[i]->Update(DeltaTime, m_Health);
		if (m_Characters[i]->m_Position.y > 1050)
		{
			if (m_Characters[i]->getIsFriendly() == false)
			{
				// Erase m_characters outside the window
				m_Characters.erase(m_Characters.begin() + i);
			}
		}
		//Update the enemies direction
		EneimeDir(*m_Characters[i]);
	}
	for (int i = 0; i < m_EBullets.size(); i++)
	{
		// Update Enemies bullet
		m_EBullets[i]->Update(1, 60 * 11, DeltaTime);
		if (m_Health > 0)
		{
			if (EBullerCollision(*m_EBullets[i], *m_Characters[0]))
			{
				// Collision between enmeis bullet and player
				m_EBullets.erase(m_EBullets.begin() + i);
				m_Health -= 1;
				break;
			}
		}
	}
	for (int i = 0; i < m_Bullets.size(); i++)
	{
		// Update the players bullet
		m_Bullets[i]->Update(-1, 60 * 11, DeltaTime);

		if (BulletPosition(*m_Bullets[i]))
		{
			// Erase the bullet when the bullet is utside the window
			m_Bullets.erase(m_Bullets.begin() + i);
			break;
		}

		for (int j = 0; j < m_Characters.size(); j++)
		{
			if (Collision(*m_Bullets[i], *m_Characters[j]) && m_Characters[j]->getIsFriendly() == false)
			{
				//Erase the bullet and the enemie ship when they collide

				m_Bullets.erase(m_Bullets.begin() + i);
				m_Characters.erase(m_Characters.begin() + j);
				m_Score += 10;
				break;
			}
		}
	}
	// Check the collision with player and enemies
	if (m_Characters.size() > 1 && m_Health > 0)
	{
		for (int j = 0; j < m_Characters.size(); j++)
		{
			if (PlayerCollision(*m_Characters[0], *m_Characters[j]))
			{
				if (m_Characters[j]->getIsFriendly() == false)
				{
					m_Health -= 1;
					m_Characters.erase(m_Characters.begin() + j);
				}

			}
		}
	}




	if (m_Health <= 0)
	{
		// Player removes and get the chance to restart the game with Enter
		m_PlayerDead = true;
		for (int i = 0; i < m_Characters.size(); i++)
		{
			if (m_Characters[i]->getIsFriendly() == true)
			{
				m_Characters.erase(m_Characters.begin());
			}
		}	
		RestartGame();

	}
	else
	{
		m_PlayerDead = false;
	}

	// Set the text
	m_TGameOver.setString("Game Over");
	m_Text.setString("Score: " + std::to_string(m_Score));
	m_TextHP.setString(std::to_string(m_Health));

}

void GameController::Draw()
{


	m_Window.clear();
	// Draw background
	m_Window.draw(m_BackgroundSprite0);

	// Draw ebullets
	for (int i = 0; i < m_EBullets.size(); i++)
	{
		m_EBullets[i]->Draw(m_Window);
	}
	for (int i = 0; i < m_Characters.size(); i++)
	{// Draw Characers player and enemeis
		m_Characters[i]->Draw(m_Window);
	}
	for (int i = 0; i < m_Bullets.size(); i++)
	{// Draw bullets
		m_Bullets[i]->Draw(m_Window);
	}



	m_Window.draw(m_Text);
	m_Window.draw(m_TextHP);
	m_Window.draw(m_HealthSprite);
	m_Window.draw(m_HealthXSprite);
	if (m_Health == 0)
	{
		// When player die draw gameover textw
		m_Window.draw(m_TGameOver);

	}


	m_Window.display();


}

void GameController::GetPosition(const Player &a)
{
	// Get player position
	m_PlayerX = a.m_MoveX;
	m_PlayerY = a.m_MoveY;

}
bool GameController::BulletPosition(const Bullets &a)
{
	// Check if bullet is outside the window
	if (a.m_BulletSprite.getPosition().y < -10)
	{
		return true;
	}

	return false;


}

void GameController::EneimeDir(Character &a)
{
	// Check the enemies pos and changes the dirrection
	if (!a.getIsFriendly())
	{
		if (a.m_Position.x >= 525)
		{
			a.m_ChangeDir = true;

		}
		if (a.m_Position.x <= 0)
		{
			a.m_ChangeDir = false;

		}
	}


}
bool GameController::Collision(const Bullets &a, const Character &b)
{
	//Const of Bullets and check if it collids with character
	if (b.m_rrect.intersects(a.m_rrect))
	{
		return true;
	}
	return false;
}

bool GameController::EBullerCollision(const EBullets &a, const Character &b)
{
	//Const of EBullets and check if it collids with character
	if (b.m_rrect.intersects(a.m_Rect))
	{
		return true;
	}
	return false;
}
bool GameController::PlayerCollision(const Character &a, const Character &b)
{
	//If character collids with character
	if (a.m_rrect.intersects(b.m_rrect))
	{
		return true;
	}
	return false;

}


void GameController::RestartGame()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
	{
		// RESETS THE GAME IF I PRESS ENTER
		m_SpawnEnemie = false;
		m_Health = 12; // ?? ska vara 10, om jag sätter den 10 så får jag 8...
		m_Score = 0;
		m_Enemie = new Enemie(m_EnemyTexture);
		m_Player = new Player(m_PlayerTexture);
		m_Characters.push_back(m_Player);		
		m_SpawnEnemie = true;
		//std::cout << "Restart" << std::endl;
	}

}