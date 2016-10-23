#pragma once
#include <SFML/Graphics.hpp>
#include "Character.h"
#include "Bullets.h"
#include <stdint.h>


class Player : public Character
{
public:
	Player(const sf::Texture& texture);
	~Player();
	void Update(float deltatime, int health) override;
	void Draw(sf::RenderWindow& window) override;
	float m_MoveX;
	float m_MoveY;

private:

	sf::Sprite m_Sprite;


};

