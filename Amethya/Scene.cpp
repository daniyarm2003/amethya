#include "Scene.h"

namespace Scenes {
	Scene::Scene(std::string name) : name(name) {}

	std::shared_ptr<GameObjects::GameObject>& Scene::addGameObject(GameObjects::GameObject* gameObject) {
		auto gameObjPtr = std::shared_ptr<GameObjects::GameObject>(gameObject);

		const auto it = this->gameObjects.insert(std::upper_bound(this->gameObjects.begin(), this->gameObjects.end(), gameObjPtr, 
			[](const std::shared_ptr<GameObjects::GameObject>& first, const std::shared_ptr<GameObjects::GameObject>& second) -> bool {
				return first->getZDepth() > second->getZDepth();
			}), gameObjPtr);

		return *it;
	}

	void Scene::addCamera(GameObjects::GameObject* gameObject) {
		const auto& camSharedPtr = this->addGameObject(gameObject);
		this->cameraPtr = camSharedPtr;
	}

	std::shared_ptr<GameObjects::GameObject> Scene::getCamera() {
		return this->cameraPtr.lock();
	}

	glm::vec2 Scene::getCameraOffset() {
		const auto camera = this->getCamera();
		return (camera ? camera->getPos() : glm::vec2()) - CAMERA_OFFSET;
	}

	Scene::gameObjIter Scene::begin() {
		return this->gameObjects.begin();
	}

	Scene::gameObjIter Scene::end() {
		return this->gameObjects.end();
	}

	std::string Scene::getName() {
		return this->name;
	}

	void Scene::update(float dt) {
		for (auto& gameObj : *this) {
			gameObj->update(dt);
		}
	}

	void Scene::lateUpdate(float dt) {
		for (auto& gameObj : *this) {
			gameObj->lateUpdate(dt);
		}

		this->gameObjects.erase(std::remove_if(this->gameObjects.begin(), this->gameObjects.end(), [](std::shared_ptr<GameObjects::GameObject>& gameObj) -> bool {
			return gameObj->getRemovable();
		}), this->gameObjects.end());
	}

	void Scene::draw(sf::RenderWindow& window) {
		for (auto& gameObj : *this) {
			gameObj->draw(window);
		}
	}
}