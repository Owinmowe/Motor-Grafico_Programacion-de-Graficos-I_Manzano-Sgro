#pragma once
#include "exports.h"
#include "entity.h"

namespace engine
{
	class renderer;
	class material;

	class ENGINE_API entity3D : public entity
	{
	public:
		entity3D();
		~entity3D();

		void setMaterial(material* newMat);
		material* getMaterial();
		virtual void draw() = 0;

	protected:
		renderer* _renderer;

		unsigned int VAO, VBO, EBO, _vertices;
		material* mat;
	};
}