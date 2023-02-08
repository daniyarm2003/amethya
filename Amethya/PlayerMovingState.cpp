#include "PlayerMovingState.h"
#include "PlayerIdleState.h"
#include "InputManager.h"

namespace GameObjects::Components::States::Player {
	PlayerMovingState::PlayerMovingState(StateMachineComp& stateMachine, int dir, std::string animationLeft, std::string animationRight) 
		: DefaultMovingState(stateMachine, dir, animationLeft, animationRight) {

		
	}

	void PlayerMovingState::initStateChanges() {
		auto& inputManager = Input::InputManager::getInstance();

		this->stateChanges.push_back({
			[this, &inputManager]() -> bool {
				return !inputManager.isInputActive(this->dir < 0 ? "Left" : "Right");
			},
			[this]() -> AbstractState* {
				return this->getIdleState();
			}
		});
	}
}