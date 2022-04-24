#include "entity3D.h"
#include "renderer.h"

namespace engine
{
	entity3D::entity3D()
	{
		_renderer = nullptr;
		mat = material();
	}
	entity3D::~entity3D()
	{

	}
	void entity3D::setMaterial(material newMat)
	{
		mat = newMat;
	}
	material entity3D::getMaterial()
	{
		return mat;
	}
}