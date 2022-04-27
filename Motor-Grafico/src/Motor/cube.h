#include "entity3D.h"

namespace engine
{
	struct textureData;
	class Shader;

	class ENGINE_API cube : public entity3D
	{
	public:
		cube(renderer* render);
		~cube();
		void draw() override;
		void deInit();
	private:
		void setUVs();
		unsigned int bufferPosUVs = 0;

		textureData* dotTexture;
	};
}