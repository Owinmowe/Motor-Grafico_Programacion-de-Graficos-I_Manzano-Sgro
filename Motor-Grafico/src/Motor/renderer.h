#pragma once
#include "exports.h"
#include "window.h"
#include "shader.h"
#include "material.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include <list>

namespace engine
{

	class directionalLight;

	class ENGINE_API renderer
	{
	public:
		renderer();
		renderer(window* window);
		~renderer();
		void setCurrentWindow(window* window);
		void createBaseBuffer(unsigned int& VAO, unsigned int& VBO, unsigned int& EBO);
		void createExtraBuffer(unsigned int& buffer, int size);
		void bindBaseBufferRequest(unsigned int VAO, unsigned int VBO, unsigned int EBO, float* vertices, unsigned int sizeOfVertices, unsigned int* indices, unsigned int sizeOfIndices);
		void bindExtraBuffer(unsigned int buffer, float* data, unsigned int sizeOfData, unsigned int bufferType);
		void drawRequest(glm::mat4 model, unsigned int VAO, unsigned int vertices, unsigned int usedShaderID, bool useLight);
		void drawRequest(glm::mat4 model, unsigned int VAO, unsigned int vertices, unsigned int usedShaderID, bool useLight, material* mat);
		void deleteBaseBuffer(unsigned int& VAO, unsigned int& VBO, unsigned int& EBO);
		void deleteExtraBuffer(unsigned int& buffer, int size);
		void startDraw();
		void endDraw();
		void setClearColor(glm::vec4 color);
		void setViewMatrix(glm::mat4 viewMatrix);
		void setProjectionMatrix(glm::mat4 projectionMatrix);
		window* getCurrentWindow();

		//TODO Pensar mejor implementacion, probablemente materiales
		Shader textureShader = Shader("../src/Motor/Shaders/3DTextureVertex.shader", "../src/Motor/Shaders/3DTextureFragment.shader");
		Shader solidShader = Shader("../src/Motor/Shaders/SolidVertex.shader", "../src/Motor/Shaders/SolidFragment.shader");

		void addDirectionalLight(directionalLight* light);

		void setCameraPosition(glm::vec3 newCameraPosition);

	private:
		void setDirectionalLight(directionalLight* dirLight, int shaderID);
		directionalLight* dirLight;
		float lastTime = 0;
		window* currentWindow;
		glm::vec4 clearColor;
		glm::mat4 viewMatrix;
		glm::mat4 projectionMatrix;
		glm::vec3 cameraPosition;
	};
}
