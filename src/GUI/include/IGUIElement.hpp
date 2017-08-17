#pragma once

#include <string>

namespace un {
	class IGUIElement {
		public:
			virtual ~IGUIElement () = default;

			virtual void SetPositionUV (float uvX, float uvY) = 0;
			virtual sf::Vector2f GetPositionUV () const = 0;

			virtual void UpdateGUIElement () = 0;
			virtual std::string ToString () const = 0;
	};
}