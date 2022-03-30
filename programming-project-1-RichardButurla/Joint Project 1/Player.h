#pragma once
#include <SFML/Graphics.hpp>

class Player
{
public:
	Player();
	~Player();

	static const int MAX_PLAYER_LIVES = 10;
	void update(sf::Time& t_deltatime);
	void render(sf::RenderWindow& t_window);
	void rotatePlayer(sf::Vector2f t_mousePos);
	void checkPlayerBounds();
	sf::Vector2f getLocation() { return m_location; }
	sf::Sprite getBody() { return m_body; }
	void setLocation(sf::Vector2f t_location) { m_location = t_location; }
	void setLives(int t_lives) { m_lives = t_lives; }
	int getLives() { return m_lives; }
	sf::Vector2f getBodySize() { return m_bodySize; }



protected:
	sf::Sprite m_body;
	sf::Texture m_soldierTexture;

	sf::Vector2f m_bodySize{ 32.0f,32.0f };
	sf::Vector2f m_location;
	float m_movementSpeed = 10.0f;
	int m_lives = 7;


};
