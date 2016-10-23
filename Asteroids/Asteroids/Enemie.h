#pragma once
#include "Character.h"
#include "Bullets.h"
#include <vector>

class Enemie : public Character
{
public:
	Enemie(const sf::Texture& texture);
	~Enemie();
	void Update(float deltatime, int health) override;
	void Draw(sf::RenderWindow& window) override;
	sf::Sprite m_EnemySprite;
	int m_DirSpeed;

private:
	float m_Delay;


};

