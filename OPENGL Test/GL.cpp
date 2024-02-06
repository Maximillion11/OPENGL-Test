#include <glad/glad.h>

#include "GL.h"

#include "Utils.h"
#include "Input.h"

#include <string>

namespace GL
{
    Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
    GLFWwindow* window;

	void GL::Init(unsigned int activeScene)
	{
        // glfw: initialize and configure
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

        int monitorCount;
        int monitorX;
        int monitorY;

        GLFWmonitor** monitors = glfwGetMonitors(&monitorCount);
        const GLFWvidmode* videoMode = glfwGetVideoMode(monitors[0]);
        glfwGetMonitorPos(monitors[0], &monitorX, &monitorY);
        // Set the visibility window hint to false for subsequent window creation
        glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);

        // Use bodged activeScene to set window name
        std::string windowTitle = "Active Scene: " + std::to_string(activeScene);

        // glfw window creation
        window = glfwCreateWindow(Utils::WINDOW_WIDTH, Utils::WINDOW_HEIGHT, windowTitle.c_str(), NULL, NULL);
        if (window == NULL)
        {
            std::cout << "Failed to create GLFW window" << std::endl;
            glfwTerminate();
            return;
        }
        // Reset the window hints to default
        glfwDefaultWindowHints();

        // Move window to centre of screen
        glfwSetWindowPos(window, monitorX + (videoMode->width - Utils::WINDOW_WIDTH) / 2, monitorY + (videoMode->height - Utils::WINDOW_HEIGHT) / 2);

        // Show the window
        glfwShowWindow(window);

        glfwMakeContextCurrent(window);

        // tell GLFW to capture our mouse
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

        glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
        glfwSetCursorPosCallback(window, mouse_callback);
        glfwSetScrollCallback(window, scroll_callback);
        glfwSetKeyCallback(window, key_callback);
	}

    void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
    {
        Input::GetKey(key, scancode, action, mods);
    }

    void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
    {
        Input::GetMouse(xposIn, yposIn);
    }

    void scroll_callback(GLFWwindow* window, double xOffset, double yOffset)
    {
        Input::GetScrollWheel(xOffset, yOffset);
    }

    // glfw: whenever the window size changed (by OS or user resize) this callback function executes
    void framebuffer_size_callback(GLFWwindow* window, int width, int height)
    {
        // make sure the viewport matches the new window dimensions; note that width and 
        // height will be significantly larger than specified on retina displays.
        glViewport(0, 0, width, height);

        Utils::WINDOW_WIDTH = width;
        Utils::WINDOW_HEIGHT = height;
    }
}