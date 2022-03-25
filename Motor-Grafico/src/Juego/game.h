#pragma once
#include "Motor/baseGame.h"

const int colorsArraySize = 8;

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
	engine::sprite* archer;
	engine::sprite* ground;
	engine::cube* cubeObject;
	engine::firstPersonCamera* firstPersonCamera;
	engine::thirdPersonCamera* thirdPersonCamera;
	bool isCameraFirstPerson;
	float cameraSpeed = 100.f;

	int archerRunLeftAnimationID;
	int archerRunRightAnimationID;
	int archerRunUpAnimationID;
	int archerRunUpLeftAnimationID;
	int archerRunUpRightAnimationID;
	int archerRunDownAnimationID;
	int archerRunDownLeftAnimationID;
	int archerRunDownRightAnimationID;
	float archerRunSpeed = 50;
};
