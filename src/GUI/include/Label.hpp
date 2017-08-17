#pragma once

#include <string>

#include <SFML/Graphics.hpp>
#include <src/GUI/include/InteractableGraphics.hpp>

namespace un {

	class Label : public InteractableGraphics {
		private:
			//int _width, _height;
			sf::Text _text;
		public:
			Label (std::string text, const sf::Font& font, unsigned int characterSize = 30)
				: _text(text, font, characterSize) {}
			~Label () override {}

			/*virtual float SetWidth () { return _width; }
			virtual float SetHeigth () { return _height; }*/

			float GetWidth () const override { return _text.getLocalBounds().left+_text.getLocalBounds().width; }
			float GetHeight () const override { return _text.getLocalBounds().top+_text.getLocalBounds().height; }
			virtual void Draw (sf::RenderTarget& window, int windowX, int windowY);
	};

}