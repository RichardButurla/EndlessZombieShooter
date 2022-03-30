#include "MainMenu.h"
#include "Game.h"
#include <iostream>

MainMenu::MainMenu()
{
}

MainMenu::~MainMenu()
{
}

void MainMenu::initialise(sf::Font& t_font)
{
	m_topOffset = Game::s_screenHeight / 8; //change if bad scaling
	m_verticalSpacing = Game::s_screenHeight / 4;
	m_buttonWidth = Game::s_screenWidth / 2; //change if bad scaling
	m_leftOffset = (Game::s_screenWidth - m_buttonWidth) / 2;
	m_buttonHeight = Game::s_screenHeight / 8; //change if bad scaling
	int textDropOffset = Game::s_screenHeight / 6.5;

	sf::String m_menuTexts[] = { "Play","Help","Exit" };

	m_font = t_font;
	if (!m_buttonTexture.loadFromFile("ASSETS/IMAGES/MenuButtons.jpg"))
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
}


void MainMenu::update(sf::Time& t_deltaTime, sf::Window& t_window)
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
	{
		sf::Vector2i mousePosition = sf::Mouse::getPosition(t_window);//integer vector since window is positive

		if (mousePosition.x > m_leftOffset && mousePosition.x < m_leftOffset + m_buttonWidth) //checks all x positions since buttons are equally distanced
		{
			if (mousePosition.y > m_topOffset && mousePosition.y && mousePosition.y < m_topOffset + m_buttonHeight) //checks between first button's y positions. (change later ,if statement wrong)
				Game::currentState = GameState::Game;

			if (mousePosition.y > m_topOffset + m_verticalSpacing && mousePosition.y < m_topOffset + m_verticalSpacing + m_buttonHeight) //verticalSpacing * index + buttonheight can be used for multiple buttons
				Game::currentState = GameState::Help;

			if (mousePosition.y > m_topOffset + m_verticalSpacing * 2 && mousePosition.y < m_topOffset + m_verticalSpacing * 2 + m_buttonHeight)
				t_window.close();
		}
	}
}

void MainMenu::render(sf::RenderWindow& t_window)
{
	for (int i = 0; i < m_numberOfButtons; i++)
	{
		t_window.draw(m_buttonsSprites[i]);
		t_window.draw(m_buttonTexts[i]);
	}


}
