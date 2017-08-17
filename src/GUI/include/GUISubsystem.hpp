#ifndef GAME_GUISUBSYSTEM_HPP
#define GAME_GUISUBSYSTEM_HPP

#include <src/GUI/include/IGUIElement.hpp>
#include <vector>

namespace un {

	class GUISubsystem {
		private:
			std::vector<IGUIElement *> _guiElements;
		public:
			void RegisterGUIElement (IGUIElement *element);
			void UpdateGUIElements ();
	};
}


#endif //GAME_GUISUBSYSTEM_HPP
