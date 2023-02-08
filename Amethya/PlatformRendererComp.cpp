#include "PlatformRendererComp.h"
#include "CollisionComp.h"
#include "ResourceManager.h"

namespace GameObjects::Components {
	PlatformRendererComp::PlatformRendererComp(GameObject& gameObject, PlatformTexture top, PlatformTexture bottom) : GameObjComp(gameObject, 2), top(top), bottom(bottom) {}

	void PlatformRendererComp::update(float dt) {}
	void PlatformRendererComp::lateUpdate(float dt) {}

	void PlatformRendererComp::draw(sf::RenderWindow& window) {
		auto& resourceManager = Resources::ResourceManager::getInstance();
		const auto collider = this->gameObject.getComponent<CollisionComp>();

		const auto camOffset = this->getGameObject().getScene().getCameraOffset();

		if (!collider)
			return;

		bool isTop = true;

		for (float top = this->gameObject.getPos().y; top < this->gameObject.getPos().y + collider->getHitboxSize().y; top += TILE_SIZE) {
			for (float left = this->gameObject.getPos().x; left < this->gameObject.getPos().x + collider->getHitboxSize().x; left += TILE_SIZE) {
				auto& sprite = resourceManager.getSprite("platforms", (size_t)(isTop ? this->top : this->bottom));

				sprite.setPosition(left - camOffset.x, top - camOffset.y);
				sprite.setScale(TILE_SIZE / (float)sprite.getTextureRect().width, TILE_SIZE / (float)sprite.getTextureRect().height);

				window.draw(sprite);
			}

			isTop = false;
		}
	}
}