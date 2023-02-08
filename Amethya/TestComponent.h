#pragma once

#include "GameObjComp.h"

namespace GameObjects::Components {
	class TestComponent : public GameObjects::GameObjComp {
	public:
		TestComponent(GameObject& gameObject);

		void update(float dt) override;
		void lateUpdate(float dt) override;
		void draw(sf::RenderWindow& window) override;
	};
}