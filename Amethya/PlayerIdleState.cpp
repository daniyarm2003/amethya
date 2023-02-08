#include "PlayerIdleState.h"
#include "InputManager.h"
#include "PlayerMovingState.h"

namespace GameObjects::Components::States::Player {
	PlayerIdleState::PlayerIdleState(StateMachineComp& stateMachine, int dir, std::string animationLeft, std::string animationRight) : DefaultIdleState(stateMachine, dir < 0 ? animationLeft : animationRight) {
		
	}

	void PlayerIdleState::initStateChanges() {
		auto& inputManager = Input::InputManager::getInstance();

		this->stateChanges.push_back({
			[this, &inputManager]() -> bool {
				return inputManager.isInputActive("Left") || inputManager.isInputActive("Right");
			},
			[this, &inputManager]() -> AbstractState* {
				return this->getMovingState(inputManager.isInputActive("Left") ? -1 : 1);
			}
		});
	}
}