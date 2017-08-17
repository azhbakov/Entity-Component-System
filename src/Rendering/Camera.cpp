#include <memory>
#include <iostream>
#include <set>

#include "Game.hpp"
#include "Camera.hpp"
#ifdef ENABLE_LOG
	#include "Logger.hpp"
#endif
//#include "UnException.hpp"

#include <SFML/Graphics.hpp>

using namespace std;
using namespace un;

#define DEGTORAD -57.295779513082320876f

Camera::Camera (weak_ptr<GameObject> g, sf::RenderWindow& window, float viewWidth, float viewHeight) : 
	Component (g),
	_window (window) {
		_window.setView(sf::View(sf::Vector2f(0,0), sf::Vector2f(viewWidth, viewHeight)));
		_layers.insert (RenderingLayer::DEFAULT);
}

void Camera::AddRenderingLayer (RenderingLayer layer) {
	_layers.insert (layer);
	#ifdef SIMPLE_LOGGER
		LOG ({"Component", "Camera"}, "Added rendering layer " + layer + '.');
	#endif
}

void Camera::RemoveRenderingLayer (RenderingLayer layer) {
	if (_layers.erase (layer) == 0) {
		#ifdef SIMPLE_LOGGER
			LOG ({"Component", "Camera", "Error"}, "Trying to remove unregistered rendering layer " + layer + '!');
		#endif
		cerr << "Trying to remove unregistered rendering layer " << layer << "!" << endl;
	}
	#ifdef SIMPLE_LOGGER
		LOG ({"Component", "Camera"}, "Removed rendering layer " + layer + '.');
	#endif
}

void Camera::Start () {
	/*
	 Not in constructor because GetSelf is not initialized in constructor!
	 GetSelf works only after _self initialization by ComponentFactory
	*/
	Game::Instance().RegisterCamera(GetSelf());
}

void Camera::UpdateCameraPosition () {
	float ppu = Game::Instance().PIXELS_PER_UNIT;
	Transform& t = GetTransform();
	const sf::View& oldView = _window.getView();
	sf::View view (sf::Vector2f(t.X(), t.Y()) * ppu, oldView.getSize());
	view.setRotation (t.Rotation() * DEGTORAD);
	_window.setView (view);
}

void Camera::UpdateCamera (std::vector<std::weak_ptr<IRenderer>>::iterator begin, std::vector<std::weak_ptr<IRenderer>>::iterator end) {
	#ifdef SIMPLE_LOGGER
		Logger::Instance().Log ({"Component", "Camera"}, "Rendering scene by camera " + GetGameObject().lock()->ToString() + ".");
	#endif

	UpdateCameraPosition ();

	for (auto it = begin; it != end; it++) {
		if (it->expired()) {
			cerr << "Error: expired renderer registered in Camera!" << endl;
			#ifdef SIMPLE_LOGGER
				Logger::Instance().Log ({"Component", "Camera", "Error"}, "Expired renderer passed to camera!");
			#endif
			continue;
		}

		if (HasMatchingLayers((*it))) {
			Render ((*it));
		}
	}

	#ifdef SIMPLE_LOGGER
		Logger::Instance().Log ({"Component", "Camera"}, "Scene rendered by camera " + GetGameObject().lock()->ToString());
	#endif
}

bool Camera::HasMatchingLayers (std::weak_ptr<IRenderer> renderer) {
	auto& targetLayers = renderer.lock()->GetRenderingLayers();
	for (auto it = targetLayers.begin(); it != targetLayers.end(); it++) {
		if (_layers.find(*it) != _layers.end()) {
			return true;
		}
	}
	return false;
}

void Camera::Render (weak_ptr<IRenderer> renderer) {
	int ppu = Game::Instance().PIXELS_PER_UNIT;

	sf::Transformable& t = renderer.lock()->GetTransformData();
	t.setPosition (t.getPosition().x * ppu, t.getPosition().y * -ppu);
	_window.draw(renderer.lock()->GetRenderData());
}