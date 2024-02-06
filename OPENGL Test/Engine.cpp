#include "Shaders.h"
#include "Shader.h"

#include "Utils.h"
#include "Input.h"
#include "Renderer.h"
#include "GL.h"

enum SceneType {
    LearnOpenGLGettingStarted,
    LearnOpenGLLighting
};

unsigned int activeScene = LearnOpenGLLighting;

int main()
{
    // Bodged scene loading to allow me to store all parts of the OpenGL tutorial in here

    // Initiate window and camera
    GL::Init(activeScene);
    // Initiate renderer
    Renderer::Init(activeScene);

    // render loop
    while (!glfwWindowShouldClose(GL::window))
    {
        // Calculate deltaTime
        float currentFrame = glfwGetTime();
        Utils::deltaTime = currentFrame - Utils::lastFrameTime;
        Utils::lastFrameTime = currentFrame;
        
        // Check input
        Input::CheckKeys();

        // Set background colour
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Render active scene
        if (activeScene == LearnOpenGLGettingStarted) {
            glm::vec3 cubePositions[] = {
                glm::vec3(0.0f,  0.0f,  0.0f),
                glm::vec3(2.0f,  5.0f, -15.0f),
                glm::vec3(-1.5f, -2.2f, -2.5f),
                glm::vec3(-3.8f, -2.0f, -12.3f),
                glm::vec3(2.4f, -0.4f, -3.5f),
                glm::vec3(-1.7f,  3.0f, -7.5f),
                glm::vec3(1.3f, -2.0f, -2.5f),
                glm::vec3(1.5f,  2.0f, -2.5f),
                glm::vec3(1.5f,  0.2f, -1.5f),
                glm::vec3(-1.3f,  1.0f, -1.5f)
            };

            // bind textures on corresponding texture units
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, Renderer::texture1gettingstarted);
            glActiveTexture(GL_TEXTURE1);
            glBindTexture(GL_TEXTURE_2D, Renderer::texture2gettingstarted);

            // Define what shader to use
            Shaders::OpenGLGettingStartedShader.use();

            // Perspective projection matrix
            glm::mat4 projection = GL::camera.GetProjection();
            Shaders::OpenGLGettingStartedShader.setMat4("projection", projection);

            // create view matrix
            glm::mat4 view = GL::camera.GetViewMatrix();
            Shaders::OpenGLGettingStartedShader.setMat4("view", view);

            // with the uniform matrix set, draw the model
            glBindVertexArray(Renderer::VAOgettingstarted);
            for (unsigned int i = 0; i < 10; i++)
            {
                glm::mat4 model = glm::mat4(1.0f);
                model = glm::translate(model, cubePositions[i]);

                float angle = 20.0f * i;
                model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
                Shaders::OpenGLGettingStartedShader.setMat4("model", model);

                glDrawArrays(GL_TRIANGLES, 0, 36);
            }
        }
        else if (activeScene == LearnOpenGLLighting) {
            // define light position vector
            glm::vec3 lightPos(1.2f, 1.0f, 2.0f);
            // Define active shader as the light source shader
            Shaders::OpenGLLightingLightShader.use();
            // Perspective projection matrix
            glm::mat4 projection = GL::camera.GetProjection();
            Shaders::OpenGLLightingLightShader.setMat4("projection", projection);
            // define view matrix
            glm::mat4 view = GL::camera.GetViewMatrix();
            Shaders::OpenGLLightingLightShader.setMat4("view", view);
            // Translate the light source cube to the light source's position and scale it down before rendering
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, lightPos);
            model = glm::scale(model, glm::vec3(0.2f));
            Shaders::OpenGLLightingLightShader.setMat4("model", model);

            // Bind VAO and render
            glBindVertexArray(Renderer::lightVAOlighting);
            glDrawArrays(GL_TRIANGLES, 0, 36);

            // Define active shader as the cube shader
            Shaders::OpenGLLightingCubeShader.use();
            // Perspective projection matrix
            projection = GL::camera.GetProjection();
            Shaders::OpenGLLightingCubeShader.setMat4("projection", projection);
            // create view matrix
            view = GL::camera.GetViewMatrix();
            Shaders::OpenGLLightingCubeShader.setMat4("view", view);
            // Set cubes position
            model = glm::mat4(1.0f);
            Shaders::OpenGLLightingCubeShader.setMat4("model", model);

            // Bind VAO and render
            glBindVertexArray(Renderer::cubeVAOlighting);
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        glfwSwapBuffers(GL::window);
        glfwPollEvents();
    }

    Renderer::Deallocate(activeScene);

    // glfw: terminate, clearing all previously allocated GLFW resources.
    glfwTerminate();
    return 0;
}