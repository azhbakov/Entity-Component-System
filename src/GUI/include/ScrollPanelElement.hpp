#ifndef GAME_SCROLLPANELELEMENT_HPP
#define GAME_SCROLLPANELELEMENT_HPP

#include "GUIElement.hpp"
#include "ScrollPanel.hpp"

namespace un {

	class ScrollPanelElement : public GUIElement {
	private:
		ScrollPanel _scrollPanel;
	public:
		ScrollPanelElement (sf::RenderWindow& window, float uvX, float uvY, int panelWidth, int panelHeight)
			: GUIElement(window, uvX, uvY), _scrollPanel(panelWidth, panelHeight) {}
		~ScrollPanelElement () override {}

		ScrollPanel& GetScrollPanel() { return _scrollPanel; }

		void UpdateGUIElement ();
		virtual std::string ToString () const { return "Scroll Panel"; }
	};

}

#endif //GAME_SCROLLPANELELEMENT_HPP
