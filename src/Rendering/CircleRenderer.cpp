#include "CircleRenderer.hpp"

using namespace un;
using namespace std;

CircleRenderer::CircleRenderer (std::weak_ptr<GameObject>& g, int sortingOrder, float radius)
	: Renderer(g, sortingOrder), _circle(radius), _extending(true) {
		_circle.setFillColor(sf::Color::Red);
	}

void CircleRenderer::UpdateRenderer () {
	Renderer::UpdateRenderer();

	if (_extending) {
		_circle.setRadius (_circle.getRadius()+1);
	} else {
		_circle.setRadius (_circle.getRadius()-1);
	}
	if (_circle.getRadius() <= 0) {
		_extending = true;
	} else if (_circle.getRadius() >= 30) {
		_extending = false;
	}
}

const sf::Drawable& CircleRenderer::GetRenderData () const {
	return _circle;
}

sf::Transformable& CircleRenderer::GetTransformData() {
	return _circle;
}
