#include "Animation.h"
#include "ResourceManager.h"

namespace Resources {
	sf::Sprite& AnimationFrame::getSprite() const {
		return ResourceManager::getInstance().getSprite(this->spritesheet, this->frame);
	}

	void Animation::addFrame(AnimationFrame frame) {
		this->frames.push_back(frame);
	}

	void Animation::animate(float dt) {
		if (this->frames[this->curFrame].frameTime < 0.0f)
			return;

		this->time += dt;

		if (this->time >= this->frames[this->curFrame].frameTime) {
			this->time = std::fmodf(this->time, this->frames[this->curFrame].frameTime);
			this->curFrame = (this->curFrame + 1) % this->frames.size();

			if (this->curFrame == 0 || this->frames[this->curFrame].frameTime < 0.0f)
				this->finished = true;
		}
	}

	sf::Sprite& Animation::getCurrentSprite() const {
		return this->frames[this->curFrame].getSprite();
	}

	glm::vec2 Animation::getOffset() {
		return this->frames[this->curFrame].offset;
	}

	glm::vec2 Animation::getScale() {
		return this->frames[this->curFrame].scale;
	}

	bool Animation::getFinished() const {
		return this->finished;
	}
}