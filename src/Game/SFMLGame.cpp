#include "SFMLGame.hpp"
#include "Loader.hpp"

#include "Game.hpp"
#ifdef ENABLE_LOG
	#include "Logger.hpp"
#endif
#include <SFML/Graphics.hpp>

using namespace un;
using namespace std;

int SFMLGame::Run () {
	_window.setVerticalSyncEnabled (true);

	while (_window.isOpen ()) {
		sf::Event event;

		while (_window.pollEvent (event)) {
			if (event.type == sf::Event::Closed) {
				_window.close ();
			}
		}

		_physicsSubsystem.UpdatePhysics ();
		_window.clear(sf::Color::White);
		_game.Update ();
		_window.display();
	}

	_game.Clear();
}