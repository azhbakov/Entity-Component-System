#pragma once

#include "SFML/Graphics.hpp"

namespace un {
	class IDrawable {
		public:
			virtual ~IDrawable () = default;
			virtual float GetWidth () const = 0;
			virtual float GetHeight () const = 0;
			virtual void Draw (sf::RenderTarget& window, int windowX, int windowY) = 0;
			//virtual void Draw (sf::RenderWindow& window, sf::IntRect fromRect, sf::IntRect toRect) = 0;
	};
}

