#include <iostream>

#include "Logger.hpp"
#include "Loader.hpp"
#include "SFMLGame.hpp"


using namespace un;
using namespace std;

int main (int argc, char *argv[]) {
	SFMLGame game;

	if (Loader::Box2DTest (game) < 0) {
		cerr << "Error: Failed to init level!" << endl;
		return -1;
	}

	game.Run();
	//RenderingTest();
	//TextureTest();
	//GameObjectTest();
}