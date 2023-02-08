#pragma once

#include "GameObjComp.h"

namespace GameObjects::Components {
	enum class CollisionType {
		ZONE, SEMISOLID, SOLID
	};

	class CollisionComp : public GameObjComp {
	private:
		glm::vec2 size;
		CollisionType type;

		int collisionFlags;

	public:
		static constexpr float MIN_MTV_LENGTH = 0.1f;

		CollisionComp(GameObject& gameObject, int collisionFlags, CollisionType type, float width, float height);

		glm::vec2& getHitboxSize();

		bool collides(GameObject& other);
		glm::vec2 getMTV(GameObject& other);

		bool hasCollision();

		template<typename T>
		std::shared_ptr<T> getCollsionWithComp() {
			for (const auto& gameObj : this->gameObject.getScene()) {
				if (&this->gameObject == gameObj.get())
					continue;

				const auto comp = gameObj->getComponent<T>();

				if (comp && this->collides(*gameObj))
					return comp;
			}

			return std::shared_ptr<T>();
		}

		void update(float dt) override;
		void lateUpdate(float dt) override;
		void draw(sf::RenderWindow& window) override;
	};
}