#include "AbstractState.h"

namespace GameObjects::Components::States {
	AbstractState::StateChange::StateChange(std::function<bool(void)> condition, std::function<AbstractState* (void)> stateSupplier) : 
		condition(condition), stateSupplier(stateSupplier) {}

	AbstractState::AbstractState(StateMachineComp& stateMachine) : stateMachine(stateMachine) {
		this->initStateChanges();
	}

	void AbstractState::initStateChanges() {}

	GameObject& AbstractState::getGameObject() {
		return this->stateMachine.getGameObject();
	}
}