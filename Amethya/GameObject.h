#pragma once

#include "pch.h"

#include "Scene.h"
#include "GameObjComp.h"

namespace Scenes {
	class Scene;
}

namespace GameObjects {
	class GameObjComp;

	class GameObject {
	private:
		Scenes::Scene& scene;
		std::vector<std::shared_ptr<GameObjComp>> components;

		glm::vec2 pos;

		int zDepth;
		bool removable;

	public:
		GameObject(Scenes::Scene& scene, glm::vec2 pos);

		void addComponent(GameObjComp* component);
		
		template <typename T>
		std::shared_ptr<T> getComponent() {
			for (auto& gameObjComp : this->components) {
				std::shared_ptr<T> comp = std::dynamic_pointer_cast<T, GameObjComp>(gameObjComp);

				if (comp)
					return comp;
			}

			return std::shared_ptr<T>();
		}

		void update(float dt);
		void lateUpdate(float dt);
		void draw(sf::RenderWindow& window);

		int getZDepth() const;
		void setZDepth(int zDepth);

		bool getRemovable();
		void setRemovable(bool removable);

		Scenes::Scene& getScene();

		glm::vec2& getPos();
	};
}