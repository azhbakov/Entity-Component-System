//
// Created by marting422 on 12.08.17.
//

#ifndef GAME_GAMEOBJECTLIST_HPP
#define GAME_GAMEOBJECTLIST_HPP

#include <src/Game/include/Component.hpp>
#include <src/GUI/include/GUIElement.hpp>
#include <src/GUI/include/Label.hpp>
#include <src/GUI/include/BoxLayout.hpp>
#include <src/GUI/include/ScrollPanel.hpp>

#define GAMEOBJECT_LIST_FONT_SIZE 30

namespace un {

	class GameObjectListElement : public GUIElement {
		private:
			std::vector<std::weak_ptr<GameObject>>& _gameObjects;
			std::vector<Label *> _labels;

			BoxLayout _boxLayout;
			ScrollPanel _scrollPanel;

			void AddGameObjectLabel (std::weak_ptr<GameObject> g);
		public:
			GameObjectListElement (sf::RenderWindow& window,
			                std::vector<std::weak_ptr<GameObject>>& gameObjects);
			~GameObjectListElement () override;

			void SetWidth (int width);
			void SetHeight (int height);

			/* GUIElement */
			void UpdateGUIElement () override = 0;
			std::string ToString () const override { return "GameObjects List"; };
	};

}

#endif //GAME_GAMEOBJECTLIST_HPP
