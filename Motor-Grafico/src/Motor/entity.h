#pragma once
#include "exports.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

namespace engine
{

	class ENGINE_API entity
	{
	public:
		entity();
		~entity();
		void setPos(glm::vec3 pos);
		void setPos(float x, float y, float z);
		void setRot(glm::vec3 rot);
		void setRot(float x, float y, float z);
		void setScale(glm::vec3 scale);
		void setScale(float x, float y, float z);

		glm::vec3 getPos();
		glm::vec3 getRot();
		glm::vec3 getScale();

		glm::vec3 GetFrontVector();
		glm::vec3 GetRightVector();
		glm::vec3 GetUpVector();

		void SetFrontVector(glm::vec3 newFrontVector);

	protected:

		glm::vec3 v3pos;
		glm::vec3 v3rot;
		glm::vec3 v3scale;

		glm::mat4 model;

		glm::mat4 translate;
		glm::mat4 rotateX;
		glm::mat4 rotateY;
		glm::mat4 rotateZ;
		glm::mat4 scale;

		glm::vec3 rightVector;
		glm::vec3 frontVector;
		glm::vec3 upVector;
		float yaw;
		float pitch;
		float roll;
		
		void updateModelMatrix();
		void alignDirectionVectorsWithFront();
		void alignDirectionVectorsWithRotation();

	private:
		void setRotX(float x);
		void setRotY(float y);
		void setRotZ(float z);
	};
}