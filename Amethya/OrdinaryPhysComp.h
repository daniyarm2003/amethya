#pragma once

#include "AbstractPhysicsComp.h"

namespace GameObjects::Components {
	class OrdinaryPhysComp : public AbstractPhysicsComp {
	public:
		OrdinaryPhysComp(GameObject& gameObject, float mass);

		void update(float dt) override;
		void lateUpdate(float dt) override;
	};
}