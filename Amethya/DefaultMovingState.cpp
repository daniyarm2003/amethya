#include "DefaultMovingState.h"
#include "AbstractPhysicsComp.h"
#include "ResourceManager.h"
#include "AnimationRendererComp.h"
#include "EntityProperties.h"

namespace GameObjects::Components::States {
	DefaultMovingState::DefaultMovingState(StateMachineComp& stateMachine, int dir, std::string animationLeft, std::string animationRight) : AbstractState(stateMachine), dir(dir),
		animationLeft(animationLeft), animationRight(animationRight), friction(0.025f) {}

	void DefaultMovingState::setDirection(int direction) {
		this->dir = direction;

		const auto animationComp = this->getGameObject().getComponent<AnimationRendererComp>();

		if (animationComp)
			animationComp->setAnimation(Resources::ResourceManager::getInstance().getAnimation(this->dir < 0 ? this->animationLeft : this->animationRight));
	}

	void DefaultMovingState::onEnter() {
		this->setDirection(this->dir);
	}

	void DefaultMovingState::onExit() {}

	void DefaultMovingState::update(float dt) {
		const auto physicsComp = this->getGameObject().getComponent<AbstractPhysicsComp>();
		const auto entityProps = this->getGameObject().getComponent<Properties::EntityProperties>();

		if (!entityProps)
			return;

		if (physicsComp && physicsComp->getVel().x * this->dir < entityProps->getMaxSpeed())
			physicsComp->getForce().x += (float)this->dir * entityProps->getMoveForce();

		else
			physicsComp->getForce().x += -physicsComp->getMass() * this->friction * physicsComp->getVel().x / dt;
	}

	void DefaultMovingState::lateUpdate(float dt) {}
}