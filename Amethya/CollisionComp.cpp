#include "CollisionComp.h"
#include "AbstractPhysicsComp.h"

namespace GameObjects::Components {
	CollisionComp::CollisionComp(GameObject& gameObject, int collisionFlags, CollisionType type, float width, float height) : GameObjComp(gameObject, 2), size(width, height), 
		type(type), collisionFlags(collisionFlags) {

		this->setEnabled(false);
	}

	glm::vec2& CollisionComp::getHitboxSize() {
		return this->size;
	}

	bool CollisionComp::collides(GameObject& other) {
		auto otherCollider = other.getComponent<CollisionComp>();

		if (!otherCollider || !(this->collisionFlags & otherCollider->collisionFlags))
			return false;

		return this->gameObject.getPos().x <= other.getPos().x + otherCollider->getHitboxSize().x &&
			this->gameObject.getPos().x + this->getHitboxSize().x >= other.getPos().x &&
			this->gameObject.getPos().y <= other.getPos().y + otherCollider->getHitboxSize().y &&
			this->gameObject.getPos().y + this->getHitboxSize().y >= other.getPos().y;
	}

	glm::vec2 CollisionComp::getMTV(GameObject& other) {
		if (!this->collides(other))
			return glm::vec2();

		auto otherCollider = other.getComponent<CollisionComp>();

		if (otherCollider->type == CollisionType::ZONE)
			return glm::vec2();

		else if (otherCollider->type == CollisionType::SOLID) {
			glm::vec2 normals[] = {
				glm::vec2(-1.0f, 0.0f), glm::vec2(1.0f, 0.0f), glm::vec2(0.0f, -1.0f), glm::vec2(0.0f, 1.0f)
			};

			glm::vec2 hitNormal;
			float overlap = INFINITY;

			for (const auto& normal : normals) {
				float proj = glm::abs(glm::min(glm::dot(this->gameObject.getPos(), normal), glm::dot(this->gameObject.getPos() + this->getHitboxSize(), normal))
					- glm::max(glm::dot(other.getPos(), normal), glm::dot(other.getPos() + otherCollider->getHitboxSize(), normal)));

				if (proj < overlap) {
					overlap = proj;
					hitNormal = normal;
				}
			}

			return overlap * hitNormal;
		}

		auto physicsComp = this->gameObject.getComponent<AbstractPhysicsComp>();

		if (!physicsComp)
			return glm::vec2();

		float proj = this->gameObject.getPos().y + this->getHitboxSize().y - other.getPos().y;

		if (proj < this->getHitboxSize().y / 2.0f && physicsComp->getVel().y > 0.0f)
			return glm::vec2(0.0f, -proj);

		return glm::vec2();
	}

	bool CollisionComp::hasCollision() {
		for (auto& gameObject : this->gameObject.getScene()) {
			if (gameObject.get() == &this->gameObject)
				continue;

			if (glm::length2(this->getMTV(*gameObject)) >= MIN_MTV_LENGTH * MIN_MTV_LENGTH)
				return true;
		}

		return false;
	}

	void CollisionComp::update(float dt) {}
	void CollisionComp::lateUpdate(float dt) {}
	void CollisionComp::draw(sf::RenderWindow& window) {}
}