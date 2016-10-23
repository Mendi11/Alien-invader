#pragma once

#include <string>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>	
#include <vector>
#include "Player.h"
#include "Enemie.h"
#include "Bullets.h"
#include "EBullets.h"

class Character;
class GameController
{
public:
	GameController();
	~GameController();

	void Run();
	void GameController::GetPosition(const Player &a);
	float m_PlayerX, m_PlayerY;

private:
	bool GameController::Collision(const Bullets &a, const Character &b);
	bool BulletPosition(const Bullets &a);
	void GameController::EneimeDir(Character &a);
	bool PlayerCollision(const Character &a, const Character &b);
	bool EBullerCollision(const EBullets &a, const Character &b);
	void RestartGame();


	std::vector<sf::Drawable*> m_Draw;
	std::vector<Character*> m_Characters;
	std::vector<Bullets*> m_Bullets;
	std::vector<EBullets*> m_EBullets;

	Bullets* m_Bullet;
	EBullets* m_Ebullet;
	Player* m_Player;
	Enemie* m_Enemie;


	sf::Clock m_DeltaClock;
	sf::Time m_Dt;

	float m_Delay;
	float m_BulletDelay;
	float m_ESpawn;

	sf::Texture m_PlayerTexture;
	sf::Texture m_EnemyTexture;
	sf::Texture m_BulletTexture;
	sf::Texture m_EBulletTexture;
	sf::Texture m_HealtShip;
	sf::Texture m_Background;
	sf::Texture m_HealthX;

	sf::Sprite m_BackgroundSprite0;
	sf::Sprite m_HealthSprite;
	sf::Sprite m_HealthXSprite;

	void Update();
	void Draw();

	sf::RenderWindow m_Window;

	sf::Text m_TGameOver;
	sf::Text m_Text;
	sf::Font m_Font;
	sf::Text m_TextHP;


	int m_Score;
	int m_Health;

	bool m_SpawnEnemie;
	bool m_PlayerDead;



};

