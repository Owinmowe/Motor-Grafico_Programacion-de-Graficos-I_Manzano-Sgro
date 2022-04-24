#pragma once
#include "exports.h"
#include "material.h"
#include "entity.h"

namespace engine
{
	class renderer;

	class ENGINE_API entity3D : public entity
	{
	public:
		entity3D();
		~entity3D();

		void setColor(glm::vec4 color);
		void setColor(float r, float g, float b, float a);
		glm::vec4 getColor();
		virtual void draw() = 0;

	protected:
		renderer* _renderer;
		glm::vec4 color;
		unsigned int VAO, VBO, EBO, _vertices;
		material mat;
	};
}