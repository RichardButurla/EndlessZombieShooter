#pragma once
#include <SFML/Graphics.hpp>


class LicenseScreen
{
public:
	LicenseScreen();
	~LicenseScreen();

	void initialise(sf::Font& t_font);
	void update(sf::Time& t_deltaTime);
	void render(sf::RenderWindow& t_window);

protected:
	sf::Font m_font;
	sf::Text m_text;
	sf::Time m_licenseTime;

};