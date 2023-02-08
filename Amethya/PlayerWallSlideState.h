#pragma once

#include "AbstractState.h"

namespace GameObjects::Components::States::Player {
	class PlayerWallSlideState : public AbstractState {
	private:
		int dir;

	public:
		PlayerWallSlideState(StateMachineComp& stateMachine, int dir);

		void onEnter() override;
		void onExit() override;

		void update(float dt) override;
		void lateUpdate(float dt) override;

		void initStateChanges() override;
	};
}