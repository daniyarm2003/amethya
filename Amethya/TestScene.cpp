#include "TestScene.h"
#include "GameObjInitializers.h"

namespace Scenes {
	TestScene::TestScene() : Scene("Test Scene") {}

	void TestScene::onEnter() {
		std::cout << "WELCOME TO THE SCENE!" << std::endl;

		this->addGameObject(GameObjects::Initializers::initBackground(*this, 0, 5, true, true));
		this->addGameObject(GameObjects::Initializers::initTestGameObj(*this, glm::vec2(300.0f, 100.0f)));
		this->addGameObject(GameObjects::Initializers::initTestHitbox(*this, glm::vec4(50.0f, 500.0f, 700.0f, 500.0f)));
		this->addGameObject(GameObjects::Initializers::initTestHitbox(*this, glm::vec4(300.0f, 200.0f, 50.0f, 150.0f)));
		this->addGameObject(GameObjects::Initializers::initTestHitbox(*this, glm::vec4(500.0f, 200.0f, 50.0f, 300.0f)));
		this->addGameObject(GameObjects::Initializers::initTestHitbox(*this, glm::vec4(150.0f, 200.0f, 50.0f, 250.0f)));
		this->addGameObject(GameObjects::Initializers::initJumpRefillOrb(*this, glm::vec2(312.5f, 0.0f)));
	}

	void TestScene::onExit() {
		std::cout << "GOODBYE!" << std::endl;
	}
}