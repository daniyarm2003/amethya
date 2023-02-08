#pragma once

#include "pch.h"
#include "ResourceManager.h"

namespace Resources {
	struct SpriteCollection {
	private:
		sf::Texture texture;
		std::vector<sf::Sprite> sprites;

		SpriteCollection(std::string location);
		void addSprite(sf::Sprite sprite);

		friend class ResourceManager;

	public:
		SpriteCollection();
		sf::Sprite& operator [](size_t index);
	};
}