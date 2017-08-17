#include "MouseListener.hpp"

using namespace un;

/*void MouseListener::StatePress () {
}
void MouseListener::StateDrag () {
}
void MouseListener::StateIdle () {
}*/

void MouseListener::UpdateMouseState() {
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