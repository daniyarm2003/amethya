#pragma once

#include "GameObjComp.h"
#include "Animation.h"

namespace GameObjects::Components {
	class AnimationRendererComp : public GameObjComp {
	private:
		Resources::Animation animation;

	public:
		AnimationRendererComp(GameObject& gameObject, Resources::Animation animation);

		void setAnimation(Resources::Animation animation);

		void update(float dt) override;
		void lateUpdate(float dt) override;
		void draw(sf::RenderWindow& window) override;
	};
}