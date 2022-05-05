#include "directionalLight.h"
#include "renderer.h"

namespace engine
{
	directionalLight::directionalLight(renderer* renderer) : light(renderer)
	{
		_renderer->addDirectionalLight(this);
	}
}
