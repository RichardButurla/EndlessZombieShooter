#include "LicenseScreen.h"
#include "Game.h"


LicenseScreen::LicenseScreen()
{
}

LicenseScreen::~LicenseScreen()
{
}

void LicenseScreen::initialise(sf::Font& t_font)
{
	m_font = t_font;
	m_text.setFont(m_font);
	m_text.setCharacterSize(40U);
	m_text.setFillColor(sf::Color::Black);
	m_text.setString("Developed by Richie Studios");

	sf::FloatRect textSize = m_text.getGlobalBounds();
	float xPosition = Game::s_screenWidth / 2.0f - textSize.width / 2; //middle of text put on middle of screen
	float yPosisiton = Game::s_screenHeight * 0.25;
	m_text.setPosition(xPosition, yPosisiton);
	m_licenseTime = sf::seconds(0);
}

void LicenseScreen::update(sf::Time& t_deltaTime)
{
	m_licenseTime += t_deltaTime; //receives game loop time.
	if (m_licenseTime.asSeconds() > 2.0f)
	{
		Game::currentState = GameState::Splash;
	}
}

void LicenseScreen::render(sf::RenderWindow& t_window)
{
	t_window.draw(m_text);
}

