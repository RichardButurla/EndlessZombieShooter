#include "RangedEnemy.h"
#include "Vector2.h"
#include <iostream>
#include "Player.h"
#include "Game.h"

RangedEnemy::RangedEnemy()
{
	

	if (!m_rangedEnemyTexture.loadFromFile("ASSETS\\IMAGES\\RangedZombie.png")) {
		std::cout << "failed to load soldier texture";
	}
	m_body.setTextureRect(sf::IntRect(0.0, 0.0, 32.0f, 32.0f));
	m_body.setTexture(m_rangedEnemyTexture);
	m_body.setScale(2, 2);
	m_body.setOrigin(m_sizeOfBody.x / 2, m_sizeOfBody.y / 2);

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

RangedEnemy::~RangedEnemy()
{
}
/// <summary>
/// update this enemy bullets and tick off at its firing delay per frame
/// </summary>
/// <param name="t_deltaTime">delta time</param>
void RangedEnemy::update(sf::Time& t_deltaTime)
{
	for (int i = 0; i < m_multipleAcidProjectiles.size(); i++)
	{
		m_multipleAcidProjectiles[i].update(t_deltaTime);
	}
	m_acidShootDelay = m_acidShootDelay - m_acidFireRate;
}
/// <summary>
/// renders bullets made by this enemy type and the enemy itself
/// if a bullete is not within the screen, erase to save memory.
/// </summary>
/// <param name="t_window">the sfml window</param>
void RangedEnemy::render(sf::RenderWindow& t_window)
{
	sf::View view = t_window.getView();
	sf::FloatRect viewRect((view.getCenter() - view.getSize() / 2.0f), view.getSize());

	for (unsigned int i = 0; i < m_multipleAcidProjectiles.size(); i++) { //renders all bullets and if they go off the window, they are erased.
		m_multipleAcidProjectiles[i].render(t_window);
		if (!viewRect.contains(m_multipleAcidProjectiles[i].getPosition())) { //if bullets are not within the rectangle
			m_multipleAcidProjectiles.erase(m_multipleAcidProjectiles.begin() + i); //erase that element from the vector bullet array
		}
	}
		t_window.draw(m_body); //draw enemy
}

/// <summary>
/// gets position between player and this enemy
/// sets a bullet in that direction and adds that bullet object to the vector array.
/// </summary>
/// <param name="t_playerLocation"> player location</param>
void RangedEnemy::shootPlayer(sf::Vector2f t_playerLocation)
{
	m_acidProjectile.rotateBulletSprite(t_playerLocation, m_body.getPosition());
	if (m_acidShootDelay <= 0) { //if enemy hasnt fired in a set amount of time
		sf::Vector2f directionVector = t_playerLocation - m_body.getPosition();
		sf::Vector2f directionNormal = vectorUnitVector(directionVector);
		m_acidProjectile.setLocation(m_body.getPosition());
		m_acidProjectile.setVelocity(directionNormal * m_acidSpeed);
		m_multipleAcidProjectiles.push_back(Bullets(m_acidProjectile)); //adds onto the vector array
		m_acidShootDelay = 1; //sets delay back to 1 and later gets ticked in update
	}

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
/// returns a boolean of hit to gameplay if the player was hit by a an acid bullet
/// </summary>
/// <param name="t_playerBody">player body</param>
/// <returns> boolean of the player being hit</returns>
bool RangedEnemy::acidHitPlayer(sf::Sprite t_playerBody)
{
	bool hit = false;
	for (int i = 0; i < m_multipleAcidProjectiles.size(); i++) //checks every bullet element within the vector array's size
	{
		if (m_multipleAcidProjectiles[i].getBody().getGlobalBounds().intersects(t_playerBody.getGlobalBounds())) { //if the bullet hit the player
			
			m_multipleAcidProjectiles.erase(m_multipleAcidProjectiles.begin() + i); //delete bullet
			hit = true;
		}
	}
	return hit;
}

/// <summary>
/// checks if this enemy was hit by a player bullet
/// </summary>
/// <param name="t_playerBullet">the bullet that the player fired</param>
/// <returns> boolean of whether this enemy was hit</returns>
bool RangedEnemy::checkIfHit(sf::Sprite t_playerBullet)
{
	bool hit = false; 
	if (t_playerBullet.getGlobalBounds().intersects(m_body.getGlobalBounds())) { //collision
		hit = true;
		m_alive = false;
		std::cout << "ranged enemy hit";
	}
	return hit;
}

/// <summary>
/// respawns the ranged enemy in set positions based on screen size
/// </summary>
void RangedEnemy::respawnRangedEnemy()
{
	int randomSpawn = rand() % 8 + 1;

	switch (randomSpawn)
	{
	case 1:
		m_spawnLocation = { 50.0f,50.0f }; //top left
		break;
	case 2:
		m_spawnLocation = { Game::s_screenWidth - 50.0f, 50.0f }; // top right
		break;
	case 3:
		m_spawnLocation = { 50.0f, Game::s_screenHeight - 50.0f }; //bottom left
		break;
	case 4:
		m_spawnLocation = { Game::s_screenWidth - 50.0f , Game::s_screenHeight - 50.0f }; //bottom right
		break;
	case 5:
		m_spawnLocation = { Game::s_screenWidth / 2.0f, 50.0f };//top middle
		break;
	case 6:
		m_spawnLocation = { Game::s_screenWidth / 2.0f, Game::s_screenHeight * 0.9f };//bottom middle
		break;
	case 7:
		m_spawnLocation = { 50.0f, Game::s_screenHeight / 2.0f };//middle left
		break;
	case 8:
		m_spawnLocation = { Game::s_screenWidth - 50.0f, Game::s_screenHeight / 2.0f };//middle right//test
	default:
		break;
	}
	m_location = m_spawnLocation;
	m_body.setPosition(m_location);
}
