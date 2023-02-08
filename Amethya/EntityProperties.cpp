#include "EntityProperties.h"

namespace GameObjects::Components::Properties {
	EntityProperties::EntityProperties(GameObject& gameObject, float maxHealth, float moveForce, float maxSpeed, float jumpHeight) : GameObjComp(gameObject, 0), health(maxHealth), 
		maxHealth(maxHealth), maxSpeed(maxSpeed), jumpHeight(jumpHeight), moveForce(moveForce) {}

	float EntityProperties::getHealth() const {
		return this->health;
	}

	void EntityProperties::setHealth(float health) {
		this->health = glm::clamp(health, 0.0f, this->maxHealth);
	}

	float EntityProperties::getMaxHealth() const {
		return this->maxHealth;
	}

	void EntityProperties::setMaxHealth(float maxHealth) {
		this->maxHealth = glm::max(maxHealth, 0.0f);
		this->setHealth(this->health);
	}

	float EntityProperties::getMoveForce() const {
		return this->moveForce;
	}

	void EntityProperties::setMoveForce(float moveForce) {
		this->moveForce = glm::max(moveForce, 0.0f);
	}

	float EntityProperties::getMaxSpeed() const {
		return this->maxSpeed;
	}

	void EntityProperties::setMaxSpeed(float maxSpeed) {
		this->maxSpeed = glm::max(maxSpeed, 0.0f);
	}

	float EntityProperties::getJumpHeight() const {
		return this->jumpHeight;
	}

	void EntityProperties::setJumpHeight(float jumpHeight) {
		this->jumpHeight = glm::max(jumpHeight, 0.0f);
	}

	void EntityProperties::update(float dt) {
		if (this->health <= 0.0f)
			this->getGameObject().setRemovable(true);
	}

	void EntityProperties::lateUpdate(float dt) {}
	void EntityProperties::draw(sf::RenderWindow& window) {}
}