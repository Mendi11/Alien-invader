#pragma once

#include <SFML/Graphics.hpp>

class Bullets
{
public:
	Bullets(const sf::Texture& texture, float x, float y);
	~Bullets();
	void Update(int dir, int speed, float deltatime);
	void Draw(sf::RenderWindow& window);
	sf::FloatRect m_rrect;
	sf::Sprite m_BulletSprite;

private:
	float m_x, m_y;


};

