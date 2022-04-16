#include "light.h"
#include "renderer.h"

namespace engine
{
	light::light(renderer* renderer)
	{
		_renderer = renderer;
		_renderer->addLight(this);
	}
	light::~light()
	{
		_renderer->removeLight(this);
	}
	void light::draw()
	{

	}
}