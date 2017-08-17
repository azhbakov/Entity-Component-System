//
// Created by marting422 on 11.08.17.
//

#include <src/Game/include/Component.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <src/GUI/include/Image.hpp>

using namespace un;

void Image::Draw(sf::RenderTarget &window, int windowX, int windowY) {
	CenterView(window);
	_image.setPosition(windowX, windowY);
	window.draw(_image);
}