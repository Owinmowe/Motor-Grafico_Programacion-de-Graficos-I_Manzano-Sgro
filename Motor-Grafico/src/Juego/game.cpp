#include "game.h"
#include <iostream>

game::game()
{
	ground = nullptr;
	cubeObject = nullptr;

	isCameraFirstPerson = true;
	firstPersonCamera = nullptr;
	thirdPersonCamera = nullptr;

	light1 = nullptr;
	light2 = nullptr;
	light3 = nullptr;
}

game::~game()
{

}

void game::draw()
{
	ground->draw();
	cubeObject->draw();
}

void game::update()
{

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

	}

	glm::vec3 position = light1->getPos();
	if(isKeyPressed(ENGINE_KEY_J))
	{
		position.x -= engine::time::getDeltaTime() * 20;
		light1->setPos(position);
	}
	else if (isKeyPressed(ENGINE_KEY_L))
	{
		position.x += engine::time::getDeltaTime() * 20;
		light1->setPos(position);
	}

	if (isKeyPressed(ENGINE_KEY_I))
	{
		position.z += engine::time::getDeltaTime() * 20;
		light1->setPos(position);
	}
	else if (isKeyPressed(ENGINE_KEY_K))
	{
		position.z -= engine::time::getDeltaTime() * 20;
		light1->setPos(position);
	}
	if (isKeyPressed(ENGINE_KEY_U))
	{
		position.y += engine::time::getDeltaTime() * 20;
		light1->setPos(position);
	}
	else if (isKeyPressed(ENGINE_KEY_O))
	{
		position.y -= engine::time::getDeltaTime() * 20;
		light1->setPos(position);
	}
}

void game::init()
{
	lockCursor();
	firstPersonCamera = new engine::firstPersonCamera(currentRenderer, 45.f, .1f, 1000.f);
	firstPersonCamera->setCameraPosition(glm::vec3(0, 20, 0));
	thirdPersonCamera = new engine::thirdPersonCamera(currentRenderer, 45.f, .1f, 1000.f);
	thirdPersonCamera->setCameraPosition(glm::vec3(0, 20, 0));
	isCameraFirstPerson = true;

	ground = new engine::cube(currentRenderer);
	ground->setPos(-250, 0, -250);
	ground->setScale(1000, 1, 1000);
	ground->setTexture("../res/assets/textures/Ground.jpg", false);

	cubeObject = new engine::cube(currentRenderer);
	cubeObject->setPos(0, 15.f, 0);
	cubeObject->setScale(20, 20, 20);
	cubeObject->setTexture("../res/assets/textures/container.jpg", false);

	changeClearColor(glm::vec4(0, 0, 0, 1));

	light1 = new engine::light(currentRenderer);
	light1->setColor(1.f, 1.f, 1.f, 1.f);
	light1->setLightDirection(glm::vec3(0, 0, 0));
}

void game::deInit()
{
	ground->deInit();
	delete ground;
	cubeObject->deInit();
	delete cubeObject;

	delete firstPersonCamera;
	delete thirdPersonCamera;
}