#ifndef EVENT_CPP
#define EVENT_CPP

#include "Event.h"

namespace Events {
	template<typename... Params>
	void Event<Params...>::subscribeHandler(std::function<void(Params...)> handler) {
		this->handlers.push_back(handler);
	}

	template<typename... Params>
	void Event<Params...>::invoke(Params... params) {
		for (size_t i = 0; i < this->handlers.size(); i++) {

			//ignore visual studio this works fine
			this->handlers[i](params...);
		}
	}
}

#endif