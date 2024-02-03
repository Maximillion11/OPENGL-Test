#include "Input.h"

#include "Utils.h"
#include "GL.h"

#include <map>

namespace Input
{
	std::map<int, int> keysPressed;

	bool firstMouse = true;

	float lastMouseX = Utils::WINDOW_WIDTH / 2;
	float lastMouseY = Utils::WINDOW_HEIGHT / 2;

	bool shiftHeld = false;

	void Input::GetKey(int key, int scancode, int action, int mods)
	{
		if (action == GLFW_PRESS)
		{
			if (key == GLFW_KEY_LEFT_SHIFT)
				shiftHeld = true;
			else
				keysPressed[key] = scancode;
		}

		if (action == GLFW_RELEASE)
		{
			if (key == GLFW_KEY_LEFT_SHIFT)
				shiftHeld = false;
			else
				keysPressed.erase(key);
		}
	}

	void Input::GetMouse(double xposIn, double yposIn)
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

		GL::camera.ProcessMouseMovement(xOffset, yOffset);
	}

	void Input::GetScrollWheel(double xOffsetIn, double yOffsetIn)
	{
		float xOffset = static_cast<float>(xOffsetIn);
		float yOffset = static_cast<float>(yOffsetIn);

		GL::camera.ProcessMouseScroll(yOffset);
	}

	void Input::CheckKeys() {
		if (KeyPressed(GLFW_KEY_W)) {
			GL::camera.ProcessKeyboard(FORWARD, shiftHeld);
		}
		if (KeyPressed(GLFW_KEY_A)) {
			GL::camera.ProcessKeyboard(LEFT, shiftHeld);
		}
		if (KeyPressed(GLFW_KEY_S)) {
			GL::camera.ProcessKeyboard(BACKWARD, shiftHeld);
		}
		if (KeyPressed(GLFW_KEY_D)) {
			GL::camera.ProcessKeyboard(RIGHT, shiftHeld);
		}
		if (KeyPressed(GLFW_KEY_SPACE)) {
			GL::camera.ProcessKeyboard(UP, shiftHeld);
		}
		if (KeyPressed(GLFW_KEY_LEFT_CONTROL)) {
			GL::camera.ProcessKeyboard(DOWN, shiftHeld);
		}

		if (KeyPressed(GLFW_KEY_ESCAPE)) {
			glfwSetWindowShouldClose(GL::window, true);
		}
	}

	bool Input::KeyPressed(int key)
	{
		if (keysPressed.count(key) > 0)
			return true;

		return false;
	}
}