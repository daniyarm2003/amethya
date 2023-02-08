#pragma once

#include "DefaultMovingState.h"
#include "DefaultIdleState.h"

namespace GameObjects::Components::States::Player {
	class PlayerMovingState : public DefaultMovingState {
	public:
		PlayerMovingState(StateMachineComp& stateMachine, int dir, std::string animationLeft, std::string animationRight);

		void initStateChanges() override;

		virtual DefaultIdleState* getIdleState() = 0;
	};
}