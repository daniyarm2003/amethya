#pragma once

#include "GameObjComp.h"

namespace GameObjects::Components {
	enum class PlatformCollision {
		GROUND, LEFT, CEILING, RIGHT
	};

	class AbstractPhysicsComp : public GameObjComp {
	public:
		static constexpr size_t PLAT_COLLISION_LEN = 4;

	private:
		glm::vec2 vel, force;
		float mass;

		std::array<bool, PLAT_COLLISION_LEN> collisions;

	protected:
		void setCollision(PlatformCollision collision, bool value);

	public:
		static constexpr float METER_SCALE = 100.0f;
		static constexpr float GRAVITY = 9.81f * METER_SCALE;

		AbstractPhysicsComp(GameObject& gameObject, float mass);

		glm::vec2 &getVel(), &getForce();

		float getMass();
		void setMass(float mass);

		void applyPhysics(float dt);
		void draw(sf::RenderWindow& window) override;

		bool getCollision(PlatformCollision collision) const;
	};
}