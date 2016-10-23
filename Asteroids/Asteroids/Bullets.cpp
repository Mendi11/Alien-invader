#include "Bullets.h"

Bullets::Bullets(const sf::Texture& texture, float x, float y) :
	m_BulletSprite(texture), m_x(x), m_y(y)
{
	m_BulletSprite.setPosition(m_x, m_y);


}


Bullets::~Bullets()
{
}

void Bullets::Update(int dir, int speed, float deltatime)
{
	//Direction and speed on the bullet and set the sprite to a floatrectangle
	m_rrect = m_BulletSprite.getGlobalBounds();
	m_BulletSprite.move(0, speed * dir * deltatime);


}
void Bullets::Draw(sf::RenderWindow& window)
{

	window.draw(m_BulletSprite);
}