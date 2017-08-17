#include "MovementScript.hpp"

#include <SFML/Graphics.hpp>

using namespace un;

void MovementScript::Update () {
	float dx = 0;
	float dy = 0;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		dx -= _speed;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		dx += _speed;
	} 
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		dy -= _speed;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
		dy += _speed;
	}

	GetTransform().Translate(dx, dy);
}