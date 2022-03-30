#include "Bullets.h"
#include "GamePlay.h"
#include <iostream>


Bullets::Bullets()
{
	if (!m_bulletTexture.loadFromFile("ASSETS\\IMAGES\\riflebullet.png")) {
		std::cout << "failed to load soldier texture";
	}
	m_projectileSprite.setTexture(m_bulletTexture);
	m_projectileSprite.setOrigin(25.0f,33.0f);
	m_projectileSprite.setPosition(m_location);
	m_projectileSprite.setScale(0.75f, 0.75f);
	speed = 15.0f;
}

Bullets::~Bullets()
{
}
/// <summary>
/// moves bullet with a direction velocity given to it from gameplay
/// </summary>
/// <param name="t_deltaTime"></param>
void Bullets::update(sf::Time& t_deltaTime)
{
	m_location += m_velocity;
	m_projectileSprite.setPosition(m_location);
}

void Bullets::render(sf::RenderWindow& t_window)
{
	t_window.draw(m_projectileSprite);
}

void Bullets::rotateBulletSprite(sf::Vector2f t_mousePos,sf::Vector2f t_playerPos)
{
	float rotation = 0.0f;
	sf::Vector2f rotationVector;
	rotationVector.x = t_mousePos.x - t_playerPos.x;
	rotationVector.y = t_mousePos.y - t_playerPos.y;

	rotation = (atan2(rotationVector.x, rotationVector.y)) * 180 / PI;

	m_projectileSprite.setRotation(-rotation);
}






