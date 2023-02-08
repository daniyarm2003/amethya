#pragma once

#include "GameObjComp.h"

namespace GameObjects::Components {
	class BackgroundComp : public GameObjComp {
	private:
		const int zDepth;
		const size_t bgInd;

		bool scrollX, scrollY;

	public:
		BackgroundComp(GameObject& gameObject, size_t bgInd, int zDepth, bool scrollX, bool scrollY);

		void update(float dt) override;
		void lateUpdate(float dt) override;
		void draw(sf::RenderWindow& window) override;
	};
}