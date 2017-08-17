#ifndef GAME_HPP
#define GAME_HPP

#include <vector>
#include <memory>

#include "WeakPtrStorage.hpp"
#include "GameObject.hpp"
#include "IPhysicsBody.hpp"
#include "IRenderer.hpp"
#include "IGUIElement.hpp"
#include "ICamera.hpp"

namespace un {

	// Singleton
	class Game final { 
		private:

			std::vector<std::shared_ptr<GameObject>> _gameObjects;

			std::vector<std::shared_ptr<GameObject>> _gameObjectsToAdd; 
			std::vector<GameObject *> _gameObjectsToDestroy;
			
			WeakPtrStorage<IRenderer> _renderers;
			std::vector<IGUIElement *> _guiElements;
			WeakPtrStorage<ICamera> _cameras;

			bool _started;

			Game () 
				: _renderers("Game Renderers"), _cameras("Game Cameras"), _started(false), PIXELS_PER_UNIT(100) {}
			Game (const Game &) = delete;
			Game& operator= (const Game&) = delete;
			~Game ();

			void UpdatePhysics ();
			void UpdateGameObjects ();
			void UpdateRenderers ();
			void UpdateGUIElements ();
			void UpdateCameras ();
		public:
			const int PIXELS_PER_UNIT;

			static Game& Instance ();
			
			std::weak_ptr<GameObject> Instantiate (std::string name);

			std::weak_ptr<GameObject> Instantiate (float worldX, float worldY);

			std::weak_ptr<GameObject> Instantiate (std::string name, float worldX, float worldY);
			/* 
				Appears to be called only from GameObject, as all the others have only GameObjectPtr
				To destroy GameObject others access GameObject's method Destroy via GameObjectPtr.
				GameObject's Destroy calls Game's Destroy with "this".
			*/
			void Destroy (GameObject *g);

			void Clear ();
			
			void RegisterRenderer (std::weak_ptr<IRenderer> renderer);
			void RegisterGUIElement (IGUIElement *element);
			void RegisterCamera (std::weak_ptr<ICamera> camera);

			void Start ();
			void Update ();

			std::weak_ptr<GameObject> FindObjectWithTag (std::string tag) const;
			std::vector<std::weak_ptr<GameObject>> FindObjectsWithTag (std::string tag) const;
	};

}
#endif