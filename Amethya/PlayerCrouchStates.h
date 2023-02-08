#pragma once

#include "PlayerIdleState.h"

namespace GameObjects::Components::States::Player {
	class PlayerCrouchState : public PlayerIdleState {
	public:
		PlayerCrouchState(StateMachineComp& stateMachine, int dir);

		void onEnter() override;
		void onExit() override;

		void initStateChanges() override;

		DefaultMovingState* getMovingState(int dir) override;
	};

	class PlayerSlideState : public PlayerIdleState {
	private:
		int dir;

	public:
		PlayerSlideState(StateMachineComp& stateMachine, int dir);

		void onEnter() override;
		void onExit() override;

		void initStateChanges() override;

		DefaultMovingState* getMovingState(int dir) override;
	};
}