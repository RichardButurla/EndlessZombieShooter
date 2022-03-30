#pragma once
#include <SFML/Graphics.hpp>
class EnemyEntity
{
public:
	EnemyEntity();
	void update(sf::Time& t_deltaTime);
	void render(sf::RenderWindow& t_window);
	void chasePlayer(sf::Vector2f t_playerLocation);
	void friendlyCollision(sf::Vector2f t_intersectPos);

	sf::Sprite getBody() { return m_body; }
	sf::Vector2f getPosition() { return m_location; }
	void setPosition(sf::Vector2f t_position) { m_location = t_position; }
	void setPosition(float xPos, float yPos) { m_location.x = xPos; m_location.y = yPos; }
	bool getAlive() { return m_alive; }
	void setAlive(bool t_alive) { m_alive = t_alive; }
	sf::Vector2f getVelocity() { return m_velocity; }
	void setSpawnPos(sf::Vector2f t_spawnlocation) { m_spawnLocation = t_spawnlocation; }
	int getDamage() { return m_damage; }

protected:
	sf::Sprite m_body;
	sf::Texture m_zombieTexture;
	sf::Vector2f m_sizeOfBody{ 32.0f,32.0f };
	sf::Vector2f m_location;
	sf::Vector2f m_spawnLocation;
	sf::Vector2f directionVector;
	sf::Vector2f m_velocity;
	float m_speed = 5.0f;
	int m_damage = 1;
	bool m_alive{ true };
};

