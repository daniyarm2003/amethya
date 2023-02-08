#pragma once

#include "PlayerIdleState.h"
#include "PlayerMovingState.h"

namespace GameObjects::Components::States::Player {
	class PlayerJumpIdleState : public PlayerIdleState {
	public:
		PlayerJumpIdleState(StateMachineComp& stateMachine, int dir);

		DefaultMovingState* getMovingState(int dir) override;

		void initStateChanges() override;
	};

	class PlayerJumpMovingState : public PlayerMovingState {
	public:
		PlayerJumpMovingState(StateMachineComp& stateMachine, int dir);

		DefaultIdleState* getIdleState() override;

		void initStateChanges() override;
	};

	class PlayerFallIdleState : public PlayerIdleState {
	public:
		PlayerFallIdleState(StateMachineComp& stateMachine, int dir);

		DefaultMovingState* getMovingState(int dir) override;

		void initStateChanges() override;
	};

	class PlayerFallMovingState : public PlayerMovingState {
	public:
		PlayerFallMovingState(StateMachineComp& stateMachine, int dir);

		DefaultIdleState* getIdleState() override;

		void initStateChanges() override;
	};
}