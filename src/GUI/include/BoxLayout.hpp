//
// Created by marting422 on 11.08.17.
//

#ifndef GAME_BOXLAYOUT_HPP
#define GAME_BOXLAYOUT_HPP

#include <src/GUI/include/InteractableGraphics.hpp>

namespace un {

	enum ElementOrientation { Vertical, Horizontal };

	class BoxLayout : public InteractableGraphics {
		private:
			std::vector<IInteractableGraphics *> _content;
			ElementOrientation _orientation;
		public:
			BoxLayout (ElementOrientation orientation = Vertical) : _orientation(orientation) {}
			~BoxLayout () override {}

			void SetOrientation (ElementOrientation orientation) { _orientation = orientation; }

			void AddComponent (IInteractableGraphics *d);
			void RemoveComponent (IInteractableGraphics *d);

			/* Drawable */
			float GetWidth () const override;
			float GetHeight () const override;
			virtual void Draw (sf::RenderTarget& window, int windowX, int windowY);

			/* MouseListener */
			void CheckMouseEvent (sf::Window& window, int windowX, int windowY) override;
	};
}


#endif //GAME_BOXLAYOUT_HPP
