#pragma once

#include "pch.h"

namespace Timer {
	class Timer {
	private:
		float elapsedTime, interval;
		unsigned int repeatTime, repeatCount;
		bool stopped;

		std::function<void(int)> callback;

	public:
		Timer(float interval, std::function<void(int)> callback);
		Timer(float interval, std::function<void(int)> callback, unsigned int repeatCount);

		bool update(float dt);
		void stop();
	};
}