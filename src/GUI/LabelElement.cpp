#include "LabelElement.hpp"

using namespace un;

void LabelElement::UpdateGUIElement () {
	sf::Vector2i pixelCoord = uvToPixels(_uv);
	_label.Draw (_window, pixelCoord.x, pixelCoord.y);
}

//void LabelElement::CheckMouseEvent() {
//
//}