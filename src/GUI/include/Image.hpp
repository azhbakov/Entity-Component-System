//
// Created by marting422 on 11.08.17.
//

#ifndef GAME_IMAGE_HPP
#define GAME_IMAGE_HPP

#include <src/GUI/include/InteractableGraphics.hpp>

namespace un {

	class Image : public InteractableGraphics {
		private:
			sf::Sprite _image;
		public:
			Image (sf::Sprite image)
					: _image(image) {}
			~Image () override {}

			float GetWidth () const override { return _image.getGlobalBounds().width; }
			float GetHeight () const override { return _image.getGlobalBounds().height; }
			virtual void Draw (sf::RenderTarget& window, int windowX, int windowY);
	};

}

#endif //GAME_IMAGE_HPP
