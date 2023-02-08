#include "GameObject.h"

namespace GameObjects {
	GameObject::GameObject(Scenes::Scene& scene, glm::vec2 pos) : scene(scene), pos(pos), zDepth(1), removable(false) {}

	void GameObject::addComponent(GameObjComp* component) {
		this->components.insert(std::upper_bound(this->components.begin(), this->components.end(), component, [](const GameObjComp* comp1, const std::shared_ptr<GameObjComp> comp2) {
				return comp1->getPriority() > comp2->getPriority();
			}), std::shared_ptr<GameObjComp>(component));
	}

	void GameObject::update(float dt) {
		for (auto& gameObjComp : this->components) {
			if(gameObjComp->isEnabled())
				gameObjComp->update(dt);
		}
	}

	void GameObject::lateUpdate(float dt) {
		for (auto& gameObjComp : this->components) {
			if (gameObjComp->isEnabled())
				gameObjComp->lateUpdate(dt);
		}
	}

	void GameObject::draw(sf::RenderWindow& window) {
		for (auto& gameObjComp : this->components) {
			if (gameObjComp->isEnabled())
				gameObjComp->draw(window);
		}
	}

	int GameObject::getZDepth() const {
		return this->zDepth;
	}

	void GameObject::setZDepth(int zDepth) {
		this->zDepth = zDepth;
	}

	bool GameObject::getRemovable() {
		return this->removable;
	}

	void GameObject::setRemovable(bool removable) {
		this->removable = removable;
	}

	Scenes::Scene& GameObject::getScene() {
		return this->scene;
	}

	glm::vec2& GameObject::getPos() {
		return this->pos;
	}
}