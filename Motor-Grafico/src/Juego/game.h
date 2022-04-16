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
	engine::firstPersonCamera* firstPersonCamera;
	engine::thirdPersonCamera* thirdPersonCamera;
	engine::light* light1;
	engine::light* light2;
	engine::light* light3;
	bool isCameraFirstPerson;
	float cameraSpeed = 100.f;
};
