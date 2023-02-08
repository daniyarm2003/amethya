#pragma once

#include "DefaultIdleState.h"
#include "DefaultMovingState.h"

namespace GameObjects::Components::States::Player {
	class PlayerIdleState : public DefaultIdleState {
	public:
		PlayerIdleState(StateMachineComp& stateMachine, int dir, std::string animationLeft, std::string animationRight);

		void initStateChanges() override;

		virtual DefaultMovingState* getMovingState(int dir) = 0;
	};
}