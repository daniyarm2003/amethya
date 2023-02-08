#include "PlayerAirStates.h"
#include "AbstractPhysicsComp.h"
#include "PlayerGroundIdleState.h"
#include "PlayerGroundMovingState.h"
#include "PlayerWallSlideState.h"
#include "PlayerProperties.h"
#include "InputManager.h"

namespace GameObjects::Components::States::Player {
	PlayerJumpIdleState::PlayerJumpIdleState(StateMachineComp& stateMachine, int dir)
		: PlayerIdleState(stateMachine, dir, "player-jump-left", "player-jump-right") {
		
		this->initStateChanges();
	}

	DefaultMovingState* PlayerJumpIdleState::getMovingState(int dir) {
		return new PlayerJumpMovingState(this->stateMachine, dir);
	}

	void PlayerJumpIdleState::initStateChanges() {
		PlayerIdleState::initStateChanges();

		auto& inputManager = Input::InputManager::getInstance();

		const auto physicsComp = this->getGameObject().getComponent<AbstractPhysicsComp>();
		const auto playerProps = this->getGameObject().getComponent<Properties::PlayerProperties>();

		this->stateChanges.push_back({
			[this, playerProps, &inputManager]() {
				return playerProps && playerProps->getJumps() > 0 && inputManager.isInputActive("Jump");
			},
			[this, playerProps]() {
				playerProps->jump();
				return new PlayerJumpIdleState(this->stateMachine, this->animationName == "player-jump-left" ? -1 : 1);
			}
		});

		this->stateChanges.push_back({
			[this, physicsComp]() {
				return physicsComp && physicsComp->getVel().y > 0.0f;
			},
			[this]() {
				return new PlayerFallIdleState(this->stateMachine, this->animationName == "player-jump-left" ? -1 : 1);
			}
		});
	}

	PlayerJumpMovingState::PlayerJumpMovingState(StateMachineComp& stateMachine, int dir) :
		PlayerMovingState(stateMachine, dir, "player-jump-left", "player-jump-right") {

		this->initStateChanges();
	}

	DefaultIdleState* PlayerJumpMovingState::getIdleState() {
		return new PlayerJumpIdleState(this->stateMachine, this->dir);
	}

	void PlayerJumpMovingState::initStateChanges() {
		PlayerMovingState::initStateChanges();

		auto& inputManager = Input::InputManager::getInstance();

		const auto physicsComp = this->getGameObject().getComponent<AbstractPhysicsComp>();
		const auto playerProps = this->getGameObject().getComponent<Properties::PlayerProperties>();

		this->stateChanges.push_back({
			[this, playerProps, &inputManager]() {
				return playerProps && playerProps->getJumps() > 0 && inputManager.isInputActive("Jump");
			},
			[this, playerProps]() {
				playerProps->jump();
				return new PlayerJumpMovingState(this->stateMachine, this->dir);
			}
		});

		this->stateChanges.push_back({
			[this, physicsComp]() {
				return physicsComp && physicsComp->getVel().y > 0.0f;
			},
			[this]() {
				return new PlayerFallIdleState(this->stateMachine, this->dir);
			}
		});

		this->stateChanges.push_back({
			[this, physicsComp]() {
				return physicsComp && physicsComp->getCollision(this->dir < 0 ? PlatformCollision::RIGHT : PlatformCollision::LEFT);
			},
			[this]() {
				return new PlayerWallSlideState(this->stateMachine, this->dir);
			}
		});
	}

	PlayerFallIdleState::PlayerFallIdleState(StateMachineComp& stateMachine, int dir) : PlayerIdleState(stateMachine, dir, "player-fall-left", "player-fall-right") {
		this->initStateChanges();
	}

	DefaultMovingState* PlayerFallIdleState::getMovingState(int dir) {
		return new PlayerFallMovingState(this->stateMachine, dir);
	}

	void PlayerFallIdleState::initStateChanges() {
		PlayerIdleState::initStateChanges();

		auto& inputManager = Input::InputManager::getInstance();

		const auto physicsComp = this->getGameObject().getComponent<AbstractPhysicsComp>();
		const auto playerProps = this->getGameObject().getComponent<Properties::PlayerProperties>();

		this->stateChanges.push_back({
			[this, playerProps, &inputManager]() {
				return playerProps && playerProps->getJumps() > 0 && inputManager.isInputActive("Jump");
			},
			[this, playerProps]() {
				playerProps->jump();
				return new PlayerJumpIdleState(this->stateMachine, this->animationName == "player-fall-left" ? -1 : 1);
			}
		});

		this->stateChanges.push_back({
			[this, physicsComp, playerProps]() {
				return playerProps && physicsComp && physicsComp->getCollision(PlatformCollision::GROUND);
			},
			[this, playerProps]() {
				playerProps->resetJumps();
				return new PlayerGroundIdleState(this->stateMachine, this->animationName == "player-fall-left" ? -1 : 1);
			}
		});
	}

	PlayerFallMovingState::PlayerFallMovingState(StateMachineComp& stateMachine, int dir) : PlayerMovingState(stateMachine, dir, "player-fall-left", "player-fall-right") {
		this->initStateChanges();
	}

	DefaultIdleState* PlayerFallMovingState::getIdleState() {
		return new PlayerFallIdleState(this->stateMachine, this->dir);
	}

	void PlayerFallMovingState::initStateChanges() {
		PlayerMovingState::initStateChanges();

		auto& inputManager = Input::InputManager::getInstance();

		const auto physicsComp = this->getGameObject().getComponent<AbstractPhysicsComp>();
		const auto playerProps = this->getGameObject().getComponent<Properties::PlayerProperties>();

		this->stateChanges.push_back({
			[this, playerProps, &inputManager]() {
				return playerProps && playerProps->getJumps() > 0 && inputManager.isInputActive("Jump");
			},
			[this, playerProps]() {
				playerProps->jump();
				return new PlayerJumpMovingState(this->stateMachine, this->dir);
			}
		});

		this->stateChanges.push_back({
			[this, physicsComp, playerProps]() {
				return physicsComp && playerProps && physicsComp->getCollision(PlatformCollision::GROUND);
			},
			[this, playerProps]() {
				playerProps->resetJumps();
				return new PlayerGroundMovingState(this->stateMachine, this->dir);
			}
		});

		this->stateChanges.push_back({
			[this, physicsComp]() {
				return physicsComp && physicsComp->getCollision(this->dir < 0 ? PlatformCollision::RIGHT : PlatformCollision::LEFT);
			},
			[this]() {
				return new PlayerWallSlideState(this->stateMachine, this->dir);
			}
		});
	}
}