#include "StateMachineComp.h"

namespace GameObjects::Components {
	StateMachineComp::StateMachineComp(GameObject& gameObject, int priority) : GameObjComp(gameObject, priority) {}

	void StateMachineComp::update(float dt) {
		if (this->currentState)
			this->currentState->update(dt);
	}

	void StateMachineComp::lateUpdate(float dt) {
		if (this->currentState)
			this->currentState->lateUpdate(dt);

		for (const auto& stateChange : this->currentState->stateChanges) {
			if (stateChange.condition()) {
				this->changeState(stateChange.stateSupplier());
				break;
			}
		}
	}

	void StateMachineComp::draw(sf::RenderWindow& window) {}

	void StateMachineComp::changeState(States::AbstractState* newState) {
		if (!newState)
			return;

		if (this->currentState)
			this->currentState->onExit();

		this->currentState.reset(newState);
		this->currentState->onEnter();
	}
}