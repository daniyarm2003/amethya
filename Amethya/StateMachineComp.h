#pragma once

#include "GameObjComp.h"
#include "AbstractState.h"

namespace GameObjects::Components {
	namespace States {
		class AbstractState;
	}

	class StateMachineComp : public GameObjComp {
	private:
		std::shared_ptr<States::AbstractState> currentState;

	public:
		StateMachineComp(GameObject& gameObject, int priority);

		void update(float dt) override;
		void lateUpdate(float dt) override;
		void draw(sf::RenderWindow& window) override;

		void changeState(States::AbstractState* newState);
	};
}