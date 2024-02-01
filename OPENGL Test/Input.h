#ifndef INPUT_H
#define INPUT_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Camera.h"

namespace Input
{
	extern void GetKey(int key, int scancode, int action, int mods);

	extern void GetMouse(Camera* camera, double xposIn, double yposIn);

	extern void GetScrollWheel(Camera* camera, double xOffset, double yOffset);

	extern void CheckKeys(GLFWwindow* window, Camera* camera);

	extern bool KeyPressed(int key);
}

#endif