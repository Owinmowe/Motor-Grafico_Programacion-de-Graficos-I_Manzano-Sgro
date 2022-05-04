#include "game.h"
#include <iostream>

game::game()
{
	ground = nullptr;
	for (int i = 0; i < CUBES_AMOUNT; i++)
	{
		cubes[i] = nullptr;
	}

	emeraldCube = nullptr;
	pearlCube = nullptr;
	bronzeCube = nullptr;
	goldCube = nullptr;
	cyanPlasticCube = nullptr;
	redPlasticCube = nullptr;
	greenRubberCube = nullptr;
	yellowRubberCube = nullptr;

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

	emeraldCube->draw();
	pearlCube->draw();
	bronzeCube->draw();
	goldCube->draw();
	cyanPlasticCube->draw();
	redPlasticCube->draw();
	greenRubberCube->draw();
	yellowRubberCube->draw();

	light1->draw();
}

void game::update()
{

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

		if (isKeyPressed(ENGINE_KEY_A))
		{
			glm::vec3 movement = { engine::time::getDeltaTime() * -lightSpeed, 0, 0 };
			light1->setPos(light1->getPos() + movement);
			light1->SetFrontVector(light1->getPos() + movement);
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
	else
	{
		thirdPersonCamera->updateCamera(cubes[0]->getPos(), mousePositionDelta, 5, cubes[0]->getRot().y);

		if (isKeyPressed(ENGINE_KEY_A))
		{
			glm::vec3 movement = { engine::time::getDeltaTime() * -lightSpeed, 0, 0 };
			cubes[0]->setPos(cubes[0]->getPos() + movement);
		}
		else if (isKeyPressed(ENGINE_KEY_D))
		{
			glm::vec3 movement = { engine::time::getDeltaTime() * lightSpeed, 0, 0 };

			cubes[0]->setPos(cubes[0]->getPos() + movement);
		}
		if (isKeyPressed(ENGINE_KEY_W))
		{
			glm::vec3 movement = { 0, 0, engine::time::getDeltaTime() * -lightSpeed };

			cubes[0]->setPos(cubes[0]->getPos() + movement);
		}
		else if (isKeyPressed(ENGINE_KEY_S))
		{
			glm::vec3 movement = { 0, 0, engine::time::getDeltaTime() * lightSpeed };

			cubes[0]->setPos(cubes[0]->getPos() + movement);
		}
		if (isKeyPressed(ENGINE_KEY_Q))
		{
			glm::vec3 movement = { 0, engine::time::getDeltaTime() * -lightSpeed, 0 };

			cubes[0]->setPos(cubes[0]->getPos() + movement);
		}
		else if (isKeyPressed(ENGINE_KEY_E))
		{
			glm::vec3 movement = { 0, engine::time::getDeltaTime() * lightSpeed, 0 };

			cubes[0]->setPos(cubes[0]->getPos() + movement);
		}

	}

	glm::vec3 cameraPos = firstPersonCamera->getPos();
}

void game::init()
{
	lockCursor();
	firstPersonCamera = new engine::firstPersonCamera(currentRenderer, 45.f, .1f, 1000.f);
	thirdPersonCamera = new engine::thirdPersonCamera(currentRenderer, 45.f, .1f, 1000.f);
	isCameraFirstPerson = true;

	engine::material* groundMaterial = new engine::material();
	groundMaterial->setDiffuseMap("../res/assets/textures/Ground.jpg", false);
	ground = new engine::cube(currentRenderer);
	ground->setPos(0, 0, 0);
	ground->setScale(100, 1, 100);
	ground->setMaterial(groundMaterial);

	engine::material* cubesMaterial = new engine::material();
	cubesMaterial->setDiffuseMap("../res/assets/textures/container2.png", false);
	cubesMaterial->setSpecularMap("../res/assets/textures/container2_specular.png", false);
	for (int i = 0; i < CUBES_AMOUNT; i++)
	{
		cubes[i] = new engine::cube(currentRenderer);

		cubes[i]->setPos(-25 + i * 2, 1.5f, 50);
		cubes[i]->setScale(1, 1, 1);
		cubes[i]->setMaterial(cubesMaterial);
	}


	emeraldCube = new engine::cube(currentRenderer);
	engine::material* emeraldMaterial = new engine::material();
	emeraldMaterial->setAmbientStrenght(glm::vec3(0.0215f, 0.1745f, 0.0215f));
	emeraldMaterial->setDiffuseStrenght(glm::vec3(0.07568, 0.61424, 0.07568));
	emeraldMaterial->setSpecularStrenght(glm::vec3(0.633, 0.727811, 0.633));
	emeraldMaterial->setShininess(0.6);
	emeraldCube->setMaterial(emeraldMaterial);
	emeraldCube->setPos(8, 4.0f, 0);
	emeraldCube->setScale(1, 1, 1);

	pearlCube = new engine::cube(currentRenderer);
	engine::material* pearlMaterial = new engine::material();
	pearlMaterial->setAmbientStrenght(glm::vec3(0.25, 0.20725, 0.20725));
	pearlMaterial->setDiffuseStrenght(glm::vec3(1, 0.829, 0.829));
	pearlMaterial->setSpecularStrenght(glm::vec3(0.296648, 0.296648, 0.296648));
	pearlMaterial->setShininess(0.088);
	pearlCube->setMaterial(pearlMaterial);
	pearlCube->setPos(6, 4.0f, 0);
	pearlCube->setScale(1, 1, 1);

	bronzeCube = new engine::cube(currentRenderer);
	engine::material* bronzeMaterial = new engine::material();
	bronzeMaterial->setAmbientStrenght(glm::vec3(0.2125, 0.1275, 0.054));
	bronzeMaterial->setDiffuseStrenght(glm::vec3(0.714, 0.4284, 0.18144));
	bronzeMaterial->setSpecularStrenght(glm::vec3(0.393548, 0.271906, 0.166721));
	bronzeMaterial->setShininess(0.2);
	bronzeCube->setMaterial(bronzeMaterial);
	bronzeCube->setPos(4, 4.0f, 0);
	bronzeCube->setScale(1, 1, 1);

	goldCube = new engine::cube(currentRenderer);
	engine::material* goldMaterial = new engine::material();
	goldMaterial->setAmbientStrenght(glm::vec3(0.24725, 0.1995, 0.0745));
	goldMaterial->setDiffuseStrenght(glm::vec3(0.75164, 0.60648, 0.22648));
	goldMaterial->setSpecularStrenght(glm::vec3(0.628281, 0.555802, 0.366065));
	goldMaterial->setShininess(0.4);
	goldCube->setMaterial(goldMaterial);
	goldCube->setPos(2, 4.0f, 0);
	goldCube->setScale(1, 1, 1);

	cyanPlasticCube = new engine::cube(currentRenderer);
	engine::material* cyanPlasticMaterial = new engine::material();
	cyanPlasticMaterial->setAmbientStrenght(glm::vec3(0.0, 0.1, 0.06));
	cyanPlasticMaterial->setDiffuseStrenght(glm::vec3(0.0, 0.50980392, 0.50980392));
	cyanPlasticMaterial->setSpecularStrenght(glm::vec3(0.50196078, 0.50196078, 0.50196078));
	cyanPlasticMaterial->setShininess(0.25);
	cyanPlasticCube->setMaterial(cyanPlasticMaterial);
	cyanPlasticCube->setPos(8, 1.5f, 0);
	cyanPlasticCube->setScale(1, 1, 1);

	redPlasticCube = new engine::cube(currentRenderer);
	engine::material* redPlasticMaterial = new engine::material();
	redPlasticMaterial->setAmbientStrenght(glm::vec3(0.0, 0.0, 0.0));
	redPlasticMaterial->setDiffuseStrenght(glm::vec3(0.5, 0.0, 0.0));
	redPlasticMaterial->setSpecularStrenght(glm::vec3(0.7, 0.6, 0.6));
	redPlasticMaterial->setShininess(0.25);
	redPlasticCube->setMaterial(redPlasticMaterial);
	redPlasticCube->setPos(6, 1.5f, 0);
	redPlasticCube->setScale(1, 1, 1);

	greenRubberCube = new engine::cube(currentRenderer);
	engine::material* greenRubberMaterial = new engine::material();
	greenRubberMaterial->setAmbientStrenght(glm::vec3(0.0, 0.05, 0.0));
	greenRubberMaterial->setDiffuseStrenght(glm::vec3(0.4, 0.5, 0.4));
	greenRubberMaterial->setSpecularStrenght(glm::vec3(0.04, 0.7,	0.04));
	greenRubberMaterial->setShininess(0.078125);
	greenRubberCube->setMaterial(greenRubberMaterial);
	greenRubberCube->setPos(4, 1.5f, 0);
	greenRubberCube->setScale(1, 1, 1);

	yellowRubberCube = new engine::cube(currentRenderer);
	engine::material* yellowRubberMaterial = new engine::material();
	yellowRubberMaterial->setAmbientStrenght(glm::vec3(0.05, 0.05, 0.0));
	yellowRubberMaterial->setDiffuseStrenght(glm::vec3(0.5, 0.5, 0.4));
	yellowRubberMaterial->setSpecularStrenght(glm::vec3(0.7, 0.7,	0.04));
	yellowRubberMaterial->setShininess(0.078125);
	yellowRubberCube->setMaterial(yellowRubberMaterial);
	yellowRubberCube->setPos(2, 1.5f, 0);
	yellowRubberCube->setScale(1, 1, 1);


	light1 = new engine::light(currentRenderer);

	light1->setColor(1.f, 1.f, 1.f);
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