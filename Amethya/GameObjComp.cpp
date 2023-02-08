#include "GameObjComp.h"

namespace GameObjects {
	GameObjComp::GameObjComp(GameObject& gameObject, int priority) : gameObject(gameObject), priority(priority), enabled(true) {}

	int GameObjComp::getPriority() const {
		return this->priority;
	}

	bool GameObjComp::isEnabled() {
		return this->enabled;
	}

	void GameObjComp::setEnabled(bool enabled) {
		this->enabled = enabled;
	}

	GameObject& GameObjComp::getGameObject() {
		return this->gameObject;
	}
}