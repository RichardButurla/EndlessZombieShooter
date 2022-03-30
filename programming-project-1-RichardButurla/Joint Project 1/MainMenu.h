#pragma once
#include <SFML/Graphics.hpp>
class MainMenu
{
public:
	MainMenu();
	~MainMenu();

	void initialise(sf::Font& t_font);
	void update(sf::Time& t_deltaTime, sf::Window& t_window);
	void render(sf::RenderWindow& t_window);

protected:
	//amount of buttons,buttons as sprites and font
	static const int m_numberOfButtons = 3;
	sf::Sprite m_buttonsSprites[m_numberOfButtons];
	sf::Texture m_buttonTexture;
	sf::Text m_buttonTexts[m_numberOfButtons];
	sf::Font m_font;

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

