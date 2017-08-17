
#include "GUISubsystem.hpp"

void un::GUISubsystem::RegisterGUIElement(un::IGUIElement *element) {
	_guiElements.push_back (element);

	#ifdef SIMPLE_LOGGER
		LOG ({"Game"}, "Registered GUI element " + element->ToString() + ".");
	#endif
}

void un::GUISubsystem::UpdateGUIElements() {
	#ifdef SIMPLE_LOGGER
		LOG ({"Game", "GUI Rendering"}, "Updating GUI elements...");
	#endif

	for (auto it = _guiElements.begin(); it != _guiElements.end(); it++) {
		#ifdef SIMPLE_LOGGER
			LOG ({"Game", "GUI Rendering"}, "Updating GUI element " + (*it)->ToString() + "...");
		#endif

		(*it)->UpdateGUIElement ();

		#ifdef SIMPLE_LOGGER
			LOG ({"Game", "GUI Rendering"}, "GUI element " + (*it)->ToString() + " updated.");
		#endif
	}

	#ifdef SIMPLE_LOGGER
		LOG ({"Game", "GUI Rendering"}, "GUI elements updated.");
	#endif
}
