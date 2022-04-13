#include "game.h"
#include <iostream>

game::game()
{
	archer = nullptr;
	ground = nullptr;
	cubeObject = nullptr;

	isCameraFirstPerson = true;
	firstPersonCamera = nullptr;
	thirdPersonCamera = nullptr;

	archerRunLeftAnimationID = 0;
	archerRunRightAnimationID = 0;
	archerRunUpAnimationID = 0;
	archerRunUpLeftAnimationID = 0;
	archerRunUpRightAnimationID = 0;
	archerRunDownAnimationID = 0;
	archerRunDownLeftAnimationID = 0;
	archerRunDownRightAnimationID = 0;

	light1 = nullptr;
}

game::~game()
{

}

void game::draw()
{
	archer->draw();
	ground->draw();
	cubeObject->draw();
}

void game::update()
{

	if(isKeyPressed(ENGINE_KEY_W) && isKeyPressed(ENGINE_KEY_A))
	{
		glm::vec3 pos = archer->getPos();
		archer->setPos(pos.x - engine::time::getDeltaTime() * archerRunSpeed / 2, pos.y, pos.z - engine::time::getDeltaTime() * archerRunSpeed / 2);
		archer->playAnimation(archerRunUpLeftAnimationID);
	}
	else if (isKeyPressed(ENGINE_KEY_W) && isKeyPressed(ENGINE_KEY_D))
	{
		glm::vec3 pos = archer->getPos();
		archer->setPos(pos.x + engine::time::getDeltaTime() * archerRunSpeed / 2, pos.y, pos.z - engine::time::getDeltaTime() * archerRunSpeed / 2);
		archer->playAnimation(archerRunUpRightAnimationID);
	}
	else if (isKeyPressed(ENGINE_KEY_S) && isKeyPressed(ENGINE_KEY_A))
	{
		glm::vec3 pos = archer->getPos();
		archer->setPos(pos.x - engine::time::getDeltaTime() * archerRunSpeed / 2, pos.y, pos.z + engine::time::getDeltaTime() * archerRunSpeed / 2);
		archer->playAnimation(archerRunDownLeftAnimationID);
	}
	else if (isKeyPressed(ENGINE_KEY_S) && isKeyPressed(ENGINE_KEY_D))
	{
		glm::vec3 pos = archer->getPos();
		archer->setPos(pos.x + engine::time::getDeltaTime() * archerRunSpeed / 2, pos.y, pos.z + engine::time::getDeltaTime() * archerRunSpeed / 2);
		archer->playAnimation(archerRunDownRightAnimationID);
	}
	else if(isKeyPressed(ENGINE_KEY_A))
	{
		glm::vec3 pos = archer->getPos();
		archer->setPos(pos.x - engine::time::getDeltaTime() * archerRunSpeed, pos.y, pos.z);
		archer->playAnimation(archerRunLeftAnimationID);
	}
	else if(isKeyPressed(ENGINE_KEY_D))
	{
		glm::vec3 pos = archer->getPos();
		archer->setPos(pos.x + engine::time::getDeltaTime() * archerRunSpeed, pos.y, pos.z);
		archer->playAnimation(archerRunRightAnimationID);
	}
	else if (isKeyPressed(ENGINE_KEY_W))
	{
		glm::vec3 pos = archer->getPos();
		archer->setPos(pos.x, pos.y, pos.z - engine::time::getDeltaTime() * archerRunSpeed);
		archer->playAnimation(archerRunUpAnimationID);
	}
	else if (isKeyPressed(ENGINE_KEY_S))
	{
		glm::vec3 pos = archer->getPos();
		archer->setPos(pos.x, pos.y, pos.z + engine::time::getDeltaTime() * archerRunSpeed);
		archer->playAnimation(archerRunDownAnimationID);
	}
	else
	{
		archer->stopAllAnimations();
	}

	if(isKeyDown(ENGINE_KEY_V))
	{
		cubeObject->toggleTextureUse();
	}

	if(isKeyDown(ENGINE_KEY_C))
	{
		isCameraFirstPerson = !isCameraFirstPerson;
	}

	glm::vec2 mousePositionDelta = getDeltaMousePosition();

	if(isCameraFirstPerson)
	{
		if (isKeyPressed(ENGINE_KEY_LEFT))
		{
			glm::vec3 movement = { engine::time::getDeltaTime() * -cameraSpeed, 0, 0 };
			firstPersonCamera->moveCameraByLocalVector(movement);
		}
		else if (isKeyPressed(ENGINE_KEY_RIGHT))
		{
			glm::vec3 movement = { engine::time::getDeltaTime() * cameraSpeed, 0, 0 };
			firstPersonCamera->moveCameraByLocalVector(movement);
		}
		if (isKeyPressed(ENGINE_KEY_UP))
		{
			glm::vec3 movement = { 0, 0 , engine::time::getDeltaTime() * -cameraSpeed };
			firstPersonCamera->moveCameraByLocalVector(movement);
		}
		else if (isKeyPressed(ENGINE_KEY_DOWN))
		{
			glm::vec3 movement = { 0, 0, engine::time::getDeltaTime() * cameraSpeed };
			firstPersonCamera->moveCameraByLocalVector(movement);
		}
		firstPersonCamera->offsetCameraAim(mousePositionDelta.x, mousePositionDelta.y, true);
	}
	else
	{
		thirdPersonCamera->updateCamera(archer->getPos(), mousePositionDelta, 200.f, archer->getRot().y);
	}

	glm::vec3 direction = light1->getLightDirection();
	if(isKeyPressed(ENGINE_KEY_K))
	{
		direction.y += engine::time::getDeltaTime();
		light1->setLightDirection(direction);
	}
	else if (isKeyPressed(ENGINE_KEY_L))
	{
		direction.y -= engine::time::getDeltaTime();
		light1->setLightDirection(direction);
	}
}

void game::init()
{
	lockCursor();
	firstPersonCamera = new engine::firstPersonCamera(currentRenderer, 45.f, .1f, 500.f);
	firstPersonCamera->setCameraPosition(glm::vec3(0, 20, 0));
	thirdPersonCamera = new engine::thirdPersonCamera(currentRenderer, 45.f, .1f, 500.f);
	thirdPersonCamera->setCameraPosition(glm::vec3(0, 20, 0));
	isCameraFirstPerson = true;

	archer = new engine::sprite(currentRenderer, "../res/assets/textures/Atlas Sprites/archerFullAtlas.png", false);

	ground = new engine::sprite(currentRenderer, "../res/assets/textures/Ground.jpg", false);
	ground->setPos(0, 0, 0);
	ground->setScale(1000, 1000, 100);
	ground->setRot(90, 0, 0);

	cubeObject = new engine::cube(currentRenderer);
	cubeObject->setPos(0, 10, 0);
	cubeObject->setScale(20, 20, 20);
	cubeObject->setTexture("../res/assets/textures/container.jpg", false);

	engine::atlasCutConfig archerRunAtlasConfig;

	archerRunAtlasConfig.CutByCount(10, 7, 6, 5, 8);
	archerRunLeftAnimationID = archer->createAnimation(archerRunAtlasConfig);

	archerRunAtlasConfig.CutByCount(10, 7, 0, 0, 8);
	archerRunRightAnimationID = archer->createAnimation(archerRunAtlasConfig);

	archerRunAtlasConfig.CutByCount(10, 7, 8, 0, 8);
	archerRunUpAnimationID = archer->createAnimation(archerRunAtlasConfig);

	archerRunAtlasConfig.CutByCount(10, 7, 2, 3, 8);
	archerRunDownAnimationID = archer->createAnimation(archerRunAtlasConfig);

	archerRunAtlasConfig.CutByCount(10, 7, 4, 2, 8);
	archerRunUpLeftAnimationID = archer->createAnimation(archerRunAtlasConfig);
	
	archerRunAtlasConfig.CutByCount(10, 7, 8, 4, 8);
	archerRunDownLeftAnimationID = archer->createAnimation(archerRunAtlasConfig);
	
	archerRunAtlasConfig.CutByCount(10, 7, 6, 1, 8);
	archerRunUpRightAnimationID = archer->createAnimation(archerRunAtlasConfig);
	
	archerRunAtlasConfig.CutByCount(10, 7, 0, 4, 8);
	archerRunDownRightAnimationID = archer->createAnimation(archerRunAtlasConfig);

	archer->setAnimationFullTime(archerRunRightAnimationID, .5f);
	archer->setAnimationFullTime(archerRunLeftAnimationID, .5f);
	archer->setAnimationFullTime(archerRunUpAnimationID, .5f);
	archer->setAnimationFullTime(archerRunUpLeftAnimationID, .5f);
	archer->setAnimationFullTime(archerRunDownAnimationID, .5f);
	archer->setAnimationFullTime(archerRunUpRightAnimationID, .5f);
	archer->setAnimationFullTime(archerRunDownLeftAnimationID, .5f);
	archer->setAnimationFullTime(archerRunDownRightAnimationID, .5f);

	archer->setScale(32, 32, 1);
	archer->setPos(0, 10, 0);

	changeClearColor(glm::vec4(0, 0, 0, 1));

	light1 = new engine::light(currentRenderer);
	light1->setColor(1.f, 1.f, 1.f, 1.f);
	light1->setPos(0.0f, 0.0f, 0.0f);
	light1->setLightDirection(glm::vec3(0, 0, 0));
}

void game::deInit()
{
	//imageCampus->deinit();
	//delete imageCampus;
	archer->deinit();
	delete archer;
	ground->deinit();
	delete ground;
	cubeObject->deInit();
	delete cubeObject;

	delete firstPersonCamera;
	delete thirdPersonCamera;
}