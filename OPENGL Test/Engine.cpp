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

    // render loop
    while (!glfwWindowShouldClose(GL::window))
    {
        // Calculate deltaTime
        float currentFrame = glfwGetTime();
        Utils::deltaTime = currentFrame - Utils::lastFrameTime;
        Utils::lastFrameTime = currentFrame;
        
        // Check input
        Input::CheckKeys();

        // Render active scene
        if (activeScene == LearnOpenGLGettingStarted) {
            // Set background colour
            glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

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
            // positions of the point lights
            glm::vec3 pointLightPositions[] = {
                glm::vec3(0.7f,  0.2f,  2.0f),
                glm::vec3(2.3f, -3.3f, -4.0f),
                glm::vec3(-4.0f,  2.0f, -12.0f),
                glm::vec3(0.0f,  0.0f, -3.0f)
            };

            // define light position vector
            glm::vec3 lightPos(1.2f, 1.0f, 2.0f);

            // Assign values to Cubes shader
            // Define active shader as the cube shader
            Shaders::OpenGLLightingCubeShader.use();
            Shaders::OpenGLLightingCubeShader.setVec3("viewPos", GL::camera.Position);

            //--- Directional Light
            // Define Point Light colour
            glm::vec3 dirLightColour = glm::vec3(1.0f, 1.0f, 1.0f);
            glm::vec3 dirLightIntensity = glm::vec3(0.4f);
            glm::vec3 dirAmbientIntensity = glm::vec3(0.05f);
            glm::vec3 dirDiffuseColour = dirLightColour * dirLightIntensity;
            glm::vec3 dirAmbientColour = dirDiffuseColour * dirAmbientIntensity;

            Shaders::OpenGLLightingCubeShader.setVec3("dirLight.direction", -0.2f, -1.0f, -0.3f);
            Shaders::OpenGLLightingCubeShader.setVec3("dirLight.ambient", dirAmbientColour);
            Shaders::OpenGLLightingCubeShader.setVec3("dirLight.diffuse", dirDiffuseColour);
            Shaders::OpenGLLightingCubeShader.setVec3("dirLight.specular", 0.5f, 0.5f, 0.5f);
            // Directional Light is global and has no drop off distance, like the sun

            //--- Point Lights
            // Define Point Light colour
            glm::vec3 lightColour = glm::vec3(1.0f, 1.0f, 1.0f);
            glm::vec3 lightIntensity = glm::vec3(0.5f);
            glm::vec3 ambientIntensity = glm::vec3(0.2f);
            glm::vec3 diffuseColour = lightColour * lightIntensity;
            glm::vec3 ambientColour = diffuseColour * ambientIntensity;

            // Point Light 1
            Shaders::OpenGLLightingCubeShader.setVec3("pointLights[0].position", pointLightPositions[0]);
            Shaders::OpenGLLightingCubeShader.setVec3("pointLights[0].ambient", ambientColour);
            Shaders::OpenGLLightingCubeShader.setVec3("pointLights[0].diffuse", diffuseColour);
            Shaders::OpenGLLightingCubeShader.setVec3("pointLights[0].specular", 1.0f, 1.0f, 1.0f);
            //Light attenuation (drop off distance)
            Shaders::OpenGLLightingCubeShader.setFloat("pointLights[0].constant", 1.0f);
            Shaders::OpenGLLightingCubeShader.setFloat("pointLights[0].linear", 0.09f);
            Shaders::OpenGLLightingCubeShader.setFloat("pointLights[0].quadratic", 0.032f);
            // Point Light 2
            Shaders::OpenGLLightingCubeShader.setVec3("pointLights[1].position", pointLightPositions[1]);
            Shaders::OpenGLLightingCubeShader.setVec3("pointLights[1].ambient", ambientColour);
            Shaders::OpenGLLightingCubeShader.setVec3("pointLights[1].diffuse", diffuseColour);
            Shaders::OpenGLLightingCubeShader.setVec3("pointLights[1].specular", 1.0f, 1.0f, 1.0f);
            //Light attenuation (drop off distance)
            Shaders::OpenGLLightingCubeShader.setFloat("pointLights[1].constant", 1.0f);
            Shaders::OpenGLLightingCubeShader.setFloat("pointLights[1].linear", 0.09f);
            Shaders::OpenGLLightingCubeShader.setFloat("pointLights[1].quadratic", 0.032f);
            // Point Light 3
            Shaders::OpenGLLightingCubeShader.setVec3("pointLights[2].position", pointLightPositions[2]);
            Shaders::OpenGLLightingCubeShader.setVec3("pointLights[2].ambient", ambientColour);
            Shaders::OpenGLLightingCubeShader.setVec3("pointLights[2].diffuse", diffuseColour);
            Shaders::OpenGLLightingCubeShader.setVec3("pointLights[2].specular", 1.0f, 1.0f, 1.0f);
            //Light attenuation (drop off distance)
            Shaders::OpenGLLightingCubeShader.setFloat("pointLights[2].constant", 1.0f);
            Shaders::OpenGLLightingCubeShader.setFloat("pointLights[2].linear", 0.09f);
            Shaders::OpenGLLightingCubeShader.setFloat("pointLights[2].quadratic", 0.032f);
            // Point Light 4
            Shaders::OpenGLLightingCubeShader.setVec3("pointLights[3].position", pointLightPositions[3]);
            Shaders::OpenGLLightingCubeShader.setVec3("pointLights[3].ambient", ambientColour);
            Shaders::OpenGLLightingCubeShader.setVec3("pointLights[3].diffuse", diffuseColour);
            Shaders::OpenGLLightingCubeShader.setVec3("pointLights[3].specular", 1.0f, 1.0f, 1.0f);
            //Light attenuation (drop off distance)
            Shaders::OpenGLLightingCubeShader.setFloat("pointLights[3].constant", 1.0f);
            Shaders::OpenGLLightingCubeShader.setFloat("pointLights[3].linear", 0.09f);
            Shaders::OpenGLLightingCubeShader.setFloat("pointLights[3].quadratic", 0.032f);

            //--- SpotLight (Torch)
            Shaders::OpenGLLightingCubeShader.setVec3("spotLight.position", GL::camera.Position);
            Shaders::OpenGLLightingCubeShader.setVec3("spotLight.direction", GL::camera.Front);
            Shaders::OpenGLLightingCubeShader.setVec3("spotLight.ambient", 0.0f, 0.0f, 0.0f);
            Shaders::OpenGLLightingCubeShader.setVec3("spotLight.diffuse", 1.0f, 1.0f, 1.0f);
            Shaders::OpenGLLightingCubeShader.setVec3("spotLight.specular", 1.0f, 1.0f, 1.0f);
            //Light attenuation (drop off distance)
            Shaders::OpenGLLightingCubeShader.setFloat("spotLight.constant", 1.0f);
            Shaders::OpenGLLightingCubeShader.setFloat("spotLight.linear", 0.09f);
            Shaders::OpenGLLightingCubeShader.setFloat("spotLight.quadratic", 0.032f);
            //Radius of spotlight
            Shaders::OpenGLLightingCubeShader.setFloat("spotLight.cutOff", glm::cos(glm::radians(12.5f)));
            Shaders::OpenGLLightingCubeShader.setFloat("spotLight.outerCutOff", glm::cos(glm::radians(15.0f)));

            // Set background colour
            glClearColor(dirDiffuseColour.r, dirDiffuseColour.g, dirDiffuseColour.b, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            // bind textures on corresponding texture units
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, Renderer::texture1lighting);
            glActiveTexture(GL_TEXTURE1);
            glBindTexture(GL_TEXTURE_2D, Renderer::texture2lighting);

            // Define the Cube values in shader
            // Assign texture unit 0 to diffuse
            Shaders::OpenGLLightingCubeShader.setInt("material.diffuse", 0);
            Shaders::OpenGLLightingCubeShader.setInt("material.specular", 1);
            Shaders::OpenGLLightingCubeShader.setFloat("material.shininess", 32.0f);

            // Perspective projection matrix
            glm::mat4 projection = GL::camera.GetProjection();
            // define view matrix
            glm::mat4 view = GL::camera.GetViewMatrix();

            // Define active shader as the Light source shader
            Shaders::OpenGLLightingLightShader.use();
            // Set the FragColor of our Cube Light to match the light it is outputting
            Shaders::OpenGLLightingLightShader.setVec3("lightColour", lightColour);
            Shaders::OpenGLLightingLightShader.setMat4("projection", projection);
            Shaders::OpenGLLightingLightShader.setMat4("view", view);

            // Bind Light Cube VAO
            glBindVertexArray(Renderer::lightVAOlighting);
            // Draw Light Cubes in pointLightPositions position
            glm::mat4 model = glm::mat4(1.0f);
            for (unsigned int i = 0; i < 4; i++)
            {
                model = glm::mat4(1.0f);
                model = glm::translate(model, pointLightPositions[i]);
                model = glm::scale(model, glm::vec3(0.2f)); // Make it a smaller cube
                Shaders::OpenGLLightingLightShader.setMat4("model", model);
                // Render
                glDrawArrays(GL_TRIANGLES, 0, 36);
            }
            Shaders::OpenGLLightingLightShader.setMat4("model", model);

            // Define active shader as the cube shader
            Shaders::OpenGLLightingCubeShader.use();
            Shaders::OpenGLLightingCubeShader.setMat4("projection", projection);
            Shaders::OpenGLLightingCubeShader.setMat4("view", view);

            // Bind Cube VAO
            glBindVertexArray(Renderer::cubeVAOlighting);
            // Set cubes positions
            for (unsigned int i = 0; i < 10; i++)
            {
                model = glm::mat4(1.0f);
                model = glm::translate(model, cubePositions[i]);
                float angle = 20.0f * i;
                model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
                Shaders::OpenGLLightingCubeShader.setMat4("model", model);

                // Render Cubes
                glDrawArrays(GL_TRIANGLES, 0, 36);
            }
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