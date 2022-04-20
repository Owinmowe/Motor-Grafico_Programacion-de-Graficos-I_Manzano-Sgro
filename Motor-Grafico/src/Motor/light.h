#pragma once
#include "entity.h"

namespace engine
{

	class renderer;

	class ENGINE_API light : public entity
	{
	public:
		light(renderer* renderer);
		~light();
		void deInit();
		void draw() override;
	};
}
