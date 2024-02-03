#include "Shaders.h"
#include "Shader.h"

#include "Utils.h"
#include "Input.h"
#include "Renderer.h"
#include "GL.h"

int main()
{
    // set up vertex data (and buffer(s)) and configure vertex attributes
    //float vertices[] = {
    //    // positions           // texture coords
    //     0.5f,  0.5f, 0.0f,    1.0f, 1.0f, // top right
    //     0.5f, -0.5f, 0.0f,    1.0f, 0.0f, // bottom right
    //    -0.5f, -0.5f, 0.0f,    0.0f, 0.0f, // bottom left
    //    -0.5f,  0.5f, 0.0f,    0.0f, 1.0f  // top left 
    //};
    //unsigned int indices[] = {
    //    0, 1, 3, // first triangle
    //    1, 2, 3  // second triangle
    //};

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

    GL::Init();
    Renderer::Init();

    // Orthographic camera
    //glm::mat4 projection = glm::ortho(0.0f, 800.0f, 0.0f, 600.0f, 0.1f, 100.0f);

    // render loop
    while (!glfwWindowShouldClose(GL::window))
    {
        // Calculate deltaTime
        float currentFrame = glfwGetTime();
        Utils::deltaTime = currentFrame - Utils::lastFrameTime;
        Utils::lastFrameTime = currentFrame;
        
        Input::CheckKeys();

        // render
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // bind textures on corresponding texture units
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, Renderer::texture1);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, Renderer::texture2);

        // Define what shader to use
        Shaders::MainShader.use();

        // Perspective projection matrix
        glm::mat4 projection = GL::camera.GetProjection();
        Shaders::MainShader.setMat4("projection", projection);

        // create view matrix
        glm::mat4 view = GL::camera.GetViewMatrix();
        Shaders::MainShader.setMat4("view", view);

        // with the uniform matrix set, draw the model
        glBindVertexArray(Renderer::VAO);
        for (unsigned int i = 0; i < 10; i++)
        {
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, cubePositions[i]);

            float angle = 20.0f * i;
            model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
            Shaders::MainShader.setMat4("model", model);

            glDrawArrays(GL_TRIANGLES, 0, 36);
        }

        //glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        glfwSwapBuffers(GL::window);
        glfwPollEvents();
    }

    Renderer::Deallocate();

    // glfw: terminate, clearing all previously allocated GLFW resources.
    glfwTerminate();
    return 0;
}