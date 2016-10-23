#include "Player.h"
#include "Bullets.h"
#include <iostream>


Player::Player(const sf::Texture& texture) :
	Character(true),
	m_Sprite(texture), m_MoveX(250),
	m_MoveY(800)// Setting the position spawn
{

}


Player::~Player()
{
}


void Player::Update(float deltatime, int health)
{
	m_Position = m_Sprite.getPosition();
	m_rrect = m_Sprite.getGlobalBounds();

	int speed = 60 * 8;
	// Move posisiton On the player
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && m_Position.y >= 0)
		m_MoveY -= speed * deltatime;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && m_Position.x <= 490)
		m_MoveX += speed * deltatime;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && m_Position.y <= 825)
		m_MoveY += speed * deltatime;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && m_Position.x >= 0)
		m_MoveX -= speed * deltatime;
	m_Sprite.setPosition(m_MoveX, m_MoveY);
	//std::cout << health << std::endl;


}
void Player::Draw(sf::RenderWindow& window)
{

	window.draw(m_Sprite);
}

