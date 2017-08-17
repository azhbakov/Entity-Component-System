//
// Created by marting422 on 12.08.17.
//

#ifndef GAME_IINTERACTABLEGRAPHICS_HPP
#define GAME_IINTERACTABLEGRAPHICS_HPP

#include <src/GUI/include/IDrawable.hpp>
#include <src/GUI/include/IMouseListener.hpp>

namespace un {

	class IInteractableGraphics : public IDrawable, public IMouseListener {
		public:
			~IInteractableGraphics() = default;

			/* IDrawable */
			virtual float GetWidth () const = 0;
			virtual float GetHeight () const = 0;
			virtual void Draw (sf::RenderTarget& window, int windowX, int windowY) = 0;

			/* IMouseListener */
			virtual void CheckMouseEvent(sf::Window &window, int windowX, int windowY) = 0;
	};

}

#endif //GAME_IINTERACTABLEGRAPHICS_HPP
