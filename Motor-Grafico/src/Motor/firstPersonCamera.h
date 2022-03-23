#pragma once

#include "camera.h"

namespace engine
{
	class ENGINE_API firstPersonCamera : public camera
	{
	public:
		firstPersonCamera(renderer* currentRenderer, float fieldOfView, float nearClip, float farClip);
		void offsetCameraAim(float xoffset, float yoffset, bool constrainPitch = true);
	};
}