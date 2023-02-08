#include "PlayerWallSlideState.h"
#include "ResourceManager.h"
#include "InputManager.h"
#include "AbstractPhysicsComp.h"
#include "PlayerAirStates.h"
#include "PlayerGroundMovingState.h"
#include "AnimationRendererComp.h"
#include "CollisionComp.h"
#include "PlayerProperties.h"

namespace GameObjects::Components::States::Player {
	PlayerWallSlideState::PlayerWallSlideState(StateMachineComp& stateMachine, int dir) : AbstractState(stateMachine), dir(dir) {
		this->initStateChanges();
	}

	void PlayerWallSlideState::onEnter() {
		const auto animationComp = this->getGameObject().getComponent<AnimationRendererComp>();

		if (animationComp)
			animationComp->setAnimation(Resources::ResourceManager::getInstance().getAnimation(this->dir < 0 ? "player-wall-slide-left" : "player-wall-slide-right"));
	}

	void PlayerWallSlideState::onExit() {}

	void PlayerWallSlideState::update(float dt) {
		const auto physicsComp = this->getGameObject().getComponent<AbstractPhysicsComp>();

		if (physicsComp) {
			physicsComp->getVel().x = 2.0f * (float)this->dir * CollisionComp::MIN_MTV_LENGTH / dt;
			physicsComp->getVel().y = glm::min(physicsComp->getVel().y, 0.5f * AbstractPhysicsComp::METER_SCALE);
		}
	}

	void PlayerWallSlideState::lateUpdate(float dt) {}

	void PlayerWallSlideState::initStateChanges() {
		const auto physicsComp = this->getGameObject().getComponent<AbstractPhysicsComp>();
		const auto playerProps = this->getGameObject().getComponent<Properties::PlayerProperties>();

		auto& inputManager = Input::InputManager::getInstance();

		if (!physicsComp || !playerProps)
			return;

		this->stateChanges.push_back({
			[this, physicsComp]() {
				return physicsComp->getCollision(PlatformCollision::GROUND);
			},
			[this, playerProps]() {
				playerProps->resetJumps();
				return new PlayerGroundMovingState(this->stateMachine, this->dir);
			}
		});

		this->stateChanges.push_back({
			[this, &inputManager, physicsComp]() {
				return !inputManager.isInputActive(this->dir < 0 ? "Left" : "Right") || !physicsComp->getCollision(this->dir < 0 ? PlatformCollision::RIGHT : PlatformCollision::LEFT);
			},
			[this, physicsComp]() -> AbstractState* {
				if (physicsComp->getVel().y < 0.0f)
					return new PlayerJumpIdleState(this->stateMachine, this->dir); 
				
				else return new PlayerFallIdleState(this->stateMachine, this->dir);
			}
		});

		this->stateChanges.push_back({
			[this, &inputManager]() {
				return inputManager.isInputActive("Jump");
			},
			[this, physicsComp, playerProps]() {
				physicsComp->getVel().x = -(float)this->dir * playerProps->getWallKickVel().x;
				physicsComp->getVel().y = -glm::sqrt(2.0f * playerProps->getWallKickVel().y * AbstractPhysicsComp::GRAVITY);

				playerProps->setJumps(0);

				return new PlayerJumpMovingState(this->stateMachine, this->dir);
			}
		});
	}
}