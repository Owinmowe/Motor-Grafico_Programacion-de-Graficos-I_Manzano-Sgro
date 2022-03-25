#include "entity.h"

namespace engine
{

	struct textureData;
	class Shader;

	class ENGINE_API cube : public entity
	{
	public:
		cube(renderer* render);
		~cube();
		void draw() override;
		void deInit();
		void toggleTextureUse();
		void setTexture(const char* filePathImage, bool invertImage);
	private:
		bool useTexture;
		unsigned int bufferPosUVs = 0;
		textureData* baseTexture;
	};
}