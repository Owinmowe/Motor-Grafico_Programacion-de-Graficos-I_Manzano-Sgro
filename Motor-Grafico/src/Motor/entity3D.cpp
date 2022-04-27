#include "entity3D.h"
#include "renderer.h"
#include "material.h"

namespace engine
{
	entity3D::entity3D()
	{
		_renderer = nullptr;
		mat = nullptr;
	}
	entity3D::~entity3D()
	{

	}
	void entity3D::setMaterial(material* newMat)
	{
		mat = newMat;
	}
	material* entity3D::getMaterial()
	{
		return mat;
	}
}