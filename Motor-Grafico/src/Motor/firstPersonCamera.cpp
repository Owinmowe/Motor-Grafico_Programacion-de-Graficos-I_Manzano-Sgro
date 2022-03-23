#include "firstPersonCamera.h"

namespace engine
{
	firstPersonCamera::firstPersonCamera(renderer* currentRenderer, float fieldOfView, float nearClip, float farClip) :
		camera(currentRenderer, fieldOfView, nearClip, farClip)
	{

	}
	void firstPersonCamera::offsetCameraAim(float xoffset, float yoffset, bool constrainPitch)
	{
		yaw += xoffset;
		pitch += yoffset;

		if (constrainPitch)
		{
			if (pitch > 89.0f)
				pitch = 89.0f;
			if (pitch < -89.0f)
				pitch = -89.0f;
		}

		updateCameraVectors();
		updateCameraTransform();
	}
}
