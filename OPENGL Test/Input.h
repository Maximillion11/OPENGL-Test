#ifndef INPUT_H
#define INPUT_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Camera.h"
#include "Utils.h"
#include "GL.h"

#include <map>

namespace Input
{
	extern void GetKey(int key, int scancode, int action, int mods);

	extern void GetMouse(double xposIn, double yposIn);

	extern void GetScrollWheel(double xOffset, double yOffset);

	extern void CheckKeys();

	extern bool KeyPressed(int key);
}

#endif