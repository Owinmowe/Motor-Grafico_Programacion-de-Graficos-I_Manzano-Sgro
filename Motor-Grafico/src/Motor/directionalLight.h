#pragma once
#include "light.h"

namespace engine
{

	class renderer;

	class ENGINE_API directionalLight : public light
	{
	public:
		directionalLight(renderer* renderer);
	};
}
