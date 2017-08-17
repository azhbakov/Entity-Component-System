#ifndef GAME_MOUSELISTENER_HPP
#define GAME_MOUSELISTENER_HPP

#include "IMouseListener.hpp"

namespace un {

	enum MouseState {
		Press, Drag, Idle
	};

	class MouseListener : public IMouseListener {
		/*private:
			void StatePress ();
			void StateDrag ();
			void StateIdle ();
			bool _firstPress;*/
		protected:
			MouseState _mouseState;
			void UpdateMouseState();
		public:
			MouseListener () = default;
			~MouseListener () = default;
			void CheckMouseEvent(sf::Window &window, int windowX, int windowY) override = 0;
	};

}

#endif //GAME_MOUSELISTENER_HPP
