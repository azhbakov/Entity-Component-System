#pragma once

#include "GUIElement.hpp"

namespace un {

	class SceneContent : public GUIElement {
		private:

		public:
			SceneContent (sf::RenderWindow& window) : GUIElement (window) {}
			~SceneContent () {}
			void UpdateGUIElement () {}
	}

}