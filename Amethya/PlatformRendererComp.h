#pragma once

#include "GameObjComp.h"

namespace GameObjects::Components {
	enum class PlatformTexture {
		AMETHYST_GROUND, AMETHYST
	};

	class PlatformRendererComp : public GameObjComp {
	private:
		PlatformTexture top, bottom;

	public:
		static constexpr float TILE_SIZE = 50.0f;

		PlatformRendererComp(GameObject& gameObj, PlatformTexture top, PlatformTexture bottom);

		void update(float dt) override;
		void lateUpdate(float dt) override;
		void draw(sf::RenderWindow& window) override;
	};
}