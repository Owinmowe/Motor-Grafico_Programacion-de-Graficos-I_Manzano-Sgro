#include "entity.h"
#include "renderer.h"

namespace engine
{
	entity::entity()
	{
		_renderer = NULL;
		model = glm::mat4(1.0f);
		translate = glm::mat4(1.0f);
		rotateX = glm::mat4(1.0f);
		rotateY = glm::mat4(1.0f);
		rotateZ = glm::mat4(1.0f);			
		scale = glm::mat4(1.0f);

		v3pos = glm::vec3(0.0f);
		v3rot = glm::vec3(0.0f);
		v3scale = glm::vec3(1.0f);


		setColor(glm::vec4(1.0f));

		yaw = -90.0f;
		pitch = 0.0f;
		roll = 0.0f;

		updateModelMatrix();
	}

	entity::~entity()
	{

	}

	void entity::updateModelMatrix()
	{
		model = translate * rotateX * rotateY * rotateZ * scale;
	}
	void entity::alignDirectionVectorsWithFront()
	{
		upVector = glm::vec3(0.0f, 1.0f, 0.0f);
		rightVector = glm::normalize(glm::cross(frontVector, upVector));
		upVector = glm::normalize(glm::cross(rightVector, frontVector));
	}
	void entity::alignDirectionVectorsWithRotation()
	{
		glm::vec3 front;
		front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
		front.y = sin(glm::radians(pitch));
		front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
		frontVector = glm::normalize(front);

		alignDirectionVectorsWithFront();
	}
	void entity::setPos(glm::vec3 pos)
	{
		v3pos = pos;
		translate = glm::translate(glm::mat4(1.0f), v3pos);
		updateModelMatrix();
	}
	void entity::setPos(float x, float y, float z)
	{
		setPos(glm::vec3(x, y, z));
	}
	void entity::setRot(glm::vec3 rot)
	{

		pitch = rot.x;
		yaw = rot.y;
		roll = rot.z;

		setRotX(glm::radians(rot.x));
		setRotY(glm::radians(rot.y));
		setRotZ(glm::radians(rot.z));
		updateModelMatrix();
	}
	void entity::setRot(float x, float y, float z)
	{

		pitch = x;
		yaw = y;
		roll = z;

		float randiansX = glm::radians(x);
		float randiansY = glm::radians(y);
		float randiansZ = glm::radians(z);
		setRotX(randiansX);
		setRotY(randiansY);
		setRotZ(randiansZ);
		updateModelMatrix();
	}
	void entity::setRotX(float x)
	{
		v3rot.x = x;
		glm::vec3 axis;

		axis[1] = axis[2] = 0.0f;
		axis[0] = 1.0f;

		rotateX = glm::rotate(glm::mat4(1.0f), x, axis);
	}
	void entity::setRotY(float y)
	{
		v3rot.y = y;
		glm::vec3 axis;

		axis[0] = axis[2] = 0.0f;
		axis[1] = 1.0f;

		rotateY = glm::rotate(glm::mat4(1.0f), y, axis);
	}
	void entity::setRotZ(float z)
	{
		v3rot.z = z;
		glm::vec3 axis;

		axis[0] = axis[1] = 0.0f;
		axis[2] = 1.0f;

		rotateZ = glm::rotate(glm::mat4(1.0f), z, axis);
	}
	void entity::setScale(glm::vec3 scale)
	{
		v3scale = scale;

		this->scale = glm::scale(glm::mat4(1.0f), v3scale);
		updateModelMatrix();
	}
	void entity::setScale(float x, float y, float z)
	{
		setScale(glm::vec3(x, y, z));
	}
	void entity::setColor(glm::vec4 color)
	{
		this->color = color;
	}
	void entity::setColor(float r, float g, float b, float a)
	{
		color = glm::vec4(r, g, b, a);
	}
	glm::vec4 entity::getColor()
	{
		return color;
	}
	glm::vec3 entity::getPos()
	{
		return v3pos;
	}
	glm::vec3 entity::getRot()
	{
		float degreesX = glm::degrees(v3rot.x);
		float degreesY = glm::degrees(v3rot.y);
		float degreesZ = glm::degrees(v3rot.z);
		glm::vec3 degreeRot = glm::vec3(degreesX, degreesY, degreesZ);
		return degreeRot;
	}
	glm::vec3 entity::getScale()
	{
		return v3scale;
	}
	glm::vec3 entity::GetFrontVector()
	{
		return frontVector;
	}
	glm::vec3 entity::GetRightVector()
	{
		return rightVector;
	}
	glm::vec3 entity::GetUpVector()
	{
		return upVector;
	}
	void entity::SetFrontVector(glm::vec3 newFrontVector)
	{
		frontVector = newFrontVector;
		alignDirectionVectorsWithFront();
	}
}