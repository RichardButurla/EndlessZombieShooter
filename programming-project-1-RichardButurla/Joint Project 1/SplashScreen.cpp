#include "SplashScreen.h"
#include "Game.h"

SplashScreen::SplashScreen()
{
}

SplashScreen::~SplashScreen()
{
}

void SplashScreen::initialise(sf::Font& t_font)
{
	m_font = t_font;
	m_splashText.setFont(m_font);
	m_splashText.setCharacterSize(40U);
	m_splashText.setStyle(sf::Text::Bold);
	m_splashText.setFillColor(sf::Color::Black);
	m_splashText.setOutlineColor(sf::Color::Red);
	m_splashText.setString("Press Any Key To Continue");

	sf::FloatRect textSize = m_splashText.getGlobalBounds();
	float xPosition = (Game::s_screenWidth / 2) - (textSize.width / 2.0f); //gets middle of text and gets middle of screen co-ords
	float yPosition = (Game::s_screenHeight / 2);
	m_splashText.setPosition(xPosition, yPosition); //places in middle of screen;

}

void SplashScreen::update(sf::Time& t_deltaTime)
{
	if (m_anyKeyPressed)
	{
		Game::currentState = GameState::MainMenu;
		m_anyKeyPressed = !m_anyKeyPressed;
	}
}

//called from main game loop
void SplashScreen::processInput(sf::Event& t_event)
{

	if (sf::Event::KeyPressed == t_event.type)
	{

		m_anyKeyPressed = true;
	}
}

void SplashScreen::render(sf::RenderWindow& t_window)
{
	t_window.draw(m_splashBackground);
	t_window.draw(m_splashText);
}
