#include "PlayerProperties.h"
#include "CollisionComp.h"
#include "AbstractPhysicsComp.h"

namespace GameObjects::Components::Properties {
	PlayerProperties::PlayerProperties(GameObject& gameObject) :
		EntityProperties(gameObject, 20.0f, 10.0f * AbstractPhysicsComp::METER_SCALE, 1.75f * AbstractPhysicsComp::METER_SCALE, AbstractPhysicsComp::METER_SCALE), 
		wallKickVel(3.5f * AbstractPhysicsComp::METER_SCALE, 0.75f * AbstractPhysicsComp::METER_SCALE), maxJumps(2) {
	
		this->jumps = this->maxJumps;
	}

	void PlayerProperties::resizeHitbox(glm::vec2 size, bool rightAlign, bool bottomAlign) {
		const auto collider = this->gameObject.getComponent<CollisionComp>();

		if (collider) {
			glm::vec2 prevSize = collider->getHitboxSize();
			collider->getHitboxSize() = size;

			this->gameObject.getPos() += glm::vec2(rightAlign ? prevSize.x - size.x : 0.0f, bottomAlign ? prevSize.y - size.y : 0.0f);
		}
	}

	void PlayerProperties::scaleHitbox(glm::vec2 scale, bool rightAlign, bool bottomAlign) {
		const auto collider = this->gameObject.getComponent<CollisionComp>();

		if (collider)
			this->resizeHitbox(collider->getHitboxSize() * scale, rightAlign, bottomAlign);
	}

	bool PlayerProperties::canResize(glm::vec2 size, bool rightAlign, bool bottomAlign) {
		const auto collider = this->gameObject.getComponent<CollisionComp>();

		bool hasCollision = true;

		if (collider) {
			glm::vec2 prevSize = collider->getHitboxSize();
			this->resizeHitbox(size, rightAlign, bottomAlign);

			hasCollision = collider->hasCollision();
			this->resizeHitbox(prevSize, rightAlign, bottomAlign);
		}

		return !hasCollision;
	}

	bool PlayerProperties::canScale(glm::vec2 scale, bool rightAlign, bool bottomAlign) {
		const auto collider = this->gameObject.getComponent<CollisionComp>();
		return collider ? this->canResize(collider->getHitboxSize() * scale, rightAlign, bottomAlign) : false;
	}

	glm::vec2 PlayerProperties::getWallKickVel() const {
		return this->wallKickVel;
	}

	void PlayerProperties::setWallKickXVel(float xVel) {
		this->wallKickVel.x = xVel;
	}

	void PlayerProperties::setWallKickYVel(float yVel) {
		this->wallKickVel.y = yVel;
	}

	unsigned int PlayerProperties::getJumps() const {
		return this->jumps;
	}

	void PlayerProperties::setJumps(unsigned int jumps) {
		this->jumps = glm::min(jumps, this->maxJumps);
	}

	unsigned int PlayerProperties::getMaxJumps() const {
		return this->maxJumps;
	}

	void PlayerProperties::setMaxJumps(unsigned int maxJumps) {
		this->maxJumps = maxJumps;
		this->setJumps(this->jumps);
	}

	void PlayerProperties::jump() {
		const auto physicsComp = this->gameObject.getComponent<AbstractPhysicsComp>();

		if (physicsComp && this->jumps > 0) {
			physicsComp->getVel().y = -glm::sqrt(2.0f * this->getJumpHeight() * AbstractPhysicsComp::GRAVITY);
			--this->jumps;
		}
	}

	void PlayerProperties::resetJumps() {
		this->jumps = this->maxJumps;
	}
}