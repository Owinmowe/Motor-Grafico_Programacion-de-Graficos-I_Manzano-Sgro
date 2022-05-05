#pragma once
#include "Motor/baseGame.h"

#define CUBES_AMOUNT 25

class game : public engine::baseGame
{
public:
	game();
	~game();
	void update() override;
	void draw() override;
	void init() override;
	void deInit() override;

private:

	engine::cube* ground;
	engine::cube* cubes[CUBES_AMOUNT];

	engine::cube* emeraldCube;
	engine::cube* pearlCube;
	engine::cube* bronzeCube;
	engine::cube* goldCube;
	engine::cube* cyanPlasticCube;
	engine::cube* redPlasticCube;
	engine::cube* greenRubberCube;
	engine::cube* yellowRubberCube;


	engine::firstPersonCamera* firstPersonCamera;
	engine::thirdPersonCamera* thirdPersonCamera;
	engine::directionalLight* light1;
	bool isCameraFirstPerson;
	float cameraSpeed = 10.f;
	float lightSpeed = 10.f;
};
