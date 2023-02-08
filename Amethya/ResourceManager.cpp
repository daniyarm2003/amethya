#include "ResourceManager.h"

using namespace rapidjson;
namespace fs = std::filesystem;

namespace Resources {

	ResourceManager::ResourceManager() {
		this->loadTextures();
		this->loadAnimations();
	}

	void ResourceManager::loadTextures() {
		Document textures;

		if (!this->parseJsonFile(TEXTURE_LOCATION, textures)) {
			std::cerr << "Unable to load textures." << std::endl;
			return;
		}

		for (auto it = textures.MemberBegin(); it != textures.MemberEnd(); it++) {
			std::string fileLocation = it->value["location"].GetString();

			const auto& [spriteCollection, inserted] = this->spriteCollections.emplace(it->name.GetString(), SpriteCollection(fileLocation));

			if (!inserted) {
				std::cerr << "Unable to load textures." << std::endl;
				return;
			}

			for (const auto& spriteInfo : it->value["sprites"].GetArray()) {
				sf::Sprite sprite;

				auto rectArr = spriteInfo["rect"].GetArray();
				auto colorArr = spriteInfo["color"].GetArray();

				sprite.setTextureRect(sf::IntRect(rectArr[0].GetInt(), rectArr[1].GetInt(), rectArr[2].GetInt(), rectArr[3].GetInt()));
				sprite.setColor(sf::Color(colorArr[0].GetInt(), colorArr[1].GetInt(), colorArr[2].GetInt(), colorArr[3].GetInt()));

				spriteCollection->second.addSprite(sprite);
			}
		}
	}

	void ResourceManager::loadAnimations() {
		Document animations;

		if (!this->parseJsonFile(ANIMATION_LOCATION, animations)) {
			std::cerr << "Unable to load animations." << std::endl;
			return;
		}

		for (auto it = animations.MemberBegin(); it != animations.MemberEnd(); it++) {
			std::string animationName = it->name.GetString();
			const auto& [insertedPair, inserted] = this->animations.emplace(animationName, Animation());

			if (!inserted) {
				std::cerr << "Unable to load animations." << std::endl;
				return;
			}

			for (const auto& animationFrame : it->value.GetArray()) {
				const auto& animFrameObj = animationFrame.GetObject();

				AnimationFrame frame = { animFrameObj["spritesheet"].GetString(), animFrameObj["index"].GetUint(), animFrameObj["duration"].GetFloat() };

				if (animFrameObj.HasMember("transforms")) {
					const auto& offsetArr = animFrameObj["transforms"]["offset"].GetArray(), scaleArr = animFrameObj["transforms"]["scale"].GetArray();

					frame.offset = glm::vec2(offsetArr[0].GetFloat(), offsetArr[1].GetFloat());
					frame.scale = glm::vec2(scaleArr[0].GetFloat(), scaleArr[1].GetFloat());
				}

				insertedPair->second.addFrame(frame);
			}
		}
	}

	sf::Sprite& ResourceManager::getSprite(std::string texture, size_t index) {
		if (this->spriteCollections.find(texture) == this->spriteCollections.end()) {
			std::cerr << "Texture by the name of " << texture << " does not exist." << std::endl;
		}

		return this->spriteCollections[texture][index];
	}

	Animation& ResourceManager::getAnimation(std::string animation) {
		if (this->animations.find(animation) == this->animations.end()) {
			std::cerr << "Animation by the name of " << animation << " does not exist." << std::endl;
		}

		return this->animations[animation];
	}

	ResourceManager& ResourceManager::getInstance() {
		static ResourceManager instance;
		return instance;
	}

	bool ResourceManager::parseJsonFile(std::string path, Document& document) {
		if (!fs::exists(path)) {
			std::cerr << "File " << path << " does not exist." << std::endl;
			return false;
		}

		std::ifstream inputStream;
		inputStream.open(path, std::ios::in);

		std::stringstream contentBuffer;
		contentBuffer << inputStream.rdbuf();

		document.Parse(contentBuffer.str().c_str());

		return document.IsObject();
	}
}