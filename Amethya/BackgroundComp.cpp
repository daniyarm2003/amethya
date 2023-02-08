#include "BackgroundComp.h"
#include "Amethya.h"
#include "ResourceManager.h"

namespace GameObjects::Components {
	BackgroundComp::BackgroundComp(GameObject& gameObject, size_t bgInd, int zDepth, bool scrollX, bool scrollY) : GameObjComp(gameObject, 1), 
		bgInd(bgInd), zDepth(zDepth), scrollX(scrollX), scrollY(scrollY) {

		gameObject.setZDepth(zDepth);
	}

	void BackgroundComp::update(float dt) {}
	void BackgroundComp::lateUpdate(float dt) {}

	void BackgroundComp::draw(sf::RenderWindow& window) {
		auto& sprite = Resources::ResourceManager::getInstance().getSprite("backgrounds", this->bgInd);
		const auto camOffset = this->gameObject.getScene().getCameraOffset() / ((float)this->zDepth * glm::vec2(1.0f, 1.0f));

		for (unsigned int i = 0; i < 4; i++) {
			glm::vec2 bgOffset = glm::vec2(Amethya::WIDTH * (i % 2), Amethya::HEIGHT * (i / 2)) + camOffset;

			bgOffset.x = std::fmodf(std::fmodf(bgOffset.x, 2.0f * (float)Amethya::WIDTH) + 2.0f * (float)Amethya::WIDTH, 2.0f * (float)Amethya::WIDTH) - (float)Amethya::WIDTH;
			bgOffset.y = std::fmodf(std::fmodf(bgOffset.y, 2.0f * (float)Amethya::HEIGHT) + 2.0f * (float)Amethya::HEIGHT, 2.0f * (float)Amethya::HEIGHT) - (float)Amethya::HEIGHT;

			sprite.setPosition(this->scrollX ? bgOffset.x : 0.0f, this->scrollY ? bgOffset.y : 0.0f);
			window.draw(sprite);
		}
	}
}