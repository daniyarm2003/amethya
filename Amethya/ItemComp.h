#pragma once

#include "GameObjComp.h"

namespace GameObjects::Components {
	class ItemComp : public GameObjComp {
	private:
		const std::function<bool(GameObject&)> onCollect;

	public:
		ItemComp(GameObject& gameObject, std::function<bool(GameObject&)> onCollect);

		void update(float dt) override;
		void lateUpdate(float dt) override;
		void draw(sf::RenderWindow& window) override;
	};

	class OscillatorComp : public GameObjComp {
	private:
		const glm::vec2 amplitude, defaultPos;
		const float period;
		float theta;

	public:
		OscillatorComp(GameObject& gameObject, glm::vec2 amplitude, float period);

		void update(float dt) override;
		void lateUpdate(float dt) override;
		void draw(sf::RenderWindow& window) override;
	};
}