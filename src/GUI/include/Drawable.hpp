#pragma once

#include "IDrawable.hpp"
#include "SFML/Graphics.hpp"

namespace un {
	class Drawable : public IDrawable {
		protected:
			void CenterView (sf::RenderTarget& window);
		public:
			~Drawable () override {}

			float GetWidth () const override = 0;
			float GetHeight () const override = 0;
			void Draw (sf::RenderTarget& window, int windowX, int windowY) override = 0;
	};
}

