#include "Player.h"
#include "Game.h"
#include "Vector2.h"
#include "GamePlay.h"
#include <iostream>

Player::Player()
{
	if (!m_soldierTexture.loadFromFile("ASSETS\\IMAGES\\SoldierSpriteSheet.png")) {
		std::cout << "failed to load soldier texture";
	}
	m_body.setTextureRect(sf::IntRect(64.0, 0.0, 32.0f, 28.0f));
	m_body.setTexture(m_soldierTexture);
	m_body.setScale(2, 2);
	m_body.setOrigin(m_bodySize.x / 2, m_bodySize.y / 2);
	m_location = { Game::s_screenWidth / 2, Game::s_screenHeight / 2 };//initial location in middle
	m_body.setPosition(m_location);
	m_lives = MAX_PLAYER_LIVES;

}

Player::~Player()
{
}


/// <summary>
/// handle player movement here
/// </summary>
/// <param name="t_deltatime">delta time</param>
void Player::update(sf::Time& t_deltatime)
{

	//movement 
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		m_location.y += -m_movementSpeed;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		m_location.x += -m_movementSpeed;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		m_location.y += m_movementSpeed;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		m_location.x += m_movementSpeed;
	}
	m_body.setPosition(m_location);


}

/// <summary>
/// while player is alive, we render them
/// </summary>
/// <param name="t_window"> sfml window</param>
void Player::render(sf::RenderWindow& t_window)
{
	if(m_lives > 0)
	t_window.draw(m_body);
}

/// <summary>
/// gets the distance between the mouse position and player position
/// and rotates the player to the mouse co-ordiante.
/// </summary>
/// <param name="t_mousePos">mouse position</param>
void Player::rotatePlayer(sf::Vector2f t_mousePos)
{
	float rotation = 0.0f;
	sf::Vector2f shapeLocation = m_body.getPosition();
	sf::Vector2f rotationVector;
	rotationVector.x = t_mousePos.x - shapeLocation.x;
	rotationVector.y = t_mousePos.y - shapeLocation.y;

	rotation = (atan2(rotationVector.x, rotationVector.y)) * 180 / PI;
	rotation = -rotation; //sfml window is upside down so negative rotation

	m_body.setRotation(rotation);
}

/// <summary>
/// keeps player within the screen
/// </summary>
void Player::checkPlayerBounds()
{
	if (m_location.x <= 0 + m_bodySize.x ) {
		m_location.x = 0 + m_bodySize.x;
	}
	if (m_location.x >= Game::s_screenWidth - m_bodySize.x) {
		m_location.x = Game::s_screenWidth - m_bodySize.x;
	}
	if (m_location.y <= 0 + m_bodySize.x) {
		m_location.y = 0 + m_bodySize.x;
	}
	if (m_location.y >= Game::s_screenHeight - m_bodySize.x) {
		m_location.y = Game::s_screenHeight - m_bodySize.x;
	}
}









