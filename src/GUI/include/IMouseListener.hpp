#ifndef GAME_IMOUSELISTENER_HPP
#define GAME_IMOUSELISTENER_HPP

#include <SFML/Graphics.hpp>

namespace un {

	class IMouseListener {
		public:
			virtual ~IMouseListener () = default;
			virtual void CheckMouseEvent(sf::Window &window, int windowX, int windowY) = 0;
	};

}

#endif //GAME_IMOUSELISTENER_HPP
