#pragma once

#include "pch.h"
#include "Scene.h"

class Amethya {
private:
	const std::string ICON_FILE = "Resources/Textures/icon.png";

	const unsigned int FPS_LIMIT = 60;
	const float FPS_DEFAULT = 1.0f / (float)FPS_LIMIT;

	const float NANOS_TO_SECONDS = 1e-9f;

	const std::string WINDOW_TITLE = "Amethya";

	std::chrono::steady_clock::time_point start;
	float dt;

	sf::RenderWindow window;
	std::unique_ptr<Scenes::Scene> scene;

	Amethya();

public:
	static constexpr unsigned int WIDTH = 800;
	static constexpr unsigned int HEIGHT = 600;

	Amethya(const Amethya&) = delete;
	void operator =(const Amethya&) = delete;

	static Amethya& getInstance();

	bool isWindowOpen();
	float getDeltaTime();

	void init();

	Scenes::Scene* getScene();
	void setScene(Scenes::Scene* scene);

	void pollEvents();
	void update(float dt);
	void draw();
};