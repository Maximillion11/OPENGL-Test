#include "Renderer.h"

#include "stb_image.h"
#define STB_IMAGE_IMPLEMENTATION

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Primitives.h"
#include "Shaders.h"

#include <string>

namespace Renderer
{
    unsigned int VBO, VAO, EBO;
    unsigned int texture1, texture2;

	void Renderer::Init() {
        // glad: load all OpenGL function pointers
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            std::cout << "Failed to initialize GLAD" << std::endl;
            return;
        }

        // build and compile our shader program
        Shaders::AssignShaders();

        //Enable zBuffer
        glEnable(GL_DEPTH_TEST);

        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);

        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(Primitives::Cube), Primitives::Cube, GL_STATIC_DRAW);

        //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        //glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

        // position attribute
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        // texture coord attribute
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);

        texture1 = CreateTexture("container.jpg");
        texture2 = CreateTexture("awesomeface.png");

        // tell opengl for each sampler to which texture unit it belongs to (only has to be done once)
        Shaders::MainShader.use();
        Shaders::MainShader.setInt("texture1", 0);
        Shaders::MainShader.setInt("texture2", 1);
	}

    void Renderer::Deallocate()
    {
        // De-allocate all resources once they've outlived their purpose:
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
        glDeleteBuffers(1, &EBO);
    }

    unsigned int Renderer::CreateTexture(const char* fileLocation)
    {
        unsigned int texture;

        // load and create a texture 
        // texture
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        // set the texture wrapping parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        // set texture filtering parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        // load image, create texture and generate mipmaps
        int width, height, nrChannels;
        stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
        unsigned char* data = stbi_load(fileLocation, &width, &height, &nrChannels, 0);
        if (data)
        {
            // Turn char* fileLocation to string
            std::string fileLocationString(fileLocation);
            // Create string to store filetype
            std::string fileType;

            // Loop through string
            bool writeToString = false;
            for (char& currentCharacter : fileLocationString)
            {
                if (writeToString)
                {
                    // Append string with currentCharacter
                    fileType += tolower(currentCharacter);
                // When currentCharacter == '.', set writeToString TRUE as the next characters will be the file type
                } else if (currentCharacter == '.')
                {
                    writeToString = true;
                }
            }

            // Add alpha channel if PNG file
            if (fileType == "png")
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
            else
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

            glGenerateMipmap(GL_TEXTURE_2D);
        }
        else
        {
            std::cout << "Failed to load texture" << std::endl;
        }
        stbi_image_free(data);

        return texture;
    }
}