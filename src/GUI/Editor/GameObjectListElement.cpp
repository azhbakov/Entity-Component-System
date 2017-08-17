//
// Created by marting422 on 12.08.17.
//

#include <sstream>
#include <src/GUI/Editor/include/GameObjectListElement.hpp>
#include <src/Game/include/ResourceManager.hpp>

using namespace un;
using namespace std;

GameObjectListElement::GameObjectListElement (sf::RenderWindow &window,
                               std::vector<std::weak_ptr<GameObject>> &gameObjects)
		: GUIElement(window), _gameObjects(gameObjects) {
	_scrollPanel.SetContent(&_boxLayout);
	for (auto g : gameObjects) {
		AddGameObjectLabel(g);
	}
}

GameObjectListElement::~GameObjectListElement () {
	for (auto l : _labels) {
		delete l;
	}
}

void GameObjectListElement::AddGameObjectLabel (std::weak_ptr<GameObject> g) {
	if (g.expired()) {
		cerr << "Failed to initialize GameObject entry in Editor!" << endl;
	}

	stringstream labelTextStream;
	labelTextStream << "Name: " << g.lock()->GetName() << endl;
	labelTextStream << "Tags: " << g.lock()->GetTag() << endl;

	Label *newLabel = new Label (labelTextStream.str(), ResourceManager::Instance().GetFont("DejaVu"), GAMEOBJECT_LIST_FONT_SIZE);
	_boxLayout.AddComponent(newLabel);
	_labels.push_back(newLabel);
}

void GameObjectListElement::SetWidth (int width) { _scrollPanel.SetWidth(width); }
void GameObjectListElement::SetHeight (int height) { _scrollPanel.SetHeigth(height); }

void GameObjectListElement::UpdateGUIElement () {
	sf::Vector2i pixelPos = uvToPixels(_uv);
	_scrollPanel.Draw(_window, pixelPos.x, pixelPos.y);
}