#pragma once

#include "Component.hpp"
#include "ComponentsEnum.hpp"
#include "IGUIElement.hpp"
#include <SFML/Graphics.hpp>

namespace un {

	class GUIElement : public IGUIElement {
		protected:
			sf::RenderWindow& _window;
			sf::Vector2f _uv;

			sf::Vector2i uvToPixels (sf::Vector2f uv);
		public:
			GUIElement (sf::RenderWindow& window) : GUIElement(window, 0, 0) {}
			GUIElement (sf::RenderWindow& window, float uvX, float uvY)
				: _window (window), _uv(uvX, uvY) {}
			~GUIElement () override {}

			/* IGUIElement */
			void SetPositionUV (float uvX, float uvY) { _uv.x = uvX; _uv.y = uvY; }
			sf::Vector2f GetPositionUV () const { return _uv; };

			void UpdateGUIElement () override = 0;
			std::string ToString () const override = 0;

	};

}