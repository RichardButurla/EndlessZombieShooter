#pragma once
#include <SFML/Graphics.hpp>

class Bullets
{
public:
	Bullets();
	~Bullets();
	static const int MAX_BULLETS = 10;

	void update(sf::Time& t_deltaTime);
	void render(sf::RenderWindow& t_window);
	void setLocation(sf::Vector2f t_playerLocation) { m_location = t_playerLocation; }
	void setTexture(sf::Texture t_bulletTex) { m_bulletTexture = t_bulletTex; }
	sf::Vector2f getPosition() { return m_location; }
	sf::Sprite getBody() { return m_projectileSprite; }
	void setVelocity(sf::Vector2f t_velocity) { m_velocity = t_velocity; }
	void rotateBulletSprite(sf::Vector2f t_mousePos, sf::Vector2f t_playerPos);
	void setScale(float xTex, float yTex) { m_projectileSprite.setScale(xTex, yTex); }
	sf::Vector2f getVelocity() { return m_velocity; }
	float getSpeed() { return speed; }

protected:
	sf::Sprite m_projectileSprite;
	sf::Texture m_bulletTexture;
	sf::Vector2f m_location{ 0,0 };
	sf::Vector2f m_velocity;
	float speed;
};
