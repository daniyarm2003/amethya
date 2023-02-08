#include "PlayerGroundIdleState.h"
#include "PlayerGroundMovingState.h"
#include "PlayerAirStates.h"
#include "InputManager.h"
#include "AbstractPhysicsComp.h"
#include "PlayerCrouchStates.h"
#include "PlayerProperties.h"

namespace GameObjects::Components::States::Player {
	PlayerGroundIdleState::PlayerGroundIdleState(StateMachineComp& stateMachine, int dir) : PlayerIdleState(stateMachine, dir, "player-idle-left", "player-idle-right") {
		this->friction = 0.05f;
		this->initStateChanges();
	}

	DefaultMovingState* PlayerGroundIdleState::getMovingState(int dir) {
		return new PlayerGroundMovingState(this->stateMachine, dir);
	}

	void PlayerGroundIdleState::initStateChanges() {
		PlayerIdleState::initStateChanges();

		auto& inputManager = Input::InputManager::getInstance();

		const auto physicsComp = this->getGameObject().getComponent<AbstractPhysicsComp>();
		const auto playerProps = this->getGameObject().getComponent<Properties::PlayerProperties>();

		this->stateChanges.push_back({
			[this, physicsComp]() -> bool {
				return physicsComp && !physicsComp->getCollision(PlatformCollision::GROUND);
			},
			[this]() -> AbstractState* {
				return new PlayerFallIdleState(this->stateMachine, this->animationName == "player-idle-left" ? -1 : 1);
			}
		});

		this->stateChanges.push_back({
			[this, &inputManager, playerProps]() -> bool {
				return playerProps && playerProps->getJumps() > 0 && inputManager.isInputActive("Jump");
			},
			[this, playerProps]() -> AbstractState* {
				playerProps->jump();
				return new PlayerJumpIdleState(this->stateMachine, this->animationName == "player-idle-left" ? -1 : 1);
			}
		});

		this->stateChanges.push_back({
			[this, &inputManager]() -> bool {
				return inputManager.isInputActive("Crouch");
			},
			[this]() -> AbstractState* {
				return new PlayerCrouchState(this->stateMachine, this->animationName == "player-idle-left" ? -1 : 1);
			}
		});
	}
}