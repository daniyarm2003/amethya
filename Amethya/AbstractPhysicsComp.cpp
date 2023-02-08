#include "AbstractPhysicsComp.h"

namespace GameObjects::Components {
	AbstractPhysicsComp::AbstractPhysicsComp(GameObject& gameObject, float mass) : GameObjComp(gameObject, 2), vel(), force(), mass(mass), collisions({false, false, false, false}) {}

	glm::vec2& AbstractPhysicsComp::getVel() {
		return this->vel;
	}

	glm::vec2& AbstractPhysicsComp::getForce() {
		return this->force;
	}

	float AbstractPhysicsComp::getMass() {
		return this->mass;
	}

	void AbstractPhysicsComp::setMass(float mass) {
		this->mass = mass;
	}

	void AbstractPhysicsComp::applyPhysics(float dt) {
		this->vel += this->force * dt / this->mass;
		this->gameObject.getPos() += this->vel * dt;
		this->force *= 0.0f;
	}

	void AbstractPhysicsComp::draw(sf::RenderWindow& window) {}

	bool AbstractPhysicsComp::getCollision(PlatformCollision collision) const {
		return this->collisions[(size_t)collision];
	}

	void AbstractPhysicsComp::setCollision(PlatformCollision collision, bool value) {
		this->collisions[(size_t)collision] = value;
	}
}