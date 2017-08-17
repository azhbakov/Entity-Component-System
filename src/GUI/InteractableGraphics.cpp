//
// Created by marting422 on 12.08.17.
//

#include "IInteractableGraphics.hpp"
#include "InteractableGraphics.hpp"

using namespace un;

void InteractableGraphics::CenterView (sf::RenderTarget& window) {
	sf::View centerView (sf::FloatRect(0, 0,
	                                   window.getView().getSize().x, window.getView().getSize().y));
	window.setView(centerView);
}


void InteractableGraphics::UpdateMouseState() {
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		switch (_mouseState) {
			case Idle:
				_mouseState = Press;
				break;
			case Press:
				_mouseState = Drag;
				break;
			case Drag:
				break;
		}
	} else {
		_mouseState = Idle;
	}
}
