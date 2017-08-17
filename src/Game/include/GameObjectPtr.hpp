#ifndef GAMEOBJECTPTR_HPP
#define GAMEOBJECTPTR_HPP

#include "GameObject.hpp"

namespace un {

	class GameObjectPtr final {
		private:
			GameObject *_gameObject;
		public:
			GameObjectPtr (GameObject *g) : _gameObject(g) {}
			GameObject *operator->() const { return _gameObject; }
	};

}

#endif