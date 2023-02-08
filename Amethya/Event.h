#pragma once

#include "pch.h"

namespace Events {

	template<typename... Params>
	class Event {
	private:
		std::vector<std::function<void(Params...)>> handlers;

	public:
		void subscribeHandler(std::function<void(Params...)> handler);
		void invoke(Params... params);
	};
}

#include "Event.cpp"