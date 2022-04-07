#pragma once
#include "entity.h"

namespace engine
{

	class renderer;

	class ENGINE_API light : public entity
	{
	public:
		light(renderer* renderer);
		~light();
		void draw() override;
		void setLightDirection(glm::vec3 newDirection);
		glm::vec3 setLightDirection();
	private:
		glm::vec3 lightDirection;
	};
}
