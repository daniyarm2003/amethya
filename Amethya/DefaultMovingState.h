#pragma once

#include "AbstractState.h"
#include "AnimationRendererComp.h"

namespace GameObjects::Components::States {
	class DefaultMovingState : public AbstractState {
	protected:
		const std::string animationLeft, animationRight;

		float friction;
		int dir;

	public:
		DefaultMovingState(StateMachineComp& stateMachine, int dir, std::string animationLeft, std::string animationRight);

		virtual void setDirection(int direction);

		virtual void onEnter() override;
		virtual void onExit() override;

		virtual void update(float dt) override;
		virtual void lateUpdate(float dt) override;
	};
}