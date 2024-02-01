#include "Input.h"

#include "Utils.h"

#include <map>

namespace Input
{
	std::map<int, int> keysPressed;

	bool firstMouse = true;

	float lastMouseX = Utils::SCR_WIDTH / 2;
	float lastMouseY = Utils::SCR_HEIGHT / 2;

	void Input::GetKey(int key, int scancode, int action, int mods)
	{
		if (action == GLFW_PRESS)
		{
			keysPressed[key] = scancode;
		}

		if (action == GLFW_RELEASE)
		{
			keysPressed.erase(key);
		}
	}

	void Input::GetMouse(Camera* camera, double xposIn, double yposIn)
	{
		float xpos = static_cast<float>(xposIn);
		float ypos = static_cast<float>(yposIn);

		if (firstMouse)
		{
			lastMouseX = xpos;
			lastMouseY = ypos;
			firstMouse = false;
		}

		// Get mouse offset from last callback
		float xOffset = xpos - lastMouseX;
		float yOffset = lastMouseY - ypos; // reversed since y-coordinates range from bottom to top
		lastMouseX = xpos;
		lastMouseY = ypos;

		camera->ProcessMouseMovement(xOffset, yOffset);
	}

	void Input::GetScrollWheel(Camera* camera, double xOffsetIn, double yOffsetIn)
	{
		float xOffset = static_cast<float>(xOffsetIn);
		float yOffset = static_cast<float>(yOffsetIn);

		camera->ProcessMouseScroll(yOffset);
	}

	void Input::CheckKeys(GLFWwindow* window, Camera* camera) {
		if (KeyPressed(GLFW_KEY_W)) {
			camera->ProcessKeyboard(FORWARD);
		}
		if (KeyPressed(GLFW_KEY_A)) {
			camera->ProcessKeyboard(LEFT);
		}
		if (KeyPressed(GLFW_KEY_S)) {
			camera->ProcessKeyboard(BACKWARD);
		}
		if (KeyPressed(GLFW_KEY_D)) {
			camera->ProcessKeyboard(RIGHT);
		}

		if (KeyPressed(GLFW_KEY_ESCAPE)) {
			glfwSetWindowShouldClose(window, true);
		}
	}

	bool Input::KeyPressed(int key)
	{
		if (keysPressed.count(key) > 0) {
			return true;
		}
		return false;
	}
}