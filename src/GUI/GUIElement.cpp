#include "GUIElement.hpp"

using namespace un;

sf::Vector2i GUIElement::uvToPixels (sf::Vector2f uv) {
	int windowX = _window.getView().getSize().x * uv.x;
	int windowY = _window.getView().getSize().y * uv.y;
	return sf::Vector2i(windowX, windowY);
}