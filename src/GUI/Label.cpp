#include "Label.hpp"
#include <iostream>

#include <SFML/Graphics.hpp>

using namespace un;
using namespace std;

void Label::Draw (sf::RenderTarget& window, int windowX, int windowY) {
	//CenterView(window);
	sf::View centerView (sf::FloatRect(0, 0,
		window.getView().getSize().x, window.getView().getSize().y));
	window.setView(centerView);

	_text.setColor(sf::Color(100, 250, 50));
	_text.setPosition (windowX, windowY);

	window.draw(_text);

}
