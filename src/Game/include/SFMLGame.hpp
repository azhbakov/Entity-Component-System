#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>

#include "Game.hpp"
#include "PhysicsSubsystem.hpp"
#include "ResourceManager.hpp"

namespace un {
	
	class SFMLGame {
		private:
			Game& _game;
			PhysicsSubsystem _physicsSubsystem;
			sf::RenderWindow _window;
			ResourceManager _resourceManager;
		public:
			SFMLGame ()
				: _game(Game::Instance()),
				_window (sf::VideoMode(800, 600), "UN Game") {}
			~SFMLGame () {}

			int Run ();
			Game& GetGame () { return _game; }
			PhysicsSubsystem& GetPhysicsSubsystem () { return _physicsSubsystem; }
			sf::RenderWindow& GetRenderWindow () { return _window; }
			ResourceManager& GetResourceManager () { return _resourceManager; }
	};

}