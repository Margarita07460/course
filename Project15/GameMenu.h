#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

void menu(RenderWindow& window) {
	using namespace sf;

	Font font;
	if (!font.loadFromFile("BAMEW-ThinPersonalUse.otf"))
	{
		//error;
	}

Texture menuBackground;
menuBackground.loadFromFile("tex.png");
Sprite Bg(menuBackground);


Text txt, txt2;
txt.setFont(font);
txt2.setFont(font);
std::string userPointsString = "PLAY";
std::string esc = "EXIT";
txt.setString(userPointsString);
txt2.setString(esc);

txt.setCharacterSize(56);
txt2.setCharacterSize(56);


txt.setFillColor(sf::Color::Black);
txt2.setFillColor(sf::Color::Black);

txt.setStyle(sf::Text::Bold | sf::Text::Underlined);
txt2.setStyle(sf::Text::Bold | sf::Text::Underlined);

txt.setPosition(190.f, 10.f);
txt2.setPosition(190.f, 100.f);


bool isMenu = 1;
int menuNum = 0;
Bg.setPosition(0, 0);


while (isMenu)
{
	menuNum = 0;
	window.clear(Color(78, 181, 221));

	if (IntRect(100, 30, 300, 50).contains(Mouse::getPosition(window))) { txt.setFillColor(sf::Color::Black); menuNum = 1; }
	if (IntRect(100, 90, 300, 50).contains(Mouse::getPosition(window))) { txt2.setFillColor(sf::Color::Black); menuNum = 2; }
	

	if (Mouse::isButtonPressed(Mouse::Left))
	{
		if (menuNum == 1) isMenu = false;
		if (menuNum == 2) { window.close(); isMenu = false; }
	

	}
	window.draw(Bg);
	window.draw(txt);
	window.draw(txt2);
	window.display();
}

}