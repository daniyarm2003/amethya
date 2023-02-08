#pragma once

#include "pch.h"
#include "SpriteCollection.h"
#include "Animation.h"

namespace Resources {
	struct SpriteCollection;

	class ResourceManager {
	private:
		const std::string TEXTURE_LOCATION = "Resources/textures.json";
		const std::string ANIMATION_LOCATION = "Resources/animations.json";

		std::map<std::string, SpriteCollection> spriteCollections;
		std::map<std::string, Animation> animations;

		ResourceManager();

		void loadTextures();
		void loadAnimations();

	public:
		static bool parseJsonFile(std::string path, rapidjson::Document& document);

		ResourceManager(const ResourceManager&) = delete;
		void operator =(const ResourceManager&) = delete;

		sf::Sprite& getSprite(std::string texture, size_t index);
		Animation& getAnimation(std::string animation);

		static ResourceManager& getInstance();
	};
}