#include "exports.h"
#pragma once

namespace engine
{
	class ENGINE_API time
	{
	public:
		time();
		~time();
		static float getDeltaTime();
		static void updateDeltaTime(float currentTime);
	private:
		static float currentDeltaTime;
		static float lastDeltaTime;
	};
}