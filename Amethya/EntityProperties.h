#pragma once

#include "GameObjComp.h"

namespace GameObjects::Components::Properties {
	class EntityProperties : public GameObjComp {
	private:
		float health, maxHealth, moveForce, maxSpeed, jumpHeight;
	
	public:
		EntityProperties(GameObject& gameObject, float maxHealth, float moveForce, float maxSpeed, float jumpHeight);

		float getHealth() const;
		void setHealth(float health);

		float getMaxHealth() const;
		void setMaxHealth(float maxHealth);

		float getMoveForce() const;
		void setMoveForce(float moveForce);

		float getMaxSpeed() const;
		void setMaxSpeed(float maxSpeed);

		float getJumpHeight() const;
		void setJumpHeight(float jumpHeight);

		void update(float dt) override;
		void lateUpdate(float dt) override;
		void draw(sf::RenderWindow& window) override;
	};
}