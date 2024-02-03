#ifndef GL_H
#define GL_H

#include <GLFW/glfw3.h>

#include "Camera.h"

namespace GL
{
	extern Camera camera;
	extern GLFWwindow* window;

	extern void framebuffer_size_callback(GLFWwindow* window, int width, int height);
	extern void mouse_callback(GLFWwindow* window, double xpos, double ypos);
	extern void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
	extern void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

	extern void Init();
}

#endif