#include "entity3D.h"
#include "renderer.h"

namespace engine
{
	entity3D::entity3D()
	{
		_renderer = nullptr;
		setColor(glm::vec4(1.0f));
		mat = material();
	}
	entity3D::~entity3D()
	{

	}
	void entity3D::setColor(glm::vec4 color)
	{
		this->color = color;
	}
	void entity3D::setColor(float r, float g, float b, float a)
	{
		setColor(glm::vec4(r, g, b, a));
	}
	glm::vec4 entity3D::getColor()
	{
		return color;
	}
}