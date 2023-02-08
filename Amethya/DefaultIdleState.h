#pragma once

#include "AbstractState.h"

namespace GameObjects::Components::States {
	class DefaultIdleState : public AbstractState {
	protected:
		const std::string animationName;
		float friction;

	public:
		DefaultIdleState(StateMachineComp& stateMachine, std::string animationName);

		virtual void onEnter() override;
		virtual void onExit() override;

		virtual void update(float dt) override;
		virtual void lateUpdate(float dt) override;
	};
}