#pragma once
#include "exports.h"
#include "entity.h"

namespace engine
{
	class collisionManager;
	class renderer;

	enum class collisionType { up, down, left, right, none };

	class ENGINE_API entity2D : public entity
	{
	public:
		entity2D();
		~entity2D();

		void setColor(glm::vec4 color);
		void setColor(float r, float g, float b, float a);
		glm::vec4 getColor();
		virtual void draw() = 0;

		void setCollisionManager(collisionManager* colManager);
		collisionType checkCollision(entity2D& target, float& xOverlap, float& yOverlap);
		void applyCollisionRestrictions(collisionType colType, float xOverlap, float yOverlap, bool halfOverlap);

	protected:
		renderer* _renderer;
		glm::vec4 color;
		unsigned int VAO, VBO, EBO, _vertices;

	private:
		collisionManager* colManager;
	};
}