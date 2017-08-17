//
// Created by marting422 on 12.08.17.
//

#ifndef GAME_INTERACTABLEGRAPHICS_HPP
#define GAME_INTERACTABLEGRAPHICS_HPP

#include "IInteractableGraphics.hpp"

namespace un {

	enum MouseState {
		Press, Drag, Idle
	};

	class InteractableGraphics : public IInteractableGraphics {
		protected:
			/* Drawable */
			void CenterView (sf::RenderTarget& window);
			/* Mouse Listener */
			MouseState _mouseState;
			void UpdateMouseState();
		public:
			/* IDrawable */
			virtual float GetWidth () const override = 0;
			virtual float GetHeight () const override = 0;
			virtual void Draw (sf::RenderTarget& window, int windowX, int windowY) override = 0;

			/* IMouseListener */
			virtual void CheckMouseEvent(sf::Window &window, int windowX, int windowY) override {};
	};

}

#endif //GAME_INTERACTABLEGRAPHICS_HPP
