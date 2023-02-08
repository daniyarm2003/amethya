#include "AnimationRendererComp.h"
#include "CollisionComp.h"

namespace GameObjects::Components {
	AnimationRendererComp::AnimationRendererComp(GameObject& gameObject, Resources::Animation animation) : GameObjComp(gameObject, 1), animation(animation) {}

	void AnimationRendererComp::setAnimation(Resources::Animation animation) {
		this->animation = animation;
	}

	void AnimationRendererComp::update(float dt) {
		this->animation.animate(dt);
	}

	void AnimationRendererComp::lateUpdate(float dt) {}

	void AnimationRendererComp::draw(sf::RenderWindow& window) {
		auto& sprite = this->animation.getCurrentSprite();
		const auto collider = this->gameObject.getComponent<CollisionComp>();

		const auto camOffset = this->getGameObject().getScene().getCameraOffset();

		if (!collider)
			return;

		sprite.setPosition(this->gameObject.getPos().x + this->animation.getOffset().x * collider->getHitboxSize().x - camOffset.x,
			this->gameObject.getPos().y + this->animation.getOffset().y * collider->getHitboxSize().y - camOffset.y);

		sprite.setScale(collider->getHitboxSize().x / sprite.getTextureRect().width * this->animation.getScale().x, 
			collider->getHitboxSize().y / sprite.getTextureRect().height * this->animation.getScale().y);

		window.draw(sprite);
	}
}