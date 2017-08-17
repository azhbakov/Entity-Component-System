#include <memory>
#include <set>
#include <iostream>

#ifdef ENABLE_LOG
	#include "Logger.hpp"
#endif
#include "Renderer.hpp"
#include "Game.hpp"

using namespace std;
using namespace un;

#define DEGTORAD -57.295779513082320876f

Renderer::Renderer (weak_ptr<GameObject>& g, int sortingOrder = 0)
	: Component(g), _sortingOrder(sortingOrder) {
		_layers.insert (RenderingLayer::DEFAULT);
	}

void Renderer::Start () {
	Game::Instance().RegisterRenderer (GetSelf());
}

void Renderer::SyncTransformToRenderer () {
	const Transform& t = GetTransform();
	GetTransformData().setPosition (t.X(), t.Y());
	GetTransformData().setRotation (t.Rotation() * DEGTORAD);
}

void Renderer::UpdateRenderer () {
	SyncTransformToRenderer ();
}

void Renderer::AddRenderingLayer (RenderingLayer layer) {
	_layers.insert (layer);
	#ifdef SIMPLE_LOGGER
		LOG ({"Component", "Renderer"}, "Added rendering layer " + layer + '.');
	#endif
}

void Renderer::RemoveRenderingLayer (RenderingLayer layer) {
	if (_layers.erase (layer) == 0) {
		#ifdef SIMPLE_LOGGER
			LOG ({"Component", "Renderer", "Error"}, "Trying to remove unregistered rendering layer " + layer + '!');
		#endif
		cerr << "Trying to remove unregistered rendering layer " << layer << "!" << endl;
	}
	#ifdef SIMPLE_LOGGER
		LOG ({"Component", "Renderer"}, "Removed rendering layer " + layer + '.');
	#endif
}
