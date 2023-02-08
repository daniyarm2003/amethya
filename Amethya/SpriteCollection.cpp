#include "SpriteCollection.h"

namespace Resources {
	SpriteCollection::SpriteCollection() {}

	SpriteCollection::SpriteCollection(std::string location) {
		this->texture.loadFromFile(location);
	}

	void SpriteCollection::addSprite(sf::Sprite sprite) {
		sprite.setTexture(this->texture);
		this->sprites.push_back(sprite);
	}

	sf::Sprite& SpriteCollection::operator [](size_t index) {
		return this->sprites[index];
	}
}