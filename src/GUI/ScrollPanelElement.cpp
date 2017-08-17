//
// Created by marting422 on 08.08.17.
//

#include <src/Game/include/Component.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <src/GUI/include/ScrollPanelElement.hpp>

using namespace un;

void ScrollPanelElement::UpdateGUIElement() {
	sf::Vector2i pixelCoord = uvToPixels (_uv);

	_scrollPanel.CheckMouseEvent (_window, pixelCoord.x, pixelCoord.y);

	_scrollPanel.Draw (_window, pixelCoord.x, pixelCoord.y);

}