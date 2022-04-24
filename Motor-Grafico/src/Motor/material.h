#pragma once
#include "glm/glm.hpp"

namespace engine
{
	struct material
	{
		material()
		{
			ambient = glm::vec3(.1, .1, .1);
			diffuse = glm::vec3(1, 1, 1);
			specular = glm::vec3(1, 1, 1);
			shininess = 1;
		}

		glm::vec3 ambient;
		glm::vec3 diffuse;
		glm::vec3 specular;
		float shininess;
	};
}