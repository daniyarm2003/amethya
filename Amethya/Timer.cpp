#include "Timer.h"

namespace Timer {
	Timer::Timer(float interval, std::function<void(int)> callback) : Timer(interval, callback, 0) { }

	Timer::Timer(float interval, std::function<void(int)> callback, unsigned int repeatCount) {
		this->interval = interval;
		this->callback = callback;
		this->repeatCount = repeatCount;
		this->elapsedTime = 0.0f;
		this->repeatTime = 1;
		this->stopped = false;
	}

	bool Timer::update(float dt) {

		if (this->stopped)
			return true;

		this->elapsedTime += dt;
		
		if (this->elapsedTime >= this->interval) {
			this->callback(this->repeatTime++);

			if (this->repeatCount != 0 && this->repeatTime > this->repeatCount)
				return true;

			this->elapsedTime = std::fmodf(this->elapsedTime, this->interval);
		}

		return false;
	}

	void Timer::stop() {
		this->stopped = true;
	}
}