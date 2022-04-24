#include "cube.h"
#include "renderer.h"
#include "textureImporter.h"
#include "glew.h"
#include "glfw3.h"

namespace engine
{
	cube::cube(renderer* render)
	{
		_renderer = render;
		bufferPosUVs = 0;

		float* vertex;
		unsigned int* indices;
		useTexture = false;
		baseTexture = nullptr;

		vertex = new float[216]
		{
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, -1.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, -1.0f,
			-0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, -1.0f,
			-0.5f,  0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, -1.0f,

			 0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
			 0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
			-0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
			-0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f,

			-0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, -1.0f, 0.0f, 0.0f,
			-0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, -1.0f, 0.0f, 0.0f,
			-0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 1.0f, -1.0f, 0.0f, 0.0f,
			-0.5f,  0.5f, 0.0f, 1.0f, 1.0f, 1.0f, -1.0f, 0.0f, 0.0f,

			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
			 0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,

			 0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f,
			-0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f,
			-0.5f,  0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f,

			 0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, -1.0f, 0.0f,
			-0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, -1.0f, 0.0f,
			-0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, -1.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, -1.0f, 0.0f

		};
		indices = new unsigned int[36]
		{
			0, 1, 3, // FRONT
			1, 2, 3,

			4, 5, 7, // BACK
			5, 6, 7,

			8, 9, 11, // LEFT  
			9, 10, 11,

			12, 13, 15, // BOTTOM
			13, 14, 15,

			16, 17, 19, // RIGHT 
			17, 18, 19,

			20, 21, 23, // TOP
			21, 22, 23
		};
		_renderer->createBaseBuffer(VAO, VBO, EBO);
		_renderer->bindBaseBufferRequest(VAO, VBO, EBO, vertex, sizeof(vertex) * 216, indices, sizeof(indices) * 36);
		_vertices = 36;

		delete[] vertex;
		delete[] indices;

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)0);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(3 * sizeof(float)));
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(6 * sizeof(float)));

		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);

		dotTexture = new textureData(textureImporter::loadTexture("../res/assets/textures/whiteDot.png", false));
		useTexture = false;

	}
	cube::~cube()
	{

	}
	void cube::draw()
	{
		_renderer->textureShader.use();
		unsigned int texture = useTexture ? baseTexture->ID : dotTexture->ID;
		glBindTexture(GL_TEXTURE_2D, texture);
		unsigned int textureLoc = glGetUniformLocation(_renderer->textureShader.ID, "ourTexture");
		glUniform1f(textureLoc, (GLfloat)texture);

		glm::vec3 newColor = glm::vec3(1, 1, 1);
		unsigned int colorLoc = glGetUniformLocation(_renderer->textureShader.ID, "color");
		glUniform3fv(colorLoc, 1, glm::value_ptr(newColor));

		float alpha = 1.0f;
		unsigned int alphaLoc = glGetUniformLocation(_renderer->textureShader.ID, "a");
		glUniform1fv(alphaLoc, 1, &(alpha));

		_renderer->drawRequest(model, VAO, _vertices, _renderer->textureShader.ID, true, mat);
	}
	void cube::toggleTextureUse()
	{
		if(baseTexture != nullptr)
		{
			useTexture = !useTexture;
		}
		else
		{
			std::cout << "Can't toggle texture on cube because it doesn't have a texture";
		}
	}
	void cube::setTexture(const char* filePathImage, bool invertImage)
	{
		float UVs[] =
		{
			1.0f, 1.0f,
			1.0f, 0.0f,
			0.0f, 0.0f,
			0.0f, 1.0f,

			1.0f, 1.0f,
			1.0f, 0.0f,
			0.0f, 0.0f,
			0.0f, 1.0f,

			1.0f, 1.0f,
			1.0f, 0.0f,
			0.0f, 0.0f,
			0.0f, 1.0f,

			1.0f, 1.0f,
			1.0f, 0.0f,
			0.0f, 0.0f,
			0.0f, 1.0f,

			1.0f, 1.0f,
			1.0f, 0.0f,
			0.0f, 0.0f,
			0.0f, 1.0f,

			1.0f, 1.0f,
			1.0f, 0.0f,
			0.0f, 0.0f,
			0.0f, 1.0f
		};
		_renderer->createExtraBuffer(bufferPosUVs, 1);
		_renderer->bindExtraBuffer(bufferPosUVs, UVs, sizeof(UVs), GL_DYNAMIC_DRAW);
		glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(3);

		baseTexture = new textureData(textureImporter::loadTexture(filePathImage, invertImage));
		useTexture = true;
	}
	void cube::deInit()
	{
		_renderer->deleteBaseBuffer(VAO, VBO, EBO);
		_renderer->deleteExtraBuffer(bufferPosUVs, 1);
		glDeleteTextures(1, &baseTexture->ID);
		delete baseTexture;
	}
}