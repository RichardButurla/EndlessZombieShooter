#include "EnemyEntity.h"
#include "Vector2.h"
#include <iostream>
#include <time.h>
#include <random>

EnemyEntity::EnemyEntity()
{
	if (!m_zombieTexture.loadFromFile("ASSETS\\IMAGES\\MeleeZombie.png")) {
		std::cout << "failed to load soldier texture";
	}
	m_body.setTextureRect(sf::IntRect(0.0, 0.0, 0.0f, 0.0f));
	m_body.setTexture(m_zombieTexture);
	m_body.setScale(3, 3);

	m_body.setOrigin(16.0f,16.0f);
	std::srand(static_cast<unsigned int>(time(nullptr)));
	int randomSpawn = rand() % 4 + 1;
	switch (randomSpawn)
	{
	case 1:
		m_spawnLocation = { 50.0f,50.0f };
		break;
	case 2:
		m_spawnLocation = { 1000.f, 20.0f };
		break;
	case 3:
		m_spawnLocation = { 50.0f, 700.0f };
		break;
	case 4:
		m_spawnLocation = { 1000.0f, 700.0f };
	default:
		break;
	}

	m_body.setPosition(m_spawnLocation);
}

void EnemyEntity::update(sf::Time& t_deltaTime)
{
	if (!m_alive) //respawn
	{
		m_body.setPosition(m_spawnLocation);
		m_alive = true;
	}

	m_body.move(m_location); //moves enemy to a location which is changed constantly by chasePlayer function

}

void EnemyEntity::render(sf::RenderWindow& t_window)
{
	t_window.draw(m_body);
}

/// <summary>
/// gets the distance between the player and the enemy
///  and sets it in that unit vector direction multiplied by speed.
/// </summary>
/// <param name="t_playerLocation">current player location</param>
void EnemyEntity::chasePlayer(sf::Vector2f t_playerLocation)
{
	sf::Vector2f directionVector = t_playerLocation - m_body.getPosition();
	sf::Vector2f directionNormal = vectorUnitVector(directionVector);
	m_velocity = directionNormal * m_speed;
	m_location = m_velocity;

	//rotate zombie
	float rotation = 0.0f;
	sf::Vector2f shapeLocation = m_body.getPosition();
	sf::Vector2f rotationVector;
	rotationVector.x = t_playerLocation.x - shapeLocation.x;
	rotationVector.y = t_playerLocation.y - shapeLocation.y;

	rotation = (atan2(rotationVector.x, rotationVector.y)) * 180 / PI;
	rotation = -rotation; //sfml window is upside down so negative rotation

	m_body.setRotation(rotation);
}
/// <summary>
/// stops all zombies from entering eachother using the other zombies position passed here as an arguement
/// when a collision is found to be true.
/// </summary>
/// <param name="t_intersectPos">position where the zombie has collided with another</param>
void EnemyEntity::friendlyCollision(sf::Vector2f t_intersectPos)
{
	float knockback = 0.9f;

	if (m_location.x < t_intersectPos.x)
		m_location.x = -knockback;

	if (m_location.x > t_intersectPos.x)
		m_location.x = +knockback;

	if (m_location.y > t_intersectPos.y)
		m_location.y = +knockback;

	if (m_location.y < t_intersectPos.y)
		m_location.y = -knockback;
}





