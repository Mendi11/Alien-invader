#include "EBullets.h"



EBullets::EBullets(const sf::Texture& texture, float x, float y):
	m_EBulletSprite(texture),m_x(x),m_y(y)
{
	m_EBulletSprite.rotate(180);
	m_EBulletSprite.setPosition(m_x + 10,m_y + 100 );

}


EBullets::~EBullets()
{
}


void EBullets::Update(int dir, int speed, float deltatimes)
{
	//Direction and speed on the bullet and set the sprite to a floatrectangle
	m_Rect = m_EBulletSprite.getGlobalBounds();
	m_EBulletSprite.move(0, speed * deltatimes);
}


void EBullets::Draw(sf::RenderWindow& window)
{

	window.draw(m_EBulletSprite);
}

