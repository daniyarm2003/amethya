#include "PlayerCrouchStates.h"
#include "InputManager.h"
#include "AbstractPhysicsComp.h"
#include "PlayerGroundIdleState.h"
#include "PlayerGroundMovingState.h"
#include "PlayerAirStates.h"
#include "PlayerProperties.h"

namespace GameObjects::Components::States::Player {
	PlayerCrouchState::PlayerCrouchState(StateMachineComp& stateMachine, int dir) : PlayerIdleState(stateMachine, dir, "player-crouch-left", "player-crouch-right") {
		this->friction = 0.05f;
		this->initStateChanges();
	}

	void PlayerCrouchState::onEnter() {
		PlayerIdleState::onEnter();

		const auto playerProps = this->getGameObject().getComponent<Properties::PlayerProperties>();

		if (playerProps)
			playerProps->scaleHitbox(glm::vec2(1.0f, 0.5f), false, true);
	}

	void PlayerCrouchState::onExit() {
		const auto playerProps = this->getGameObject().getComponent<Properties::PlayerProperties>();

		if (playerProps)
			playerProps->scaleHitbox(glm::vec2(1.0f, 2.0f), false, true);
	}

	void PlayerCrouchState::initStateChanges() {
		auto& inputManager = Input::InputManager::getInstance();

		const auto playerProps = this->getGameObject().getComponent<Properties::PlayerProperties>();
		const auto physicsComp = this->getGameObject().getComponent<AbstractPhysicsComp>();

		if (!physicsComp || !playerProps)
			return;

		this->stateChanges.push_back({
			[this, &inputManager, playerProps]() {
				if (inputManager.isInputActive("Crouch"))
					return false;

				return playerProps->canScale(glm::vec2(1.0f, 2.0f), false, true);
			},
			[this]() {
				return new PlayerGroundIdleState(this->stateMachine, this->animationName == "player-crouch-left" ? -1 : 1);
			}
		});

		this->stateChanges.push_back({
			[this, physicsComp, playerProps]() {
				if (glm::abs(physicsComp->getVel().x) < Properties::PlayerProperties::SLIDE_MIN_SPEED)
					return false;

				return playerProps->canScale(glm::vec2(2.0f, 1.0f), this->animationName == "player-crouch-left", false);
			},
			[this]() {
				return new PlayerSlideState(this->stateMachine, this->animationName == "player-crouch-left" ? -1 : 1);
			}
		});
	}

	DefaultMovingState* PlayerCrouchState::getMovingState(int dir) {
		return nullptr;
	}

	PlayerSlideState::PlayerSlideState(StateMachineComp& stateMachine, int dir) : PlayerIdleState(stateMachine, dir, "player-slide-left", "player-slide-right"), dir(dir) {
		this->friction = 0.015f;
		this->initStateChanges();
	}

	void PlayerSlideState::onEnter() {
		PlayerIdleState::onEnter();

		const auto playerProps = this->getGameObject().getComponent<Properties::PlayerProperties>();

		if (playerProps)
			playerProps->scaleHitbox(glm::vec2(2.0f, 0.5f), this->dir < 0, true);
	}

	void PlayerSlideState::onExit() {
		const auto playerProps = this->getGameObject().getComponent<Properties::PlayerProperties>();

		if (playerProps)
			playerProps->scaleHitbox(glm::vec2(0.5f, 2.0f), this->dir < 0, true);
	}

	void PlayerSlideState::initStateChanges() {
		auto& inputManager = Input::InputManager::getInstance();

		const auto physicsComp = this->getGameObject().getComponent<AbstractPhysicsComp>();
		const auto playerProps = this->getGameObject().getComponent<Properties::PlayerProperties>();

		if (!physicsComp|| !playerProps)
			return;

		this->stateChanges.push_back({
			[this, &inputManager, playerProps]() {
				if (inputManager.isInputActive("Crouch"))
					return false;

				return playerProps->canScale(glm::vec2(0.5f, 2.0f), this->dir < 0, true);
			},
			[this]() {
				return new PlayerGroundMovingState(this->stateMachine, this->dir);
			}
		});

		this->stateChanges.push_back({
			[this, physicsComp]() {
				return glm::abs(physicsComp->getVel().x) < Properties::PlayerProperties::SLIDE_MIN_SPEED;
			},
			[this]() {
				return new PlayerCrouchState(this->stateMachine, this->dir);
			}
		});
	}

	DefaultMovingState* PlayerSlideState::getMovingState(int dir) {
		return nullptr;
	}
}