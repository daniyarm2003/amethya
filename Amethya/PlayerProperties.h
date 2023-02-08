#pragma once

#include "EntityProperties.h"
#include "AbstractPhysicsComp.h"

namespace GameObjects::Components::Properties {
	class PlayerProperties : public EntityProperties {
	private:
		glm::vec2 wallKickVel;
		unsigned int jumps, maxJumps;

	public:
		static constexpr float SLIDE_MIN_SPEED = 0.25f * AbstractPhysicsComp::METER_SCALE;

		PlayerProperties(GameObject& gameObject);

		void resizeHitbox(glm::vec2 size, bool rightAlign, bool bottomAlign);
		void scaleHitbox(glm::vec2 scale, bool rightAlign, bool bottomAlign);

		bool canResize(glm::vec2 size, bool rightAlign, bool bottomAlign);
		bool canScale(glm::vec2 scale, bool rightAlign, bool bottomAlign);

		glm::vec2 getWallKickVel() const;
		
		void setWallKickXVel(float xVel);
		void setWallKickYVel(float yVel);

		unsigned int getJumps() const;
		void setJumps(unsigned int jumps);

		unsigned int getMaxJumps() const;
		void setMaxJumps(unsigned int maxJumps);

		void jump();
		void resetJumps();
	};
}