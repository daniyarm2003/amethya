#pragma once

#include "pch.h"

namespace Resources {
	struct AnimationFrame {
		std::string spritesheet;
		size_t frame;

		float frameTime;

		glm::vec2 offset, scale = glm::vec2(1.0f, 1.0f);

		sf::Sprite& getSprite() const;
	};

	class Animation {
	private:
		std::vector<AnimationFrame> frames;
		size_t curFrame = 0;

		float time = 0.0f;
		bool finished = false;

	public:
		void addFrame(AnimationFrame frame);
		void animate(float dt);

		sf::Sprite& getCurrentSprite() const;

		glm::vec2 getOffset(), getScale();

		bool getFinished() const;
	};
}