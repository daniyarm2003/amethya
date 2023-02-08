#pragma once

#include "pch.h"
#include "GameObject.h"

namespace GameObjects {
	class GameObject;
}

namespace Scenes {
	class Scene {
	private:
		static constexpr glm::vec2 CAMERA_OFFSET = glm::vec2(400.0f, 250.0f);

		using gameObjIter = std::vector<std::shared_ptr<GameObjects::GameObject>>::iterator;
		std::weak_ptr<GameObjects::GameObject> cameraPtr;

	protected:
		std::string name;
		std::vector<std::shared_ptr<GameObjects::GameObject>> gameObjects;

	public:
		Scene(std::string name);

		std::shared_ptr<GameObjects::GameObject>& addGameObject(GameObjects::GameObject* gameObject);

		void addCamera(GameObjects::GameObject* camera);

		std::shared_ptr<GameObjects::GameObject> getCamera();
		glm::vec2 getCameraOffset();

		gameObjIter begin(), end();

		virtual void onEnter() = 0;
		virtual void update(float dt);
		virtual void lateUpdate(float dt);
		virtual void onExit() = 0;

		std::string getName();

		void draw(sf::RenderWindow& window);
	};
}