#include <vector>
#include <memory>
#include <algorithm>

#include "Box2DWorld.hpp"
#include "WeakPtrStorage.hpp"
#include "Game.hpp"
#include "GameObject.hpp"

#include "UnException.hpp"

#ifdef ENABLE_LOG
	#include "Logger.hpp"
#endif

using namespace un;
using namespace std;


Game::~Game () {
}

Game& Game::Instance () {
	static Game _instance;
	return _instance;
}

weak_ptr<GameObject> Game::Instantiate (string name) {
	return Instantiate (name, 0, 0);
}

weak_ptr<GameObject> Game::Instantiate (float worldX, float worldY) {
	return Instantiate ("GameObject", worldX, worldY);
}

weak_ptr<GameObject> Game::Instantiate (string name, float worldX, float worldY) {
	#ifdef SIMPLE_LOGGER
	LOG ({"Game"}, "GameObject instantiating: name==" + name + ", worldX==" + to_string(worldX) + ", worldY==" + to_string(worldY));
	#endif

	_gameObjectsToAdd.push_back (GameObject::CreateGameObject(name, worldX, worldY));
	
	#ifdef SIMPLE_LOGGER
	LOG ({"Game"}, "GameObject created and registered to instantiate: " + _gameObjectsToAdd.back()->GetName());
	#endif

	return weak_ptr<GameObject>(_gameObjectsToAdd.back());
}

void Game::Destroy (GameObject *g) {
	_gameObjectsToDestroy.push_back (g);

	#ifdef SIMPLE_LOGGER
		LOG ({"Game"}, "GameObject registered to remove: " + g->GetName());
    #endif
}

void Game::RegisterGUIElement (IGUIElement *element) {
	_guiElements.push_back (element);

	#ifdef SIMPLE_LOGGER
		LOG ({"Game"}, "Registered GUI element " + element->ToString() + ".");
	#endif
}

void Game::RegisterRenderer (std::weak_ptr<IRenderer> renderer) {
	_renderers.AddPointer (renderer);

	#ifdef SIMPLE_LOGGER
	LOG ({"Game"}, "Registered renderer " + renderer.lock()->ToString() + ".");
	#endif
}

void Game::RegisterCamera (std::weak_ptr<ICamera> camera) {
	_cameras.AddPointer (camera);
	
	#ifdef SIMPLE_LOGGER
	LOG ({"Game"}, "Registered camera " + camera.lock()->ToString() + ".");
	#endif
}

/*void Game::RemoveCamera () {
	std::vector<std::vector<weak_ptr<ICamera>>::iterator> toBeDeleted;
	for (auto i = _cameras.begin(); i != _cameras.end(); i++) {
		if (i->expired()) {
			toBeDeleted.push_back(i);		
		}
	}

	if (toBeDeleted.size() == 0) {
		#ifdef SIMPLE_LOGGER
			Logger::Instance().Log({"Game", "Error"}, "Trying to remove camera but no expired camera found!");
		#endif
		cerr << "Error! Trying to remove camera but no expired camera found!" << endl;
	} else {
		for (auto i : toBeDeleted) {
			_cameras.erase(i);
			#ifdef SIMPLE_LOGGER
				Logger::Instance().Log({"Game"}, "Removed camera");
			#endif
		}
	}
}*/

void Game::Start () {
	#ifdef SIMPLE_LOGGER
		Logger::Instance().Log({"Game"}, "Starting game");
	#endif

	for (shared_ptr<GameObject> g : _gameObjects) {
		g->Start();
	}
	_started = true;
}

void Game::Update () {
	#ifdef SIMPLE_LOGGER
	LOG ({"Game", "Tick"}, "################");
	#endif
	UpdateGameObjects ();
	UpdateRenderers ();
	UpdateCameras ();
	UpdateGUIElements ();
}

void Game::UpdateGameObjects () {
	for (shared_ptr<GameObject> g : _gameObjectsToAdd) {
		_gameObjects.push_back (g);
	}
	/* 
	 Two passes through _gameObjectsToAdd to guarantee initialization
	 in case when objects added on the same tick need to find each other during their Start routine
	 via FindObject.
	*/ 
	for (shared_ptr<GameObject> g : _gameObjectsToAdd) {
		g->Start();

		#ifdef SIMPLE_LOGGER
		LOG ({"Game"}, "GameObject completely instantiated: " + g->GetName());
		#endif
	}
	_gameObjectsToAdd.clear();

	for (GameObject *g : _gameObjectsToDestroy) {
		bool removed = false;
		for (auto i = _gameObjects.begin(); i < _gameObjects.end(); i++) {
			if ((*i).get() == g) {
				#ifdef SIMPLE_LOGGER
					Logger::Instance().Log({"Game"}, "GameObject removing:" + g->GetName());
					string nameOfDestroyed = g->GetName();
				#endif

				_gameObjects.erase (i);

				#ifdef SIMPLE_LOGGER
					Logger::Instance().Log({"Game"}, "GameObject removed: " + nameOfDestroyed);
				#endif

				removed = true;
				break;
			}
		}

		if (!removed) {
			#ifdef SIMPLE_LOGGER
				Logger::Instance().Log({"Game", "Error"}, "Failed to remove game object! No such object exists: " + g->GetName());
			#endif
			cerr << "Failed to remove game object! No such object exists." << endl; 
		}
	}
	_gameObjectsToDestroy.clear();	


	#ifdef SIMPLE_LOGGER
		LOG ({"Game"}, "Updating GameObjects...");
	#endif
	
	for (shared_ptr<GameObject> g : _gameObjects) {
		#ifdef SIMPLE_LOGGER
			LOG ({"Game"}, "Updating GameObject " + g->GetName() + "...");
		#endif

		g->Update();

		#ifdef SIMPLE_LOGGER
			LOG ({"Game"}, "GameObject updated " + g->GetName() + ".");
		#endif
	}

	#ifdef SIMPLE_LOGGER
		LOG ({"Game"}, "GameObjects updated.");
	#endif
}

void Game::UpdateRenderers () {
	#ifdef SIMPLE_LOGGER
		LOG ({"Game", "Rendering"}, "Updating renderers...");
	#endif
	
	_renderers.RemoveExpired ();

	for (auto it = _renderers->begin(); it != _renderers->end(); it++) {
		#ifdef SIMPLE_LOGGER
			LOG ({"Game", "Rendering"}, "Updating renderer " + it->lock()->ToString() + "...");
		#endif
		
		it->lock()->UpdateRenderer ();

		#ifdef SIMPLE_LOGGER
			LOG ({"Game", "Rendering"}, "Renderer " + it->lock()->ToString() + " updated.");
		#endif
	}

	#ifdef SIMPLE_LOGGER
		LOG ({"Game", "Rendering"}, "Renderers updated.");
	#endif
}

void Game::UpdateGUIElements () {
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

bool SortingComparator (const weak_ptr<IRenderer>& a, const weak_ptr<IRenderer>& b) {
	if (a.expired() || b.expired()) {
		
		#ifdef SIMPLE_LOGGER
			Logger::Instance().Log ({"Component", "Camera", "Error"}, "Error: Trying to compare expired IRenderer ptr in Camera!");
		#endif

		cerr << "Error: Trying to compare expired IRenderer ptr in Camera!" << endl;

		throw UnException("Error: Trying to compare expired IRenderer ptr in Camera!");
	}
	return a.lock()->GetSortingOrder() < b.lock()->GetSortingOrder();
}

void Game::UpdateCameras () {
	#ifdef SIMPLE_LOGGER
		Logger::Instance().Log({"Game", "Rendering"}, "Updating cameras...");
	#endif

	sort (_renderers->begin(), _renderers->end(), &SortingComparator);

	for (auto it = _cameras->begin(); it != _cameras->end(); it++) {
		#ifdef SIMPLE_LOGGER
			LOG ({"Game", "Rendering"}, "Updating camera " + it->lock()->ToString() + "...");
		#endif

		it->lock()->UpdateCamera(_renderers->begin(), _renderers->end());

		#ifdef SIMPLE_LOGGER
			LOG ({"Game", "Rendering"}, "Camera " + it->lock()->ToString() + " updated.");
		#endif
	}

	#ifdef SIMPLE_LOGGER
		Logger::Instance().Log({"Game", "Rendering"}, "Cameras updated.");
	#endif
}

void Game::Clear () {
	#ifdef SIMPLE_LOGGER
		Logger::Instance().Log({"Game"}, "Clearing game");
	#endif

	_gameObjects.clear();
	_gameObjectsToAdd.clear ();
	_gameObjectsToDestroy.clear ();

	_started = false;

	#ifdef SIMPLE_LOGGER
		Logger::Instance().Log({"Game"}, "Game cleared");
	#endif
}

weak_ptr<GameObject> Game::FindObjectWithTag (string tag) const {
	for (shared_ptr<GameObject> g : _gameObjects) {
		if (g->GetTag().compare(tag) == 0) {
			return weak_ptr<GameObject> (g);
		}
	}
	return weak_ptr<GameObject>();
}

vector<weak_ptr<GameObject>> Game::FindObjectsWithTag (string tag) const {
	vector<weak_ptr<GameObject>> res;
	for (shared_ptr<GameObject> g : _gameObjects) {
		if (g->GetTag().compare(tag) == 0) {
			res.push_back(weak_ptr<GameObject> (g));
		}
	}
	return res;
}
