#pragma once
#include "entity3D.h"

namespace engine
{

	class renderer;

	class ENGINE_API light abstract : public entity3D
	{
	public:
		light(renderer* renderer);

		void setColor(glm::vec3 color);
		void setColor(float r, float g, float b);
		glm::vec3 getColor();

		void deInit();
		void draw() override;
	private:
		glm::vec3 lightColor;
	};
}
