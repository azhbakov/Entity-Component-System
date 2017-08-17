#include "Drawable.hpp"

using namespace un;
using namespace std;

void Drawable::CenterView (sf::RenderTarget& window) {
	sf::View centerView (sf::FloatRect(0, 0,
		window.getView().getSize().x, window.getView().getSize().y));
	window.setView(centerView);
}
