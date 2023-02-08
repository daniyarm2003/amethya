#pragma once

#include "pch.h"
#include "Scene.h"

namespace Scenes {
	class TestScene : public Scene {
	public:
		TestScene();

		void onEnter() override;
		void onExit() override;
	};
}