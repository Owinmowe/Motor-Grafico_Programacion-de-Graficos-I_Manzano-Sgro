#include "game.h"
#include <iostream>

game::game()
{
	ground = nullptr;
	for (int i = 0; i < CUBES_AMOUNT; i++)
	{
		cubes[i] = nullptr;
	}

	isCameraFirstPerson = true;
	firstPersonCamera = nullptr;
	thirdPersonCamera = nullptr;

	light1 = nullptr;
}

game::~game()
{

}

void game::draw()
{
	ground->draw();

	for (int i = 0; i < CUBES_AMOUNT; i++)
	{
		cubes[i]->draw();
	}

	light1->draw();
}

void game::update()
{

	if(isKeyDown(ENGINE_KEY_V))
	{
		for (int i = 0; i < CUBES_AMOUNT; i++)
		{
			cubes[i]->toggleTextureUse();
		}
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
		thirdPersonCamera->updateCamera(cubes[0]->getPos(), mousePositionDelta, 250, cubes[0]->getRot().y);
	}

	glm::vec3 cameraPos = firstPersonCamera->getPos();

	if (isKeyPressed(ENGINE_KEY_A))
	{
		glm::vec3 movement = { engine::time::getDeltaTime() * -lightSpeed, 0, 0 };
		light1->setPos(light1->getPos() + movement);
	}
	else if (isKeyPressed(ENGINE_KEY_D))
	{
		glm::vec3 movement = { engine::time::getDeltaTime() * lightSpeed, 0, 0 };

		light1->setPos(light1->getPos() + movement);
	}
	if (isKeyPressed(ENGINE_KEY_W))
	{
		glm::vec3 movement = { 0, 0, engine::time::getDeltaTime() * -lightSpeed };

		light1->setPos(light1->getPos() + movement);
	}
	else if (isKeyPressed(ENGINE_KEY_S))
	{
		glm::vec3 movement = { 0, 0, engine::time::getDeltaTime() * lightSpeed };

		light1->setPos(light1->getPos() + movement);
	}
	if (isKeyPressed(ENGINE_KEY_Q))
	{
		glm::vec3 movement = { 0, engine::time::getDeltaTime() * -lightSpeed, 0 };

		light1->setPos(light1->getPos() + movement);
	}
	else if (isKeyPressed(ENGINE_KEY_E))
	{
		glm::vec3 movement = { 0, engine::time::getDeltaTime() * lightSpeed, 0 };

		light1->setPos(light1->getPos() + movement);
	}
}

void game::init()
{
	lockCursor();
	firstPersonCamera = new engine::firstPersonCamera(currentRenderer, 45.f, .1f, 1000.f);
	thirdPersonCamera = new engine::thirdPersonCamera(currentRenderer, 45.f, .1f, 1000.f);
	isCameraFirstPerson = true;

	ground = new engine::cube(currentRenderer);
	ground->setPos(0, 0, 0);
	ground->setScale(100, 1, 100);
	ground->setTexture("../res/assets/textures/Ground.jpg", false);

	for (int i = 0; i < CUBES_AMOUNT; i++)
	{
		cubes[i] = new engine::cube(currentRenderer);

		cubes[i]->setPos(-5 * i, 1.5f, -5);
		cubes[i]->setScale(1, 1, 1);
		cubes[i]->setTexture("../res/assets/textures/container.jpg", false);
	}

	light1 = new engine::light(currentRenderer);

	light1->setColor(1.f, 1.f, 1.f, 1.f);
	light1->setPos(0, 5, 0);
	light1->setScale(1, 1, 1);

	changeClearColor(glm::vec4(0, 0, 0, 1));
}

void game::deInit()
{
	ground->deInit();
	delete ground;

	for (int i = 0; i < CUBES_AMOUNT; i++)
	{
		cubes[i]->deInit();
		delete cubes[i];
	}

	delete firstPersonCamera;
	delete thirdPersonCamera;

	light1->deInit();
	delete light1;
}