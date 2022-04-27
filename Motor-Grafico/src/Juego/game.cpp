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
			light1->SetFrontVector(light1->getPos() + movement);
		}
		if (isKeyPressed(ENGINE_KEY_W))
		{
			glm::vec3 movement = { 0, 0, engine::time::getDeltaTime() * -lightSpeed };

			light1->setPos(light1->getPos() + movement);
			light1->SetFrontVector(light1->getPos() + movement);
		}
		else if (isKeyPressed(ENGINE_KEY_S))
		{
			glm::vec3 movement = { 0, 0, engine::time::getDeltaTime() * lightSpeed };

			light1->setPos(light1->getPos() + movement);
			light1->SetFrontVector(light1->getPos() + movement);
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

	ground = new engine::cube(currentRenderer);
	ground->setPos(0, 0, 0);
	ground->setScale(100, 1, 100);
	//ground->setTexture("../res/assets/textures/Ground.jpg", false);

	for (int i = 0; i < CUBES_AMOUNT; i++)
	{
		cubes[i] = new engine::cube(currentRenderer);

		cubes[i]->setPos(-25 + i * 2, 1.5f, 50);
		cubes[i]->setScale(1, 1, 1);
		//cubes[i]->setTexture("../res/assets/textures/container2.png", false);
	}


	emeraldCube = new engine::cube(currentRenderer);
	engine::material emeraldMaterial;
	//emeraldMaterial.ambient = glm::vec3(0.0215f, 0.1745f, 0.0215f);
	//emeraldMaterial.diffuseStrenght = glm::vec3(0.07568, 0.61424, 0.07568);
	//emeraldMaterial.specularStrenght = glm::vec3(0.633, 0.727811, 0.633);
	//emeraldMaterial.shininess = 0.6;
	emeraldCube->setMaterial(emeraldMaterial);
	emeraldCube->setPos(8, 4.0f, 0);
	emeraldCube->setScale(1, 1, 1);

	pearlCube = new engine::cube(currentRenderer);
	engine::material pearlMaterial;
	//pearlMaterial.ambient = glm::vec3(0.25, 0.20725, 0.20725);
	//pearlMaterial.diffuseStrenght = glm::vec3(1, 0.829, 0.829);
	//pearlMaterial.specularStrenght = glm::vec3(0.296648, 0.296648, 0.296648);
	//pearlMaterial.shininess = 0.088;
	pearlCube->setMaterial(pearlMaterial);
	pearlCube->setPos(6, 4.0f, 0);
	pearlCube->setScale(1, 1, 1);

	bronzeCube = new engine::cube(currentRenderer);
	engine::material bronzeMaterial;
	//bronzeMaterial.ambient = glm::vec3(0.2125, 0.1275, 0.054);
	//bronzeMaterial.diffuseStrenght = glm::vec3(0.714, 0.4284, 0.18144);
	//bronzeMaterial.specularStrenght = glm::vec3(0.393548, 0.271906, 0.166721);
	//bronzeMaterial.shininess = 0.2;
	bronzeCube->setMaterial(bronzeMaterial);
	bronzeCube->setPos(4, 4.0f, 0);
	bronzeCube->setScale(1, 1, 1);

	goldCube = new engine::cube(currentRenderer);
	engine::material goldMaterial;
	//goldMaterial.ambient = glm::vec3(0.24725, 0.1995, 0.0745);
	//goldMaterial.diffuseStrenght = glm::vec3(0.75164, 0.60648, 0.22648);
	//goldMaterial.specularStrenght = glm::vec3(0.628281, 0.555802, 0.366065);
	//goldMaterial.shininess = 0.4;
	goldCube->setMaterial(goldMaterial);
	goldCube->setPos(2, 4.0f, 0);
	goldCube->setScale(1, 1, 1);

	cyanPlasticCube = new engine::cube(currentRenderer);
	engine::material cyanPlasticMaterial;
	//cyanPlasticMaterial.ambient = glm::vec3(0.0, 0.1, 0.06);
	//cyanPlasticMaterial.diffuseStrenght = glm::vec3(0.0, 0.50980392, 0.50980392);
	//cyanPlasticMaterial.specularStrenght = glm::vec3(0.50196078, 0.50196078, 0.50196078);
	//cyanPlasticMaterial.shininess = 0.25;
	cyanPlasticCube->setMaterial(cyanPlasticMaterial);
	cyanPlasticCube->setPos(8, 1.5f, 0);
	cyanPlasticCube->setScale(1, 1, 1);

	redPlasticCube = new engine::cube(currentRenderer);
	engine::material redPlasticMaterial;
	//redPlasticMaterial.ambient = glm::vec3(0.0, 0.0, 0.0);
	//redPlasticMaterial.diffuseStrenght = glm::vec3(0.5, 0.0, 0.0);
	//redPlasticMaterial.specularStrenght = glm::vec3(0.7, 0.6, 0.6);
	//redPlasticMaterial.shininess = 0.25;
	redPlasticCube->setMaterial(redPlasticMaterial);
	redPlasticCube->setPos(6, 1.5f, 0);
	redPlasticCube->setScale(1, 1, 1);

	greenRubberCube = new engine::cube(currentRenderer);
	engine::material greenRubberMaterial;
	//greenRubberMaterial.ambient = glm::vec3(0.0, 0.05, 0.0);
	//greenRubberMaterial.diffuseStrenght = glm::vec3(0.4, 0.5, 0.4);
	//greenRubberMaterial.specularStrenght = glm::vec3(0.04, 0.7,	0.04);
	//greenRubberMaterial.shininess = 0.078125;
	greenRubberCube->setMaterial(greenRubberMaterial);
	greenRubberCube->setPos(4, 1.5f, 0);
	greenRubberCube->setScale(1, 1, 1);

	yellowRubberCube = new engine::cube(currentRenderer);
	engine::material yellowRubberMaterial;
	//yellowRubberMaterial.ambient = glm::vec3(0.05, 0.05, 0.0);
	//yellowRubberMaterial.diffuseStrenght = glm::vec3(0.5, 0.5, 0.4);
	//yellowRubberMaterial.specularStrenght = glm::vec3(0.7, 0.7,	0.04);
	//yellowRubberMaterial.shininess = 0.078125;
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