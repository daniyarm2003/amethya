#pragma once

#include "PlayerIdleState.h"

namespace GameObjects::Components::States::Player {
	class PlayerGroundIdleState : public PlayerIdleState {
	public:
		PlayerGroundIdleState(StateMachineComp& stateMachine, int dir);

		DefaultMovingState* getMovingState(int dir) override;

		void initStateChanges() override;
	};
}