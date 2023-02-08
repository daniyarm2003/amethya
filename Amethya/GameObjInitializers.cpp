#include "GameObjInitializers.h"
#include "TestComponent.h"
#include "CollisionComp.h"
#include "OrdinaryPhysComp.h"
#include "PlatformRendererComp.h"
#include "ResourceManager.h"
#include "AnimationRendererComp.h"
#include "StateMachineComp.h"
#include "PlayerGroundIdleState.h"
#include "PlayerProperties.h"
#include "CameraComp.h"
#include "BackgroundComp.h"
#include "ItemComp.h"

using namespace GameObjects::Components;

namespace GameObjects {
	GameObject* Initializers::initTestGameObj(Scenes::Scene& scene, glm::vec2 pos) {
		auto gameObj = new GameObject(scene, pos);

		gameObj->addComponent(new Properties::PlayerProperties(*gameObj));
		gameObj->addComponent(new CollisionComp(*gameObj, 1, CollisionType::SOLID, 50.0f, 100.0f));
		gameObj->addComponent(new OrdinaryPhysComp(*gameObj, 1.0f));
		gameObj->addComponent(new AnimationRendererComp(*gameObj, Resources::ResourceManager::getInstance().getAnimation("player-run-right")));
		
		auto stateMachine = new StateMachineComp(*gameObj, 1);

		stateMachine->changeState(new States::Player::PlayerGroundIdleState(*stateMachine, 1));
		gameObj->addComponent(stateMachine);

		gameObj->setZDepth(3);

		scene.addCamera(initCamera(*gameObj));

		return gameObj;
	}

	GameObject* Initializers::initTestHitbox(Scenes::Scene& scene, glm::vec4 rect) {
		auto gameObj = new GameObject(scene, glm::vec2(rect.x, rect.y));

		gameObj->addComponent(new CollisionComp(*gameObj, 1, CollisionType::SOLID, rect.z, rect.w));
		gameObj->addComponent(new PlatformRendererComp(*gameObj, PlatformTexture::AMETHYST_GROUND, PlatformTexture::AMETHYST));

		return gameObj;
	}

	GameObject* Initializers::initCamera(GameObject& trackedObj) {
		auto gameObj = new GameObject(trackedObj.getScene(), trackedObj.getPos());

		gameObj->addComponent(new CameraComp(*gameObj, trackedObj));

		return gameObj;
	}

	GameObject* Initializers::initBackground(Scenes::Scene& scene, size_t bgInd, int zDepth, bool scrollX, bool scrollY) {
		auto gameObj = new GameObject(scene, glm::vec2());

		gameObj->addComponent(new BackgroundComp(*gameObj, bgInd, zDepth, scrollX, scrollY));

		return gameObj;
	}

	GameObject* Initializers::initJumpRefillOrb(Scenes::Scene& scene, glm::vec2 pos) {
		auto gameObj = new GameObject(scene, pos);

		gameObj->addComponent(new CollisionComp(*gameObj, 1, CollisionType::ZONE, 25.0f, 25.0f));

		gameObj->addComponent(new ItemComp(*gameObj, [](GameObject& gameObject) {
			const auto playerProps = gameObject.getComponent<Properties::PlayerProperties>();

			if (!playerProps)
				return false;

			playerProps->resetJumps();
			return true;
		}));

		gameObj->addComponent(new OscillatorComp(*gameObj, glm::vec2(0.0f, 10.0f), 2.0f));

		gameObj->addComponent(new AnimationRendererComp(*gameObj, Resources::ResourceManager::getInstance().getAnimation("jump-orb")));

		return gameObj;
	}
}