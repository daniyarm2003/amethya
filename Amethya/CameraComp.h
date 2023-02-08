#pragma once

#include "GameObjComp.h"

namespace GameObjects::Components {
	class CameraComp : public GameObjComp {
	private:
		static constexpr float CAM_LERP_FACTOR = 0.05f;

		GameObject& trackedObj;

	public:
		CameraComp(GameObject& gameObject, GameObject& trackedObj);

		void update(float dt) override;
		void lateUpdate(float dt) override;
		void draw(sf::RenderWindow& window) override;
	};
}