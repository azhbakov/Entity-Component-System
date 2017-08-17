#pragma once

#include <SFML/Graphics.hpp>
#include <map>
#include <string>

namespace un {

	class ResourceManager {
		private:
			std::map<std::string, sf::Texture *> _textures;
			std::map<std::string, sf::Font *> _fonts;
		public:
			ResourceManager() {};
			~ResourceManager();
			sf::Texture& LoadTexture (const std::string& path, const std::string& resourceId, bool repeat = false);
			sf::Texture& GetTexture (const std::string& resourceId) const;
			sf::Font& LoadFont (const std::string& path, const std::string& resourceId);
			sf::Font& GetFont (const std::string& resourceId) const;
	};

}