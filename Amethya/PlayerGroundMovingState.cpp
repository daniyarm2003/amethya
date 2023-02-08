#include "PlayerGroundMovingState.h"
#include "PlayerGroundIdleState.h"
#include "PlayerAirStates.h"
#include "InputManager.h"
#include "AbstractPhysicsComp.h"
#include "PlayerCrouchStates.h"
#include "PlayerProperties.h"

namespace GameObjects::Components::States::Player {
	PlayerGroundMovingState::PlayerGroundMovingState(StateMachineComp& stateMachine, int dir) : PlayerMovingState(stateMachine, dir, "player-run-left", "player-run-right") {
		this->friction = 0.05f;
		this->initStateChanges();
	}

	DefaultIdleState* PlayerGroundMovingState::getIdleState() {
		return new PlayerGroundIdleState(this->stateMachine, this->dir);
	}

	void PlayerGroundMovingState::initStateChanges() {
		PlayerMovingState::initStateChanges();

		auto& inputManager = Input::InputManager::getInstance();

		const auto physicsComp = this->getGameObject().getComponent<AbstractPhysicsComp>();
		const auto playerProps = this->getGameObject().getComponent<Properties::PlayerProperties>();

		this->stateChanges.push_back({
			[this, physicsComp]() -> bool {
				return physicsComp && !physicsComp->getCollision(PlatformCollision::GROUND);
			},
			[this]() -> AbstractState* {
				return new PlayerFallMovingState(this->stateMachine, this->dir);
			}
		});

		this->stateChanges.push_back({
			[this, &inputManager, playerProps]() -> bool {
				return playerProps && inputManager.isInputActive("Jump") && playerProps->getJumps() > 0;
			},
			[this, playerProps]() -> AbstractState* {
				playerProps->jump();
				return new PlayerJumpIdleState(this->stateMachine, this->dir);
			}
		});

		this->stateChanges.push_back({
			[this, &inputManager, physicsComp, playerProps]() -> bool {
				if (!physicsComp || !playerProps || !inputManager.isInputActive("Crouch"))
					return false;

				return playerProps->canScale(glm::vec2(2.0f, 0.5f), this->dir < 0, true);
			},
			[this, physicsComp]() -> AbstractState* {
				return new PlayerSlideState(this->stateMachine, this->dir);
			}
		});
	}
}