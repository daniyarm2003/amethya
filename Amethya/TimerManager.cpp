#include "TimerManager.h"

namespace Timer {
	TimerManager::TimerManager() : timers() {}

	Timer& TimerManager::addTimer(Timer timer) {
		this->timers.push_back(timer);
		return this->timers[this->timers.size() - 1];
	}

	void TimerManager::updateTimers(float dt) {
		this->timers.erase(std::remove_if(this->timers.begin(), this->timers.end(), [=](Timer& timer) -> bool {
			return timer.update(dt);
		}), this->timers.end());
	}

	TimerManager& TimerManager::getInstance() {
		static TimerManager instance;
		return instance;
	}
}