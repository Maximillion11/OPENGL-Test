#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Utils.h"

#include <iostream>

// Defines several possible options for camera movement. Used as abstraction to stay away from window-system specific input methods
enum Camera_Input {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT,
    UP,
    DOWN
};

// Default camera values
const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = 2.5f;
const float SPRINTMODIFIER = 2.0f;
const float SENSITIVITY = 0.1f;
const float VERTICALFOV = 45.0f;

// Camera limits
const float VERTICALFOV_MIN = 1.0f;
const float VERTICALFOV_MAX = 75.0f;
const float NEARPLANE = 0.01f;
const float FARPLANE = 100.0f;

// An abstract camera class that processes input and calculates the corresponding Euler Angles, Vectors and Matrices for use in OpenGL
class Camera
{
public:
    // camera Attributes
    glm::vec3 Position;
    glm::vec3 Front;
    glm::vec3 Up;
    glm::vec3 Right;
    glm::vec3 WorldUp;

    // euler Angles
    float Yaw;
    float Pitch;

    // camera options
    float MovementSpeed;
    float SprintModifier;
    float MouseSensitivity;
    float VerticalFOV;

    // constructor with vectors
    Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH)
        :
        Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), SprintModifier(SPRINTMODIFIER), MouseSensitivity(SENSITIVITY), VerticalFOV(VERTICALFOV)
    {
        Position = position;
        WorldUp = up;
        Yaw = yaw;
        Pitch = pitch;
        updateCameraVectors();
    }
    // constructor with scalar values
    Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch)
        :
        Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), SprintModifier(SPRINTMODIFIER), MouseSensitivity(SENSITIVITY), VerticalFOV(VERTICALFOV)
    {
        Position = glm::vec3(posX, posY, posZ);
        WorldUp = glm::vec3(upX, upY, upZ);
        Yaw = yaw;
        Pitch = pitch;
        updateCameraVectors();
    }

    // returns the view matrix calculated using Euler Angles and the LookAt Matrix
    glm::mat4 GetViewMatrix()
    {
        return glm::lookAt(Position, Position + Front, Up);
    }

    glm::mat4 GetProjection()
    {
        return glm::perspective(glm::radians(VerticalFOV), (float)Utils::WINDOW_WIDTH / (float)Utils::WINDOW_HEIGHT, NEARPLANE, FARPLANE);
    }

    // processes input received from any keyboard-like input system. Accepts input parameter in the form of camera defined ENUM (to abstract it from windowing systems)
    void ProcessKeyboard(Camera_Input input, bool shiftHeld)
    {
        float velocity = MovementSpeed;

        if (shiftHeld)
            velocity *= SprintModifier;

        velocity *= Utils::deltaTime;

        if (input == FORWARD)
            Position += Front * velocity;
        if (input == BACKWARD)
            Position -= Front * velocity;
        if (input == LEFT)
            Position -= Right * velocity;
        if (input == RIGHT)
            Position += Right * velocity;
        if (input == UP)
            Position += Up * velocity;
        if (input == DOWN)
            Position -= Up * velocity;
    }

    // processes input received from a mouse input system. Expects the offset value in both the x and y direction.
    void ProcessMouseMovement(float xoffset, float yoffset, bool constrainPitch = true)
    {
        xoffset *= MouseSensitivity;
        yoffset *= MouseSensitivity;

        Yaw += xoffset;
        Pitch += yoffset;

        // make sure that when pitch is out of bounds, screen doesn't get flipped
        if (constrainPitch)
        {
            if (Pitch > 89.0f)
                Pitch = 89.0f;
            if (Pitch < -89.0f)
                Pitch = -89.0f;
        }

        // update Front, Right and Up Vectors using the updated Euler angles
        updateCameraVectors();
    }

    // processes input received from a mouse scroll-wheel event. Only requires input on the vertical wheel-axis
    void ProcessMouseScroll(float yoffset)
    {
        VerticalFOV -= (float)yoffset;
        if (VerticalFOV < VERTICALFOV_MIN)
            VerticalFOV = VERTICALFOV_MIN;
        if (VerticalFOV > VERTICALFOV_MAX)
            VerticalFOV = VERTICALFOV_MAX;
    }

private:
    // calculates the front vector from the Camera's (updated) Euler Angles
    void updateCameraVectors()
    {
        // calculate the new Front vector
        glm::vec3 front;
        front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
        front.y = sin(glm::radians(Pitch));
        front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
        Front = glm::normalize(front);
        // also re-calculate the Right and Up vector
        Right = glm::normalize(glm::cross(Front, WorldUp));  // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
        Up = glm::normalize(glm::cross(Right, Front));
    }
};
#endif