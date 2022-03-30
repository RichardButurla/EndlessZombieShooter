#include "Help.h"
#include "Game.h"

Help::Help()
{
}

Help::~Help()
{
}

void Help::initialise(sf::Font& t_font)
{
	m_font = t_font;

	m_font = t_font;
	m_helpText.setFont(m_font);
	m_helpText.setCharacterSize(40U);
	m_helpText.setStyle(sf::Text::Bold);
	m_helpText.setFillColor(sf::Color::Black);
	m_helpText.setOutlineColor(sf::Color::Red);
	m_helpText.setString("Aim with mouse.\n Shoot with Left Click.\n Move with WASD\n Kill zombies to earn score.\n Surivive as long as you can!");

	sf::FloatRect textSize = m_helpText.getGlobalBounds();
	float xPosition = (Game::s_screenWidth / 2) - (textSize.width / 2.0f); //gets middle of text and gets middle of screen co-ords
	float yPosition = (Game::s_screenHeight / 3);
	m_helpText.setPosition(xPosition, yPosition);
}

void Help::processInput(sf::Event& t_event)
{
	if (sf::Event::KeyPressed == t_event.type)
	{
		if (sf::Keyboard::Escape == t_event.key.code)
		{
			m_exitPressed = true;
		}
	}
}

void Help::update(sf::Time& t_deltatime)
{
	if (m_exitPressed)
	{
		Game::currentState = GameState::MainMenu;
	}
	m_exitPressed = false;
}

void Help::render(sf::RenderWindow& t_window)
{
	t_window.draw(m_helpText);
}
