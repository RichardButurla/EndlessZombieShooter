#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Bullets.h"
#include "Vector2.h"
#include "EnemyEntity.h"
#include "RangedEnemy.h"
#include <vector>

class GamePlay
{
public:
	GamePlay();
	~GamePlay();

	static const int MAX_ENEMIES = 20;
	static const int MAX_RANGED_ENEMIES = 3;
	static const int SPAWN_TIME = 5;
	static const int MAG_CAPACITY = 30;
	int finalScore = 0;//passed on to gameOver screen
	int m_currentNumberOfEnemies = 1;
	int m_currentNumberOfRangedEnemies = 1;

	void initialise(sf::Font& t_font);
	void render(sf::RenderWindow& t_window);
	void processEvents(sf::Event& t_event);
	void update(sf::Time& t_deltatime);
	void moveCamera();
	void tickTimers();

	void bulletCollision(int t_bulletCell, int t_zombieCell);
	void checkPlayerCollision(int t_zombieCell);
	void checkZombiesCollide(int t_firstZomb, int t_secondZomb);
	void respawnEnemy(int t_zombiecell);
	void spawnEnemy();


	//Weapons
	void switchWeapon();
	void shootBullet();
	void checkMag();

	void checkPlayerLife();
	void resetGame();

protected:
	bool isFiring{ false };

	//background
	sf::Sprite m_backgroundSprite;
	sf::Texture m_backgroundTex;

	//Enemy
	EnemyEntity m_enemy;
	EnemyEntity m_zombieArray[MAX_ENEMIES];
	sf::Vector2f m_spawnLocation;

	RangedEnemy m_rangedZombieArray[MAX_RANGED_ENEMIES];

	//Game
	bool m_gameOver{false};

	//Player
	sf::Vector2f m_playerLocation;
	Player m_player;

	//Bullets
	Bullets m_singleBullet;
	std::vector<Bullets> m_multipleBullets;
	sf::Vector2f m_currentBulletVelocity;
	bool isReloading{ false };
	int m_bulletsShot = 0;

	//Weapons
	bool m_holdingRifle = true;
	float m_rifleShootDelay = 0.0f ;
	float m_rifleFireRate = 0.19; //11 rounds a second

	float m_shotgunFireRate = 0.032; //60fps so every half second it can fire

	bool m_holdingShotgun = false;
	float m_shotgunShootDelay = 0.0;

	bool m_holdingSniper = false;
	float m_sniperShootDelay = 0.0;
	float m_sniperFireRate = 0.016;

	float reloadTime = 3;

	//bulletTextures
	sf::Texture m_rifleBulletTex;
	sf::Texture m_shotgunPelletTex;
	sf::Texture m_sniperBulletTex;


	//mouse
	sf::Vector2f m_mousePos;
	sf::Vector2f m_aimingDirection;
	sf::Vector2f m_aimingNormal;


	//timers
	float frameDecrement = 0.016;
	float meleeZombieSpawnCounter = 1;
	float rangedZombieSpawnCounter = 5;

	

	//Text
	sf::Font m_font;

	sf::Text m_reloadText;

	sf::Text m_currentWeaponText;

	sf::Text m_playerLifeText;
	int m_playerLives = 7;

	sf::Text m_scoreText;
	int m_scoreNumber = 0;

	//View
	sf::View playerView;
	float viewSpeed = 5.0f;///experimental

	//GameOver stuff
	static const int m_numberOfButtons = 3;
	sf::Sprite m_buttonsSprites[m_numberOfButtons];
	sf::Texture m_buttonTexture;
	sf::Text m_buttonTexts[m_numberOfButtons];
	sf::String m_menuTexts[m_numberOfButtons] = { "Score: " + std::to_string(finalScore),"Restart","Exit" };

	//background
	sf::Sprite m_mainMenuBackground;
	sf::Texture m_mainMenuBackgroundTexture;

	//offsets for spacing
	float m_topOffset{ 0.0f };
	float m_leftOffset{ 0.0f };
	float m_verticalSpacing{ 0.0f }; //gap between buttons
	float m_buttonWidth{ 0.0f };
	float m_buttonHeight{ 0.0f }; //less than vertical spacing

};

