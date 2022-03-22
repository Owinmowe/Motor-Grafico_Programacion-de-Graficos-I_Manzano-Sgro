#include "input.h"
#include "glfw3.h"
#include "window.h"
#include <algorithm>

namespace engine
{
	void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
	void mouse_callback(GLFWwindow* window, double xpos, double ypos);

	std::list<int> currentKeysDown;
	glm::vec2 mousePosition;
	glm::vec2 deltaMousePosition;
	bool firstMouse = false;
	const float sensitivity = 0.1f;


	input::input(window* window)
	{
		glfwSetKeyCallback(window->getGLFWwindow(), keyCallback);
		glfwSetCursorPosCallback(window->getGLFWwindow(), mouse_callback);
		mousePosition.x = window->getWidth() / 2;
		mousePosition.y = window->getHeight() / 2;
	}

	input::~input()
	{

	}

	bool input::isKeyPressed(int keycode, window* window)
	{
		int aux = glfwGetKey(window->getGLFWwindow(), keycode);
		return aux == GLFW_PRESS;
	}

	bool input::isKeyDown(int keycode, window* window)
	{
		std::list<int>::iterator it = find(currentKeysDown.begin(), currentKeysDown.end(), keycode);
		if(it != currentKeysDown.end())
		{
			currentKeysDown.remove(keycode);
			return true;
		}
		return false;
	}
	glm::vec2 input::getMousePosition()
	{
		return mousePosition;
	}
	glm::vec2 input::getDeltaMousePosition()
	{
		glm::vec2 previousOffset = deltaMousePosition;
		deltaMousePosition = glm::vec2(0, 0);
		return previousOffset;
	}
	void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		if(action == GLFW_PRESS)
		{
			currentKeysDown.push_front(key);
		}
		else if(action == GLFW_RELEASE)
		{
			currentKeysDown.remove(key);
		}
	}
	void mouse_callback(GLFWwindow* window, double posX, double posY)
	{

		if (firstMouse)
		{
			mousePosition.x = posX;
			mousePosition.y = posY;
			firstMouse = false;
		}

		float offsetPosX = posX - mousePosition.x;
		float offsetPosY = mousePosition.y - posY; //Coordenadas en Y estan invertidas
		mousePosition.x = posX;
		mousePosition.y = posY;

		offsetPosX *= sensitivity;
		offsetPosY *= sensitivity;
		deltaMousePosition.x = offsetPosX;
		deltaMousePosition.y = offsetPosY;
	}
}