#include "Amethya.h"
#include "TimerManager.h"
#include "InputManager.h"
#include "ResourceManager.h"
#include "TestScene.h"

Amethya::Amethya() : dt(FPS_DEFAULT), start(std::chrono::steady_clock::now()) { }

void Amethya::init() {
	this->window.create(sf::VideoMode(WIDTH, HEIGHT), WINDOW_TITLE);
	this->window.setFramerateLimit(FPS_LIMIT);

	sf::Image icon;
	if (icon.loadFromFile(this->ICON_FILE))
		this->window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

	this->setScene(new Scenes::TestScene);
}

Amethya& Amethya::getInstance() {
	static Amethya instance;
	return instance;
}

bool Amethya::isWindowOpen() {
	return this->window.isOpen();
}

float Amethya::getDeltaTime() {
	return this->dt;
}

Scenes::Scene* Amethya::getScene() {
	return this->scene.get();
}

void Amethya::setScene(Scenes::Scene* scene) {
	if (this->scene)
		this->scene->onExit();

	this->scene.reset(scene);
	this->scene->onEnter();
}

void Amethya::pollEvents() {
	sf::Event evt;

	while (this->window.pollEvent(evt)) {
		switch (evt.type) {
		case sf::Event::Closed:
			this->window.close();
			break;

		case sf::Event::KeyPressed:
			if (evt.key.code != sf::Keyboard::Unknown)
				Input::InputManager::getInstance().setButtonPressed(evt.key.code, true);

			break;

		case sf::Event::KeyReleased:
			if (evt.key.code != sf::Keyboard::Unknown)
				Input::InputManager::getInstance().setButtonPressed(evt.key.code, false);

			break;

		default:
			break;
		}
	}

	Input::InputManager::getInstance().updateButtonStates();
}

void Amethya::update(float dt) {
	this->start = std::chrono::steady_clock::now();

	if (this->scene) {
		this->scene->update(dt);
		this->scene->lateUpdate(dt);
	}
}

void Amethya::draw() {
	this->window.clear(sf::Color(80, 0, 180, 255));

	if (this->scene) {
		this->scene->draw(this->window);
	}

	this->window.display();

	auto end = std::chrono::steady_clock::now();
	this->dt = (float)std::chrono::duration_cast<std::chrono::nanoseconds>(end - this->start).count() * NANOS_TO_SECONDS;

	Timer::TimerManager::getInstance().updateTimers(this->dt);
}

int main()
{
	Amethya& game = Amethya::getInstance();
	game.init();

	while (game.isWindowOpen()) {
		game.pollEvents();
		game.update(game.getDeltaTime());
		game.draw();
	}
}