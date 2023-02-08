#include "ItemComp.h"
#include "CollisionComp.h"

namespace GameObjects::Components {
	ItemComp::ItemComp(GameObject& gameObject, std::function<bool(GameObject&)> onCollect) : GameObjComp(gameObject, 2), onCollect(onCollect) {}

	void ItemComp::update(float dt) {
		const auto collider = this->gameObject.getComponent<CollisionComp>();

		if (!collider)
			return;

		for (const auto& gameObject : this->gameObject.getScene()) {
			if (&this->gameObject == gameObject.get())
				continue;

			else if (collider->collides(*gameObject) && this->onCollect(*gameObject))
				this->gameObject.setRemovable(true);
		}
	}

	void ItemComp::lateUpdate(float dt) {}
	void ItemComp::draw(sf::RenderWindow& window) {}

	OscillatorComp::OscillatorComp(GameObject& gameObject, glm::vec2 amplitude, float period) : GameObjComp(gameObject, 1), amplitude(amplitude), period(period), theta(0.0f), 
		defaultPos(gameObject.getPos() + (gameObject.getComponent<CollisionComp>() ? gameObject.getComponent<CollisionComp>()->getHitboxSize() / 2.0f : glm::vec2())) {}

	void OscillatorComp::update(float dt) {
		const auto collider = this->gameObject.getComponent<CollisionComp>();

		this->gameObject.getPos() = this->defaultPos + glm::sin(this->theta) * this->amplitude - (collider ? collider->getHitboxSize() / 2.0f : glm::vec2());

		this->theta += glm::two_pi<float>() * dt / this->period;
		this->theta = std::fmodf(this->theta, glm::two_pi<float>());
	}

	void OscillatorComp::lateUpdate(float dt) {}
	void OscillatorComp::draw(sf::RenderWindow& window) {}
}