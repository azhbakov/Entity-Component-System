#include <sstream>
#include <string>
#include <memory>

#include "Game.hpp"
#include "GameObject.hpp"
#include "IComponent.hpp"

#ifdef ENABLE_LOG
	#include "Logger.hpp"
#endif

using namespace std;
using namespace un;

GameObject::GameObject (string name, float worldX, float worldY) : _name(name), _transform(worldX, worldY) {
	#ifdef SIMPLE_LOGGER
		Logger::Instance().Log ({"GameObject"}, "GameObject ctor: " + this->ToString());
	#endif	
}

shared_ptr<GameObject> GameObject::CreateGameObject (std::string name, float worldX, float worldY) {
	auto sptr = shared_ptr<GameObject>(new GameObject(name, worldX, worldY));
	sptr->_self = weak_ptr<GameObject>(sptr);
	return sptr;
}

GameObject::~GameObject () {
	#ifdef SIMPLE_LOGGER
		Logger::Instance().Log ({"GameObject"}, "GameObject dtor: " + this->ToString());
	#endif
	_components.clear();
}

void GameObject::Start () {
	#ifdef SIMPLE_LOGGER
		Logger::Instance().Log ({"GameObject"}, "GameObject starting: " + this->ToString());
	#endif

	for (shared_ptr<IComponent> c : _components) {
		c->Start ();
	}
}

void GameObject::Update () {
	#ifdef SIMPLE_LOGGER
		Logger::Instance().Log ({"GameObject"}, "GameObject updating: " + this->ToString());
	#endif

	for (shared_ptr<IComponent> c : _components) {
		c->Update ();
	}

	#ifdef SIMPLE_LOGGER
		Logger::Instance().Log ({"GameObject"}, "GameObject updated: " + this->ToString());
	#endif
}

void GameObject::Destroy () {
	#ifdef SIMPLE_LOGGER
		Logger::Instance().Log ({"GameObject"}, "GameObject initiating destruction: " + this->ToString());
	#endif

	_components.clear ();
	
	Game::Instance().Destroy (this);
}

string GameObject::ToString () {
	stringstream ss;
	ss << "[" << "name: " << _name << ", transform: " << _transform.ToString() << "]";
	return ss.str();
}