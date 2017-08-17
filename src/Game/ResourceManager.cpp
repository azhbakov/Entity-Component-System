#include <map>
#include <string>

#include "ResourceManager.hpp"
#ifdef ENABLE_LOG
	#include "Logger.hpp"
#endif
#include <SFML/Graphics.hpp>
#include "UnException.hpp"

using namespace std;
using namespace un;

ResourceManager::~ResourceManager () {
	for (auto i = _textures.begin(); i != _textures.end(); i++) {
		#ifdef SIMPLE_LOGGER
	    	Logger::Instance().Log ({"ResourceManager", "Texture"}, "Resource unloading: texture " + i->first);
	    #endif
	    delete i->second;
	}

	for (auto i = _fonts.begin(); i != _fonts.end(); i++) {
		#ifdef SIMPLE_LOGGER
			Logger::Instance().Log ({"ResourceManager", "Font"}, "Resource unloading: font " + i->first);
		#endif
		delete i->second;
	}
	#ifdef SIMPLE_LOGGER
    	Logger::Instance().Log ({"ResourceManager"}, "Resource Manager destructed");
    #endif
}

sf::Texture& ResourceManager::LoadTexture (const string& path, const string& resourceId, bool repeat) {
	sf::Texture *texture = new sf::Texture();

	if (!texture->loadFromFile (path)) {
	    cerr << "Failed to load texture from file!" << endl; 
	    
	    #ifdef SIMPLE_LOGGER
	    	Logger::Instance().Log ({"ResourceManager", "Texture", "Error"}, "Error: Failed to load texture: " + path);
	    #endif

	    throw UnException ("Failed to load texture: " + path);
	}

	texture->setRepeated (repeat);

	_textures.insert (pair<string, sf::Texture *>(resourceId, texture));

	#ifdef SIMPLE_LOGGER
    	Logger::Instance().Log ({"ResourceManager", "Texture"}, "Resource loaded: texture " + resourceId + " (" + path + ")");
    #endif

	return *texture;
}

sf::Texture& ResourceManager::GetTexture (const string& resourceId) const {
	return *(_textures.find (resourceId)->second);
}

sf::Font& ResourceManager::LoadFont (const string& path, const string& resourceId) {
	sf::Font *font = new sf::Font();

	if (!font->loadFromFile (path)) {
	    cerr << "Failed to load font from file!" << endl; 
	    
	    #ifdef SIMPLE_LOGGER
	    	Logger::Instance().Log ({"ResourceManager", "Texture", "Error"}, "Error: Failed to load font: " + path);
	    #endif

	    throw UnException ("Failed to load font: " + path);
	}

	_fonts.insert (pair<string, sf::Font *>(resourceId, font));

	#ifdef SIMPLE_LOGGER
    	Logger::Instance().Log ({"ResourceManager", "Texture"}, "Resource loaded: font " + resourceId + " (" + path + ")");
    #endif

	return *font;
}

sf::Font& ResourceManager::GetFont (const string& resourceId) const {
	return *(_fonts.find (resourceId)->second);
}
