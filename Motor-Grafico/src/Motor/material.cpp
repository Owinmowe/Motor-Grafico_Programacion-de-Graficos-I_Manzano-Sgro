#include "material.h"
#include "textureImporter.h"
#include "glfw3.h"

namespace engine
{
	material::material()
	{
		diffuseStrenght = glm::vec3(.5, .5, .5);
		diffuseMap = nullptr;

		specularStrenght = glm::vec3(1, 1, 1);
		specularMap = nullptr;

		ambientStrenght = glm::vec3(.1, .1, .1);

		shininess = 1;
	}
	material::~material()
	{
		if(diffuseMap != nullptr)
		{
			glDeleteTextures(1, &diffuseMap->ID);
			delete diffuseMap;
		}
		if(specularMap != nullptr)
		{
			glDeleteTextures(1, &specularMap->ID);
			delete specularMap;
		}
	}
	void material::setDiffuseStrenght(glm::vec3 strenght)
	{
		diffuseStrenght = strenght;
	}
	void material::setDiffuseMap(const char* path, bool invertVertical)
	{
		diffuseMap = new textureData(textureImporter::loadTexture(path, invertVertical));
	}
	textureData* material::getDiffuseMap()
	{
		return diffuseMap;
	}
	void material::setSpecularStrenght(glm::vec3 strenght)
	{
		specularStrenght = strenght;
	}
	void material::setSpecularMap(const char* path, bool invertVertical)
	{
		specularMap = new textureData(textureImporter::loadTexture(path, invertVertical));
	}
	textureData* material::getSpecularMap()
	{
		return specularMap;
	}
	void material::setAmbientStrenght(glm::vec3 strenght)
	{
		ambientStrenght = strenght;
	}
	void material::setShininess(float shininess)
	{
		this->shininess = shininess;
	}
}