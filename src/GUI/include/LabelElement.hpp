#pragma once

#include <string>

#include "GUIElement.hpp"
#include "Label.hpp"
#include "IMouseListener.hpp"

namespace un {

	class LabelElement : public GUIElement/*, public IMouseListener*/ {
		private:
			Label _label;
		public:
			LabelElement (sf::RenderWindow& window, float uvX, float uvY, std::string text, const sf::Font& font, unsigned int characterSize = 30)
				: GUIElement(window, uvX, uvY), _label(text, font, characterSize) {}
			virtual ~LabelElement () {}

			/* GUI Element*/
			void UpdateGUIElement () override;
			virtual std::string ToString () const { return "Label"; }

			/* IMouseListener */
			//void CheckMouseEvent (const sf::Window& window) override;
	};

}