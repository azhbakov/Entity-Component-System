#include <SFML/Graphics.hpp>

#include "Game.hpp"
#include "SFMLGame.hpp"
#include "ResourceManager.hpp"

namespace un {

	class Loader {
		public:
			static int RenderTest (Game& game, sf::RenderWindow& window, ResourceManager& _resourceManager);
			static int Box2DTest (SFMLGame& game);
	};

}