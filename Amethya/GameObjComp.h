#pragma once

#include "pch.h"
#include "GameObject.h"

namespace GameObjects {
	class GameObject;

	class GameObjComp {
	protected:
		GameObject& gameObject;
		const int priority;

		bool enabled;

	public:
		GameObjComp(GameObject& gameObject, int priority);

		int getPriority() const;

		bool isEnabled();
		void setEnabled(bool enabled);

		virtual void update(float dt) = 0;
		virtual void lateUpdate(float dt) = 0;
		virtual void draw(sf::RenderWindow& window) = 0;

		GameObject& getGameObject();
	};
}