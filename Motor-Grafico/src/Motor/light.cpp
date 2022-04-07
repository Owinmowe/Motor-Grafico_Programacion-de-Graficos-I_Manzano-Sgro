#include "light.h"
#include "renderer.h"

namespace engine
{
	light::light(renderer* renderer)
	{
		lightDirection = glm::vec3(0, 0, 0);
		_renderer = renderer;
		_renderer->addLight(this);
	}
	light::~light()
	{
		_renderer->removeLight(this);
	}
	void light::draw()
	{

	}
	void light::setLightDirection(glm::vec3 newDirection)
	{
		lightDirection = newDirection;
	}
	glm::vec3 light::setLightDirection()
	{
		return lightDirection;
	}
}