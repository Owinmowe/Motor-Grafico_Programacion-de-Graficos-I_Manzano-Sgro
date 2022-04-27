#pragma once
#include "exports.h"
#include "glm/glm.hpp"

namespace engine
{

	class textureData;

	class ENGINE_API material
	{
	public:
		material();
		~material();
		void setDiffuseStrenght(glm::vec3 strenght);
		void setDiffuseMap(const char* path, bool invertVertical);
		textureData* getDiffuseMap();

		void setSpecularStrenght(glm::vec3 strenght);
		void setSpecularMap(const char* path, bool invertVertical);
		textureData* getSpecularMap();

		void setAmbientStrenght(glm::vec3 strenght);
		void setShininess(float shininess);
	private:
		glm::vec3 diffuseStrenght;
		textureData* diffuseMap;

		glm::vec3 specularStrenght;
		textureData* specularMap;

		float shininess;
		glm::vec3 ambientStrenght;

		friend class renderer;
	};
}