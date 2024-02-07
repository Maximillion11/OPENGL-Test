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
    // Scene 0 = LearnOpenGLGettingStarted
    unsigned int VBOgettingstarted, VAOgettingstarted;
    unsigned int texture1gettingstarted, texture2gettingstarted;

    // Scene 1 = LearnOpenGLLighting
    unsigned int VBOlighting, cubeVAOlighting;
    unsigned int lightVAOlighting;
    unsigned int texture1lighting, texture2lighting;

	void Renderer::Init(unsigned int sceneID) {
        // glad: load all OpenGL function pointers
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            std::cout << "Failed to initialize GLAD" << std::endl;
            return;
        }

        // build and compile our shader program
        Shaders::AssignShaders(sceneID);

        // Configure global opengl state
        glEnable(GL_DEPTH_TEST);

        // Scene 0 = LearnOpenGLGettingStarted
        if (sceneID == 0)
        {
            glGenVertexArrays(1, &VAOgettingstarted);
            glGenBuffers(1, &VBOgettingstarted);

            glBindBuffer(GL_ARRAY_BUFFER, VBOgettingstarted);
            glBufferData(GL_ARRAY_BUFFER, sizeof(Primitives::Cube), Primitives::Cube, GL_STATIC_DRAW);

            glBindVertexArray(VAOgettingstarted);

            // position attribute
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
            glEnableVertexAttribArray(0);
            // normal attribute NOT USED
            //glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
            //glEnableVertexAttribArray(1);
            // texture coord attribute
            glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
            glEnableVertexAttribArray(1);

            texture1gettingstarted = CreateTexture("Images/container.jpg");
            texture2gettingstarted = CreateTexture("Images/awesomeface.png");

            // tell opengl for each sampler to which texture unit it belongs to (only has to be done once)
            Shaders::OpenGLGettingStartedShader.use();
            Shaders::OpenGLGettingStartedShader.setInt("texture1", 0);
            Shaders::OpenGLGettingStartedShader.setInt("texture2", 1);
        }
        // Scene 1 = LearnOpenGLLighting
        else if (sceneID == 1) {
            // -----CUBE
            // Configure the cube's VAO (and VBO)
            glGenVertexArrays(1, &cubeVAOlighting);
            glGenBuffers(1, &VBOlighting);

            glBindBuffer(GL_ARRAY_BUFFER, VBOlighting);
            glBufferData(GL_ARRAY_BUFFER, sizeof(Primitives::Cube), Primitives::Cube, GL_STATIC_DRAW);

            glBindVertexArray(cubeVAOlighting);

            // position attribute
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
            glEnableVertexAttribArray(0);
            // normals attribute
            glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
            glEnableVertexAttribArray(1);
            // texture coord attribute
            glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
            glEnableVertexAttribArray(2);
            // -----

            // -----CUBE LIGHT SOURCE
            // Configure the light's VAO (VBO stays the same; the vertices are the same for the light object which is also a 3D cube)
            glGenVertexArrays(1, &lightVAOlighting);
            glBindVertexArray(lightVAOlighting);

            // we only need to bind to the VBO (to link it with glVertexAttribPointer), no need to fill it; the VBO's data already contains all we need (it's already bound, but we do it again for educational purposes)
            glBindBuffer(GL_ARRAY_BUFFER, VBOlighting);

            // position attribute
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
            glEnableVertexAttribArray(0);
            // -----

            texture1lighting = CreateTexture("Images/container2.png");
            texture2lighting = CreateTexture("Images/container2_specular.png");
        }
	}

    void Renderer::Deallocate(unsigned int sceneID)
    {
        // De-allocate all resources once they've outlived their purpose
        // Scene 0 = LearnOpenGLGettingStarted
        if (sceneID == 0)
        {
            glDeleteVertexArrays(1, &VAOgettingstarted);
            glDeleteBuffers(1, &VBOgettingstarted);
        }
        // Scene 1 = LearnOpenGLLighting
        else if (sceneID == 1) {
            glDeleteVertexArrays(1, &cubeVAOlighting);
            glDeleteVertexArrays(1, &lightVAOlighting);
            glDeleteBuffers(1, &VBOlighting);
        }
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