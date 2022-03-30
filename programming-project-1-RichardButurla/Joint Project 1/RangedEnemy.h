#pragma once
#include <SFML/Graphics.hpp>
#include "Bullets.h"
class RangedEnemy
{
public:
	RangedEnemy();
	~RangedEnemy();
	void update(sf::Time& t_deltaTime);
	void render(sf::RenderWindow& t_window);

	sf::Sprite getBody() { return m_body; }
	sf::Vector2f getPosition() { return m_location; }
	void shootPlayer(sf::Vector2f t_playerLocation);
	void setPosition(sf::Vector2f t_position) { m_location = t_position; }
	void setPosition(float xPos, float yPos) { m_location.x = xPos; m_location.y = yPos; }
	bool getAlive() { return m_alive; }
	void setAlive(bool t_alive) { m_alive = t_alive; }
	sf::Vector2f getVelocity() { return m_velocity; }
	void setSpawnPos(sf::Vector2f t_spawnlocation) { m_spawnLocation = t_spawnlocation; }
	bool acidHitPlayer(sf::Sprite t_playerBody);
	bool checkIfHit(sf::Sprite t_playerBullet);
	void respawnRangedEnemy();
	int getDamage() { return m_damage; }

protected:
	sf::Sprite m_body;
	sf::Texture m_rangedEnemyTexture;

	sf::Vector2f m_sizeOfBody{ 40.0f,40.0f };
	sf::Vector2f m_location;
	sf::Vector2f m_spawnLocation;
	sf::Vector2f directionVector;
	sf::Vector2f m_velocity;
	float m_speed = 5.0f;
	int m_damage = 1;
	bool m_alive{ true };
	Bullets m_acidProjectile;
	std::vector<Bullets> m_multipleAcidProjectiles;
	float m_acidSpeed = 10.0f;

	float m_acidShootDelay = 0.0;
	float m_acidFireRate =  0.008; //fire every 2 seconds

};

