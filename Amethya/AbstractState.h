#pragma once

#include "StateMachineComp.h"

namespace GameObjects::Components {
	class StateMachineComp;

	namespace States {
		class AbstractState {
		private:
			friend class GameObjects::Components::StateMachineComp;

		protected:
			struct StateChange {
				std::function<bool(void)> condition;
				std::function<AbstractState* (void)> stateSupplier;

				StateChange(std::function<bool(void)> condition, std::function<AbstractState* (void)> stateSupplier);
			};

			StateMachineComp& stateMachine;
			std::vector<StateChange> stateChanges;

		public:
			AbstractState(StateMachineComp& stateMachine);

			virtual void initStateChanges();

			virtual void onEnter() = 0;
			virtual void onExit() = 0;

			virtual void update(float dt) = 0;
			virtual void lateUpdate(float dt) = 0;

			GameObject& getGameObject();
		};
	}
}