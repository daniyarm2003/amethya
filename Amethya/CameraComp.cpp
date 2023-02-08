#include "CameraComp.h"

namespace GameObjects::Components {
	CameraComp::CameraComp(GameObject& gameObject, GameObject& trackedObj) : GameObjComp(gameObject, 1), trackedObj(trackedObj) {}

	void CameraComp::update(float dt) {
		this->gameObject.getPos() = glm::lerp(this->gameObject.getPos(), this->trackedObj.getPos(), CAM_LERP_FACTOR);
	}

	void CameraComp::lateUpdate(float dt) {}

	void CameraComp::draw(sf::RenderWindow& window) {}
}