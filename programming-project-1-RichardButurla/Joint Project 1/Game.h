/// <summary>
/// Richard Buturla
/// </summary>
#ifndef GAME_HPP
#define GAME_HPP
/// <summary>
/// include guards used so we don't process this file twice
/// same as #pragma once
/// Don't forget the endif at the bottom
/// </summary>
#include <SFML/Graphics.hpp>
#include "LicenseScreen.h"
#include "SplashScreen.h"
#include "MainMenu.h"
#include "Help.h"
#include "GamePlay.h"
#include "Player.h"


/// <summary>
/// different states for game
/// </summary>
enum class
	GameState
{
	None,
	License,
	Splash,
	MainMenu,
	Help,
	Game
};

class Game
{

public:
	Game();
	~Game();
	/// <summary>
	/// main method for game
	/// </summary>
	void run();
	static float s_screenWidth;
	static float s_screenHeight;
	static GameState currentState;

protected:

	void processEvents();
	void processKeys(sf::Event t_event);
	void update(sf::Time t_deltaTime);
	void render();

	void initialiseScreens();

	sf::RenderWindow m_window; // main SFML window
	sf::Font m_ArialBlackfont; // font used by message
	sf::Text m_welcomeMessage; // text used for message on screen

	LicenseScreen s_licenseScreen;
	SplashScreen s_splashScreen;
	MainMenu s_mainMenuScreen;
	Help s_helpScreen;
	GamePlay s_gamePlayScreen;


	bool m_exitGame; // control exiting game

};

#endif // !GAME_HPP

