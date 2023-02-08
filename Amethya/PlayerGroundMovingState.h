#pragma once

#include "PlayerMovingState.h"

namespace GameObjects::Components::States::Player {
	class PlayerGroundMovingState : public PlayerMovingState {
	public:
		PlayerGroundMovingState(StateMachineComp& stateMachine, int dir);

		DefaultIdleState* getIdleState() override;

		void initStateChanges() override;
	};
}