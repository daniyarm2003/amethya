#pragma once

#include "pch.h"
#include "GameObject.h"

namespace GameObjects::Initializers {
	GameObject* initTestGameObj(Scenes::Scene& scene, glm::vec2 pos);
	GameObject* initTestHitbox(Scenes::Scene& scene, glm::vec4 rect);
	GameObject* initCamera(GameObject& trackedObj);
	GameObject* initBackground(Scenes::Scene& scene, size_t bgInd, int zDepth, bool scrollX, bool scrollY);
	GameObject* initJumpRefillOrb(Scenes::Scene& scene, glm::vec2 pos);
}