#include "DefaultIdleState.h"
#include "ResourceManager.h"
#include "AnimationRendererComp.h"
#include "AbstractPhysicsComp.h"

namespace GameObjects::Components::States {
	DefaultIdleState::DefaultIdleState(StateMachineComp& stateMachine, std::string animationName) : AbstractState(stateMachine), animationName(animationName), friction(0.025f) {}

	void DefaultIdleState::onEnter() {
		const auto animationComp = this->getGameObject().getComponent<AnimationRendererComp>();

		if (animationComp)
			animationComp->setAnimation(Resources::ResourceManager::getInstance().getAnimation(this->animationName));
	}

	void DefaultIdleState::onExit() {}

	void DefaultIdleState::update(float dt) {
		const auto physicsComp = this->getGameObject().getComponent<AbstractPhysicsComp>();

		if (physicsComp)
			physicsComp->getForce().x += -physicsComp->getMass() * this->friction * physicsComp->getVel().x / dt;
	}

	void DefaultIdleState::lateUpdate(float dt) {}
}