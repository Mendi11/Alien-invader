#pragma once
#include <SFML/Graphics.hpp>
class EBullets
{
public:
	EBullets(const sf::Texture& texture, float x, float y);
	~EBullets();
	void Update(int dir, int speed, float deltatime);
	void Draw(sf::RenderWindow& window);
	sf::Sprite m_EBulletSprite;
	sf::FloatRect m_Rect;

private:
	float m_x, m_y;
	

};

