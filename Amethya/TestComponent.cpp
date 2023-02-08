#include "TestComponent.h"
#include "InputManager.h"
#include "AbstractPhysicsComp.h"

namespace GameObjects::Components {
	TestComponent::TestComponent(GameObject& gameObject) : GameObjComp(gameObject, 1) {}

	void TestComponent::update(float dt) {
		auto physComp = this->gameObject.getComponent<AbstractPhysicsComp>();

		if (!physComp)
			return;

		auto& inputManager = Input::InputManager::getInstance();

		if (inputManager.isInputActive("Left") && physComp->getVel().x > -2.0f * AbstractPhysicsComp::METER_SCALE) {
			physComp->getForce().x -= 10.0f * AbstractPhysicsComp::METER_SCALE;
		}
		else if (inputManager.isInputActive("Right") && physComp->getVel().x < 2.0f * AbstractPhysicsComp::METER_SCALE) {
			physComp->getForce().x += 10.0f * AbstractPhysicsComp::METER_SCALE;
		}
		else {
			physComp->getVel().x *= 0.98f;
		}

		if (inputManager.isInputActive("Jump")) {
			physComp->getVel().y = -500.0f;
		}
	}

	void TestComponent::lateUpdate(float dt) {}

	void TestComponent::draw(sf::RenderWindow& window) {}
}