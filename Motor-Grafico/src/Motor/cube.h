#include "entity.h"

namespace engine
{
	class ENGINE_API cube : public entity
	{
	public:
		cube(renderer* render);
		~cube();
		void draw() override;
	private:
		void setShader();
	};
}