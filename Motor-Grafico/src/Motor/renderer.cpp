#include "renderer.h"

#include "glew.h"
#include "glfw3.h"
#include "light.h"

namespace engine
{
	renderer::renderer()
	{
		currentWindow = NULL;
		viewMatrix = glm::mat4();
		projectionMatrix = glm::mat4();
		clearColor = glm::vec4(0, 0, 0, 1);
		cameraPosition = glm::vec3();
	}
	renderer::renderer(window* window)
	{
		clearColor = glm::vec4(0, 0, 0, 1);

		currentWindow = window;

		cameraPosition = glm::vec3();

		viewMatrix = glm::mat4(1.0f);
		//viewMatrix = glm::lookAt(glm::vec3(0, 0, -15), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
		projectionMatrix = glm::mat4(1.0f);
		//projectionMatrix = glm::perspective(glm::radians(90.0f), (float)currentWindow->getWidth() / (float)currentWindow->getHeight(), 0.1f, 100.0f);		
		//projectionMatrix = glm::ortho(0.0f, (float)currentWindow->getWidth(), 0.0f, (float)currentWindow->getHeight(), 0.1f, 100.0f);
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LESS);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}
	renderer::~renderer()
	{

	}
	void renderer::setCurrentWindow(window* window)
	{
		currentWindow = window;
	}
	void renderer::startDraw()
	{
		glClearColor(clearColor.r, clearColor.g, clearColor.b, clearColor.a);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}
	void renderer::endDraw()
	{
		glfwSwapBuffers(currentWindow->getGLFWwindow());
	}
	void renderer::drawRequest(glm::mat4 modelMatrix, unsigned int VAO, unsigned int vertices, unsigned int usedShaderID, bool useLight, material mat)
	{
		unsigned int modelLoc = glGetUniformLocation(usedShaderID, "model");
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelMatrix));

		unsigned int viewLoc = glGetUniformLocation(usedShaderID, "view");
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(viewMatrix));

		unsigned int projectionLoc = glGetUniformLocation(usedShaderID, "projection");
		glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

		if(useLight)
		{
			glm::vec3 lightColor = glm::vec3(0, 0, 0);
			glm::vec3 lightPos = glm::vec3(0, 0, 0);
			std::list<light*>::iterator it;
			for (auto const& i : lights) {
				lightColor = i->getColor();
				lightPos = i->getPos();
			}
			unsigned int lightColorLoc = glGetUniformLocation(usedShaderID, "lightColor");
			glUniform3fv(lightColorLoc, 1, glm::value_ptr(lightColor));

			unsigned int lightPosLoc = glGetUniformLocation(usedShaderID, "lightPosition");
			glUniform3fv(lightPosLoc, 1, glm::value_ptr(lightPos));

			unsigned int ambientLightLoc = glGetUniformLocation(usedShaderID, "ambientLight");
			glUniform3fv(ambientLightLoc, 1, glm::value_ptr(lightColor * 0.01f));

			unsigned int cameraPosLoc = glGetUniformLocation(usedShaderID, "cameraPos");
			glUniform3fv(cameraPosLoc, 1, glm::value_ptr(cameraPosition));

			unsigned int ambientLoc = glGetUniformLocation(usedShaderID, "material.ambient");
			glUniform3fv(ambientLoc, 1, glm::value_ptr(mat.ambient));

			unsigned int diffuseLoc = glGetUniformLocation(usedShaderID, "material.diffuse");
			glUniform3fv(diffuseLoc, 1, glm::value_ptr(mat.diffuse));
			
			unsigned int specularLoc = glGetUniformLocation(usedShaderID, "material.specular");
			glUniform3fv(specularLoc, 1, glm::value_ptr(mat.specular));

			unsigned int shininessLoc = glGetUniformLocation(usedShaderID, "material.shininess");
			glUniform1fv(shininessLoc, 1, &(mat.shininess));
		}


		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, vertices, GL_UNSIGNED_INT, 0);
	}
	void renderer::createBaseBuffer(unsigned int& VAO, unsigned int& VBO, unsigned int& EBO)
	{
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &EBO);
	}
	void renderer::createExtraBuffer(unsigned int& buffer, int size)
	{
		glGenBuffers(size, &buffer);
	}
	void renderer::bindBaseBufferRequest(unsigned int VAO, unsigned int VBO, unsigned int EBO, float* vertices, unsigned int sizeOfVertices, unsigned int* indices, unsigned int sizeOfIndices)
	{
		glBindVertexArray(VAO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeOfVertices, vertices, GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeOfIndices, indices, GL_STATIC_DRAW);
	}
	void renderer::bindExtraBuffer(unsigned int buffer, float* data, unsigned int sizeOfData, unsigned int bufferType)
	{
		glBindBuffer(GL_ARRAY_BUFFER, buffer);
		glBufferData(GL_ARRAY_BUFFER, sizeOfData, data, bufferType);
	}
	void renderer::deleteBaseBuffer(unsigned int& VAO, unsigned int& VBO, unsigned int& EBO)
	{
		glDeleteVertexArrays(1, &VAO);
		glDeleteBuffers(1, &VBO);
		glDeleteBuffers(1, &EBO);
	}
	void renderer::deleteExtraBuffer(unsigned int& buffer, int size)
	{
		glDeleteBuffers(size, &buffer);
	}
	void renderer::setClearColor(glm::vec4 color)
	{
		clearColor = color;
	}
	void renderer::setViewMatrix(glm::mat4 viewMatrix)
	{
		this->viewMatrix = viewMatrix;
	}
	void renderer::setProjectionMatrix(glm::mat4 projectionMatrix)
	{
		this->projectionMatrix = projectionMatrix;
	}
	window* renderer::getCurrentWindow()
	{
		return currentWindow;
	}
	void renderer::addLight(light* light)
	{
		lights.push_back(light);
	}
	void renderer::removeLight(light* light)
	{
		lights.remove(light);
	}
	void renderer::setCameraPosition(glm::vec3 newCameraPosition)
	{
		cameraPosition = newCameraPosition;
	}
}