

#include "Game.h"
#include <iostream>

//defined here because the data members are statics
float Game::s_screenWidth = 1500;
float Game::s_screenHeight = 800;
GameState Game::currentState = GameState::License;

/// <summary>
/// default constructor
/// setup the window properties
/// load and setup the text 
/// load and setup thne image
/// </summary>

Game::Game() :
	m_window{ sf::VideoMode{ static_cast<unsigned int>(s_screenWidth), static_cast<unsigned int>(s_screenHeight) }, "SFML Game" },
	m_exitGame{ false } //when true game will exit
{

	initialiseScreens();

}

/// <summary>
/// default destructor we didn't dynamically allocate anything
/// so we don't need to free it, but mthod needs to be here
/// </summary>
Game::~Game()
{
}


/// <summary>
/// main game loop
/// update 60 times per second,
/// process update as often as possible and at least 60 times per second
/// draw as often as possible but only updates are on time
/// if updates run slow then don't render frames
/// </summary>
void Game::run()
{

	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	const float fps{ 60.0f };
	sf::Time timePerFrame = sf::seconds(1.0f / fps); // 60 fps
	while (m_window.isOpen())
	{
		processEvents(); // as many as possible
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > timePerFrame)
		{
			timeSinceLastUpdate -= timePerFrame;
			processEvents(); // at least 60 fps
			update(timePerFrame); //60 fps
		}
		render(); // as many as possible
	}
}
/// <summary>
/// handle user and system events/ input
/// get key presses/ mouse moves etc. from OS
/// and user :: Don't do game update here
/// </summary>
void Game::processEvents()
{
	sf::Event newEvent;
	while (m_window.pollEvent(newEvent))
	{
		if (sf::Event::Closed == newEvent.type) // window message
		{
			m_exitGame = true;
		}


		switch (currentState)
		{
		case GameState::None:
			break;
		case GameState::License:
			//no process events in license
			break;
		case GameState::Splash:
			s_splashScreen.processInput(newEvent);
			break;
		case GameState::MainMenu:
			//no event processing method except for update
			break;
		case GameState::Help:
			s_helpScreen.processInput(newEvent);
			break;
		case GameState::Game:
			s_gamePlayScreen.processEvents(newEvent);
			break;
		default:
			break;
		}
	}
}


/// <summary>
/// deal with key presses from the user
/// </summary>
/// <param name="t_event">key press event</param>
void Game::processKeys(sf::Event t_event)
{
	if (sf::Keyboard::Escape == t_event.key.code)
	{
		m_exitGame = true;
	}
}

/// <summary>
/// Update the game world
/// </summary>
/// <param name="t_deltaTime">time interval per frame</param>
void Game::update(sf::Time t_deltaTime)
{
	if (m_exitGame)
	{
		m_window.close();
	}
	switch (currentState)
	{
	case GameState::None:
		break;
	case GameState::License:
		s_licenseScreen.update(t_deltaTime);
		break;
	case GameState::Splash:
		s_splashScreen.update(t_deltaTime);
		break;
	case GameState::MainMenu:
		s_mainMenuScreen.update(t_deltaTime, m_window);
		break;
	case GameState::Help:
		s_helpScreen.update(t_deltaTime);
		break;
	case GameState::Game:
		s_gamePlayScreen.update(t_deltaTime);
		break;
	default:
		break;
	}
}

/// <summary>
/// draw the frame and then switch buffers
/// </summary>
void Game::render()
{
	m_window.clear(sf::Color::Blue);

	switch (currentState)
	{
	case GameState::None:
		break;
	case GameState::License:
		s_licenseScreen.render(m_window);
		break;
	case GameState::Splash:
		s_splashScreen.render(m_window);
		break;
	case GameState::MainMenu:
		s_mainMenuScreen.render(m_window);
		break;
	case GameState::Help:
		s_helpScreen.render(m_window);
		break;
	case GameState::Game:
		s_gamePlayScreen.render(m_window);
		break;
	default:
		break;
	}
	m_window.display();
}

void Game::initialiseScreens()
{
	if (!m_ArialBlackfont.loadFromFile("ASSETS\\FONTS\\ariblk.ttf"))
	{
		std::cout << "problem loading arial black font" << std::endl;
	}
	m_welcomeMessage.setFont(m_ArialBlackfont);

	s_licenseScreen.initialise(m_ArialBlackfont);
	s_splashScreen.initialise(m_ArialBlackfont);
	s_mainMenuScreen.initialise(m_ArialBlackfont);
	s_helpScreen.initialise(m_ArialBlackfont);
	s_gamePlayScreen.initialise(m_ArialBlackfont);
}


