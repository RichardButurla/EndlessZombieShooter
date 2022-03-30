#include "GamePlay.h"
#include "Game.h"
#include "EnemyEntity.h"
#include <iostream>
#include <time.h>
#include <random>




GamePlay::GamePlay()
{
	std::srand(static_cast<unsigned int>(time(nullptr)));
}

GamePlay::~GamePlay()
{

}

/// <summary>
/// set text position,color,etc.
/// load button texture
/// </summary>
/// <param name="t_font"></param>
void GamePlay::initialise(sf::Font& t_font)
{
	m_font = t_font;
	m_reloadText.setFont(m_font);
	m_reloadText.setCharacterSize(30U);
	m_reloadText.setStyle(sf::Text::Bold);
	m_reloadText.setFillColor(sf::Color::White);
	m_reloadText.setOutlineColor(sf::Color::Red);
	m_reloadText.setPosition(Game::s_screenWidth * 0.8f, Game::s_screenHeight - Game::s_screenHeight + 20.0f);


	m_scoreText.setFont(m_font);
	m_scoreText.setCharacterSize(30U);
	m_scoreText.setStyle(sf::Text::Bold);
	m_scoreText.setFillColor(sf::Color::White);
	m_scoreText.setOutlineColor(sf::Color::Red);
	m_scoreText.setPosition(Game::s_screenWidth * 0.02f, Game::s_screenHeight - Game::s_screenHeight + 20.0f);
	m_scoreText.setString("Score: " + std::to_string(m_scoreNumber));


	m_playerLifeText.setFont(m_font);
	m_playerLifeText.setCharacterSize(30U);
	m_playerLifeText.setStyle(sf::Text::Bold);
	m_playerLifeText.setFillColor(sf::Color::White);
	m_playerLifeText.setOutlineColor(sf::Color::Red);
	m_playerLifeText.setPosition(Game::s_screenWidth * 0.45f, Game::s_screenHeight - Game::s_screenHeight + 20.0f);
	m_playerLifeText.setString("Lives: " + std::to_string(Player::MAX_PLAYER_LIVES));

	m_currentWeaponText.setFont(m_font);
	m_currentWeaponText.setCharacterSize(30U);
	m_currentWeaponText.setStyle(sf::Text::Bold);
	m_currentWeaponText.setFillColor(sf::Color::White);
	m_currentWeaponText.setOutlineColor(sf::Color::Red);
	m_currentWeaponText.setPosition(Game::s_screenWidth * 0.02f, Game::s_screenHeight - 50.0f);
	m_currentWeaponText.setString("Current Weapon: Rifle");

	
	m_topOffset = Game::s_screenHeight / 8; //change if bad scaling
	m_verticalSpacing = Game::s_screenHeight / 4;
	m_buttonWidth = Game::s_screenWidth / 2; //change if bad scaling
	m_leftOffset = (Game::s_screenWidth - m_buttonWidth) / 2;
	m_buttonHeight = Game::s_screenHeight / 8; //change if bad scaling
	int textDropOffset = static_cast<int>(Game::s_screenHeight / 6.5);

	m_menuTexts[0] = { "Score: " +std::to_string(finalScore)};
	m_menuTexts[1] = { "Restart"};
	m_menuTexts[2] = { "Exit" };

	if (!m_buttonTexture.loadFromFile("ASSETS/IMAGES/MenuButtons.jpg")) //not too efficient, should create a function to get a texture from main menu
	{
		std::cout << "error loading button file" << std::endl;
	}

	/// <summary>
	/// setup button sprites + textures, button text, position button and text
	/// </summary>
	/// <param name="t_font"></param>
	for (int i = 0; i < m_numberOfButtons; i++)
	{
		m_buttonsSprites[i].setTexture(m_buttonTexture);
		m_buttonsSprites[i].setPosition(m_leftOffset, m_verticalSpacing * i + m_topOffset); //100 x any other button to push it down
		sf::Vector2u textureSize = m_buttonTexture.getSize(); //unsigned vector to set scale
		m_buttonsSprites[i].setScale(m_buttonWidth / textureSize.x, m_buttonHeight / textureSize.y);

		m_buttonTexts[i].setFont(m_font);
		m_buttonTexts[i].setString(m_menuTexts[i]); //every button gets a menu option string
		m_buttonTexts[i].setFillColor(sf::Color::Yellow);
		m_buttonTexts[i].setOutlineColor(sf::Color::Red);
		m_buttonTexts[i].setCharacterSize(40U);

		sf::FloatRect textSize = m_buttonTexts[i].getGlobalBounds();
		float textOffset = (m_buttonWidth / 2) - (textSize.width / 2); //alligns text onto the middle of the button
		m_buttonTexts[i].setPosition(m_leftOffset + textOffset, m_verticalSpacing * i + textDropOffset); //multiply Vertical spacing by "i" to set the texts right

	}

	//background
	if (!m_backgroundTex.loadFromFile("ASSETS/IMAGES/Background.jpg")) //not too efficient, should create a function to get a texture from main menu
	{
		std::cout << "error loading background" << std::endl;
	}
	m_backgroundSprite.setTexture(m_backgroundTex);

	if (!m_rifleBulletTex.loadFromFile("ASSETS\\IMAGES\\riflebullet.png")) {
		std::cout << "failed to load rifle bullet texture";
	}
	if (!m_shotgunPelletTex.loadFromFile("ASSETS\\IMAGES\\shotgunpellet.png")) {
		std::cout << "failed to load shorgun pellet tex texture";
	}
	if (!m_sniperBulletTex.loadFromFile("ASSETS\\IMAGES\\sniperbullet.png")) {
		std::cout << "failed to load sniper bullet texture";
	}
}

void GamePlay::render(sf::RenderWindow& t_window)
{
	t_window.draw(m_backgroundSprite);
	t_window.draw(m_currentWeaponText);
	sf::View view = t_window.getView();
	sf::FloatRect viewRect((view.getCenter() - view.getSize() / 2.0f), view.getSize());
	m_player.render(t_window);
	

	for (unsigned int b = 0; b < m_multipleBullets.size(); b++) { //render bullet
		m_multipleBullets[b].render(t_window);

		if (!viewRect.contains(m_multipleBullets[b].getPosition())) { //if the bullet is not in the window, delete it
			m_multipleBullets.erase(m_multipleBullets.begin() + b);
		}
	}
	for (int i = 0; i < m_currentNumberOfRangedEnemies; i++) //render all ranged enemies
	{
		m_rangedZombieArray[i].render(t_window);
	}
	for (int z = 0; z < m_currentNumberOfEnemies; z++) //render all melee enemies
	{
		m_zombieArray[z].render(t_window);
	}

	//draw texts
	t_window.draw(m_reloadText);
	t_window.draw(m_scoreText);
	t_window.draw(m_playerLifeText);
	
	

	if (m_gameOver) { //draw the texts and buttons that come on screen once player dies
		for (int i = 0; i < m_numberOfButtons; i++)
		{
			t_window.draw(m_buttonsSprites[i]);
			t_window.draw(m_buttonTexts[i]);
		}
	}
	//t_window.setView(playerView); //experimental
}

/// <summary>
/// check events and process them here
/// </summary>
/// <param name="t_event"> game event</param>
void GamePlay::processEvents(sf::Event& t_event)
{
	if (sf::Event::MouseMoved == t_event.type) { //always gets the mouse position when mouse is moved
		m_mousePos.x = static_cast<float>(t_event.mouseMove.x);
		m_mousePos.y = static_cast<float>(t_event.mouseMove.y);
		m_player.rotatePlayer(m_mousePos);
	}
	if (sf::Event::KeyPressed == t_event.type) { //if a key is pressed
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) { //if the key E is pressed
			switchWeapon();
		}
	}

}
/// <summary>
/// update player first, then bullet, then enemy.
/// </summary>
/// <param name="t_deltatime"></param>
void GamePlay::update(sf::Time& t_deltatime)
{
	//while game is not over, update and render the gameplay objects,etc
	if (!m_gameOver) {
		tickTimers();
		moveCamera();
		checkPlayerLife();
		spawnEnemy();
		checkMag();

		m_singleBullet.rotateBulletSprite(m_mousePos,m_player.getLocation());

	

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) //called here because shooting is independant of rotation in process Events.
			if (!isReloading) {
				shootBullet();
			}
				


		for (int z = 0; z < m_currentNumberOfEnemies; z++) { //checks collision of bullet against zombies
			for (int b = 0; unsigned(b) < m_multipleBullets.size(); b++) {

				bulletCollision(b, z);
			}
		}


		for (int i = 0; i < m_currentNumberOfRangedEnemies; i++)
		{
			for (int b = 0; unsigned(b) < m_multipleBullets.size(); b++) {
				if (m_rangedZombieArray[i].checkIfHit(m_multipleBullets[b].getBody()) == true) { //checks if ranged zombie was hit by player bullet
					m_rangedZombieArray[i].respawnRangedEnemy();
					m_scoreNumber += 10;
					m_scoreText.setString("Score " + std::to_string(m_scoreNumber)); //adding score and set to string
				}
			}
			if (m_rangedZombieArray[i].acidHitPlayer(m_player.getBody()) == true) { //checks if the ranged zombie hit the player
				int newPlayerLife = m_player.getLives() - 1;
				m_player.setLives(newPlayerLife);
				m_playerLifeText.setString("Lives: " + std::to_string(m_player.getLives()));
			}
			m_rangedZombieArray[i].shootPlayer(m_player.getLocation());
			m_rangedZombieArray[i].update(t_deltatime); //update rnaged enemy after we check everything
		}

		for (size_t b = 0; b < m_multipleBullets.size(); b++) {
			m_multipleBullets[b].update(t_deltatime); //update all bullets
		}

		for (int z = 0; z < m_currentNumberOfEnemies; z++) {
			m_zombieArray[z].chasePlayer(m_player.getLocation()); //make all melee zombie chase player
			checkPlayerCollision(z);
		}

		for (int a = 0; a < m_currentNumberOfEnemies; a++) {
			for (int b = 1 + a; b < m_currentNumberOfEnemies; b++) {
				checkZombiesCollide(a, b); //checks if melee zombies went inside eachother
			}
		}

		for (int i = 0; i < m_currentNumberOfEnemies; i++) { //update all melee zombies
			m_zombieArray[i].update(t_deltatime); 
		}
		m_player.checkPlayerBounds();
		m_player.update(t_deltatime);
	}
	if (m_gameOver) { //if the game is over, make these events possible
		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
		{
			sf::Vector2i mousePosition = static_cast<sf::Vector2i>(m_mousePos);//integer vector since window is positive

			if (mousePosition.x > m_leftOffset && mousePosition.x < m_leftOffset + m_buttonWidth) //checks all x positions since buttons are equally distanced
			{
				if (mousePosition.y > m_topOffset + m_verticalSpacing && mousePosition.y < m_topOffset + m_verticalSpacing + m_buttonHeight) //verticalSpacing * index + buttonheight can be used for multiple buttons
					resetGame(); //restart game

				if (mousePosition.y > m_topOffset + m_verticalSpacing * 2 && mousePosition.y < m_topOffset + m_verticalSpacing * 2 + m_buttonHeight)
					Game::currentState = GameState::MainMenu; //exit gameplay
			}
		}
	}
}



/// <summary>
/// check which weapon we are currently holding
/// then set location of the bullet to the player, and get which direction its facing.
/// then set bullet in that direction and add onto the vector array.
/// increment bullets shot and set the fire rate timer of the gun to 1 which is ticked in update.
/// </summary>
void GamePlay::shootBullet()
{
	

	if (m_holdingRifle) { 
		m_singleBullet.setTexture(m_rifleBulletTex);
		m_singleBullet.setScale(0.75f, 0.75f);
		if (m_rifleShootDelay <= 0) {
			m_singleBullet.setLocation(m_player.getLocation()); //set bullet to player position when firing
			m_currentBulletVelocity = vectorUnitVector(m_mousePos - m_player.getLocation()) * m_singleBullet.getSpeed(); //set bullet in that direction
			m_singleBullet.setVelocity(m_currentBulletVelocity); //we give it unit vector because in bullet class it multiplies by speed
			m_multipleBullets.push_back(Bullets(m_singleBullet)); //add new element onto vector array
			m_bulletsShot += 1;
			m_rifleShootDelay = 1;
		}
	
	}
	if (m_holdingShotgun) {
		m_singleBullet.setTexture(m_shotgunPelletTex);
		m_singleBullet.setScale(0.25f, 0.25f);
		if (m_shotgunShootDelay <= 0) {
			m_singleBullet.setLocation(m_player.getLocation()); //set bullet to player position when firing
			m_currentBulletVelocity = vectorUnitVector(m_mousePos - m_player.getLocation()) * m_singleBullet.getSpeed(); //set bullet in that direction
			m_singleBullet.setVelocity(m_currentBulletVelocity);
			sf::Vector2f facing = m_currentBulletVelocity;
			m_multipleBullets.push_back(Bullets(m_singleBullet)); //straight ahead.

			//positve spread then reset, then negative for spread to look real, not a moving fan of bullets
			float rotation = 0.1f;
			facing = vectorRotateBy(facing, rotation);
			m_singleBullet.setVelocity(facing);
			m_multipleBullets.push_back(Bullets(m_singleBullet));

			facing = m_currentBulletVelocity; //reset direction for new rotation;
			rotation = -rotation;
			facing = vectorRotateBy(facing, rotation);
			m_singleBullet.setVelocity(facing);
			m_multipleBullets.push_back(Bullets(m_singleBullet));

			facing = m_currentBulletVelocity; //reset direction for new rotation;
			rotation = -rotation * 2;
			facing = vectorRotateBy(facing, rotation);
			m_singleBullet.setVelocity(facing);
			m_multipleBullets.push_back(Bullets(m_singleBullet));

			facing = m_currentBulletVelocity; //reset direction for new rotation;
			rotation = -rotation;
			facing = vectorRotateBy(facing, rotation);
			m_singleBullet.setVelocity(facing);
			m_multipleBullets.push_back(Bullets(m_singleBullet));

			m_shotgunShootDelay = 1; //take away by 0.016 in update
		}	
	}
	if (m_holdingSniper) {
		m_singleBullet.setTexture(m_sniperBulletTex);
		m_singleBullet.setScale(0.75f, 0.75f);
		if (m_sniperShootDelay <= 0)
		{
			m_singleBullet.setLocation(m_player.getLocation()); //set bullet to player position when firing
			m_currentBulletVelocity = vectorUnitVector(m_mousePos - m_player.getLocation()) * m_singleBullet.getSpeed(); //set bullet in that direction
			m_singleBullet.setVelocity(m_currentBulletVelocity); //we give it unit vector because in bullet class it multiplies by speed
			m_multipleBullets.push_back(Bullets(m_singleBullet));
			m_bulletsShot += 1;
			m_sniperShootDelay = 1;
		}
	}
	
}
/// <summary>
/// checks if player is currently reloading and starts timer that is ticked later
/// sets text based on if player is reloading
/// </summary>
void GamePlay::checkMag()
{
	if (m_bulletsShot >= MAG_CAPACITY) {
		isReloading = true;
		reloadTime = 3;
		m_bulletsShot = 0;
		m_reloadText.setString("Reloading...");
	}
	if (reloadTime <= 0) {
		isReloading = false;
		m_reloadText.setString("");
	}
}


/// <summary>
/// handles bullet collision between player bullets and melee zombies
/// </summary>
/// <param name="t_bulletCell"></param>
/// <param name="t_zombieCell"></param>
void GamePlay::bulletCollision(int t_bulletCell, int t_zombieCell)
{
	if (m_multipleBullets[t_bulletCell].getBody().getGlobalBounds().intersects(m_zombieArray[t_zombieCell].getBody().getGlobalBounds()))
	{
		m_scoreNumber += 10;
		m_scoreText.setString("Score " + std::to_string(m_scoreNumber)); //adding score and set to string

		m_bulletsShot += 1;//this here because even if mouse left is pressed once, sometimes more bullets can fire

		if (!m_holdingSniper) { //sniper penetrates so we dont erase.
			m_multipleBullets.erase(m_multipleBullets.begin() + t_bulletCell); //remove bullet and respawn enemy.
		}
		
		m_zombieArray[t_zombieCell].setAlive(false);
		respawnEnemy(t_zombieCell);
	}
}

void GamePlay::checkPlayerCollision(int t_zombieCell)
{

	if (m_player.getBody().getGlobalBounds().intersects(m_zombieArray[t_zombieCell].getBody().getGlobalBounds()))
	{
		//player loses one life when zombie touches them
		int newPlayerLife = m_player.getLives() - m_zombieArray[t_zombieCell].getDamage();
		m_player.setLives(newPlayerLife);
		m_playerLifeText.setString("Lives: " + std::to_string(m_player.getLives()));


		std::cout << "playerHit";
		//Knock zombies back so they dont glue to player
		float knockback = 40.0f;
		sf::Vector2f m_zombieLocation = m_zombieArray[t_zombieCell].getPosition();
		m_zombieArray[t_zombieCell].setPosition(m_zombieLocation - m_zombieArray[t_zombieCell].getVelocity() * knockback);

		//m_zombieArray[t_zombieCell].setPosition(m_playerLocation);
	}
}

void GamePlay::checkZombiesCollide(int t_firstZomb, int t_secondZomb)
{
	if (m_zombieArray[t_firstZomb].getBody().getGlobalBounds().intersects(m_zombieArray[t_secondZomb].getBody().getGlobalBounds()))
		m_zombieArray[t_firstZomb].friendlyCollision(m_zombieArray[t_secondZomb].getPosition());
}

void GamePlay::respawnEnemy(int t_zombiecell)
{
	int randomSpawn = rand() % 8 + 1;

	switch (randomSpawn)
	{
	case 1:
		m_spawnLocation = { 50.0f,50.0f }; //top left
		break;
	case 2:
		m_spawnLocation = { Game::s_screenWidth, 50.0f }; // top right
		break;
	case 3:
		m_spawnLocation = { 50.0f, Game::s_screenHeight }; //bottom left
		break;
	case 4:
		m_spawnLocation = { Game::s_screenWidth, Game::s_screenHeight }; //bottom right
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
		m_spawnLocation = { Game::s_screenWidth, Game::s_screenHeight / 2.0f };//middle right//test
	default:
		break;
	}
	m_zombieArray[t_zombiecell].setSpawnPos(m_spawnLocation);
}



void GamePlay::spawnEnemy()
{
	if (meleeZombieSpawnCounter <= 0)
	{
		if (m_currentNumberOfEnemies < MAX_ENEMIES) {
			m_currentNumberOfEnemies += 1;
		}
		meleeZombieSpawnCounter = 5; //every 5 seconds
	}
	if (rangedZombieSpawnCounter <= 0) {
		if (m_currentNumberOfRangedEnemies < MAX_RANGED_ENEMIES) {
			m_currentNumberOfRangedEnemies++;
		}
		rangedZombieSpawnCounter = 5;
	}
}



void GamePlay::switchWeapon()
{
	bool switched = false; //used to stop other if statements from executing

	if (m_holdingRifle && !switched) {
		m_holdingRifle = false;
		m_holdingShotgun = true;
		m_currentWeaponText.setString("Current Weapon: Shotgun");
		switched = true;
	}
	if (m_holdingShotgun && !switched) {
		m_currentWeaponText.setString("Current Weapon: Sniper");
		m_holdingSniper = true;
		m_holdingShotgun = false;
		switched = true;
	}
	if (m_holdingSniper && !switched) {
		m_currentWeaponText.setString("Current Weapon: Rifle");
		m_holdingRifle = true;
		m_holdingSniper = false;
		switched = true;
	}
	
}

void GamePlay::checkPlayerLife()
{
	if (m_player.getLives() <= 0)
	{
		finalScore = m_scoreNumber;
		m_buttonTexts[0].setString("Score: " + std::to_string(finalScore));
		m_gameOver = true;
	}
}

void GamePlay::resetGame()
{
	m_currentNumberOfEnemies = 0;
	m_currentNumberOfRangedEnemies = 0;
	m_playerLocation = { Game::s_screenWidth / 2.0f, Game::s_screenHeight / 2.0f };
	isReloading = false;
	m_bulletsShot = 0;
	m_player.setLives(Player::MAX_PLAYER_LIVES);
	m_playerLifeText.setString("Lives: " + std::to_string(m_player.getLives()));
	m_scoreNumber = 0;
	m_gameOver = false;
	m_scoreText.setString("Score ");
}

void GamePlay::moveCamera()
{
	//playerView.setCenter(m_player.getLocation().x, m_player.getLocation().y);///experimental
}

void GamePlay::tickTimers()
{
	m_shotgunShootDelay = m_shotgunShootDelay - m_shotgunFireRate;
	m_rifleShootDelay = m_rifleShootDelay - m_rifleFireRate;
	m_sniperShootDelay = m_sniperShootDelay - m_sniperFireRate;
	meleeZombieSpawnCounter = meleeZombieSpawnCounter - frameDecrement;
	rangedZombieSpawnCounter = rangedZombieSpawnCounter - frameDecrement;
	if (isReloading)
		reloadTime = reloadTime - frameDecrement;
	
}











