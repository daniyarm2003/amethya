#include "OrdinaryPhysComp.h"
#include "CollisionComp.h"

namespace GameObjects::Components {
	OrdinaryPhysComp::OrdinaryPhysComp(GameObject& gameObject, float mass) : AbstractPhysicsComp(gameObject, mass) {}

	void OrdinaryPhysComp::update(float dt) {
		this->getForce() += this->getMass() * glm::vec2(0.0f, GRAVITY);
	}

	void OrdinaryPhysComp::lateUpdate(float dt) {
		this->applyPhysics(dt);

		for (size_t i = 0; i < PLAT_COLLISION_LEN; i++) {
			this->setCollision((PlatformCollision)i, false);
		}

		const auto collider = this->gameObject.getComponent<CollisionComp>();
		if (!collider)
			return;

		for (auto& gameObject : this->gameObject.getScene()) {
			if (gameObject.get() == &this->gameObject)
				continue;

			glm::vec2 mtv = collider->getMTV(*gameObject);
			if (glm::length2(mtv) < CollisionComp::MIN_MTV_LENGTH * CollisionComp::MIN_MTV_LENGTH)
				continue;

			if (glm::abs(mtv.y) >= glm::abs(mtv.x)) {
				this->setCollision(mtv.y < 0.0f ? PlatformCollision::GROUND : PlatformCollision::CEILING, true);
			}
			else {
				this->setCollision(mtv.x < 0.0f ? PlatformCollision::LEFT : PlatformCollision::RIGHT, true);
			}

			this->gameObject.getPos() += mtv;

			if (glm::dot(this->getVel(), mtv) < 0.0f) {
				glm::vec2 normal = glm::normalize(mtv), edge = glm::vec2(normal.y, -normal.x);
				this->getVel() = glm::dot(this->getVel(), edge) * edge;
			}
		}
	}
}