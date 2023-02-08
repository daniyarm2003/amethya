#pragma once

#include "timer.h"

namespace Timer {
	class TimerManager {
	private:
		std::vector<Timer> timers;
		TimerManager();

	public:
		Timer& addTimer(Timer timer);
		void updateTimers(float dt);

		TimerManager(const TimerManager&) = delete;
		void operator =(const TimerManager&) = delete;

		static TimerManager& getInstance();
	};
}