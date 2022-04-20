#include "light.h"
#include "renderer.h"
#include "glew.h"
#include "glfw3.h"

namespace engine
{
	light::light(renderer* renderer)
	{
		_renderer = renderer;
		_renderer->addLight(this);

		float* vertex;
		unsigned int* indices;

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
	}
	light::~light()
	{
		_renderer->removeLight(this);
	}
	void light::deInit()
	{
		_renderer->deleteBaseBuffer(VAO, VBO, EBO);
	}
	void light::draw()
	{
		_renderer->solidShader.use();
		glm::vec3 newColor = glm::vec3(color.r, color.g, color.b);
		unsigned int colorLoc = glGetUniformLocation(_renderer->solidShader.ID, "color");
		glUniform3fv(colorLoc, 1, glm::value_ptr(newColor));

		unsigned int alphaLoc = glGetUniformLocation(_renderer->solidShader.ID, "a");
		glUniform1fv(alphaLoc, 1, &(color.a));

		_renderer->drawRequest(model, VAO, _vertices, _renderer->solidShader.ID, false);
	}
}