#pragma once
#include "entity3D.h"

namespace engine
{

	class renderer;

	class ENGINE_API light : public entity3D
	{
	public:
		light();
		light(renderer* renderer);
		~light();
		void deInit();
		void draw() override;
	};
}
