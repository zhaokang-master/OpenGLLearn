#pragma once
// learn_3_math.h

#pragma once

#include <glm/glm.hpp>

class learn_3_math
{
public:
    // timing
    static float deltaTime;
    static float lastFrame;
    static float factor;
    static glm::vec3 cameraPos;
    static glm::vec3 cameraFront;
    static glm::vec3 cameraUp;
    static bool firstMouse;
    static float yaw;
    static float pitch;
    static float lastX;
    static float lastY;
    static float fov;

    static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
    static void mouse_callback(GLFWwindow* window, double xposIn, double yposIn);
    int execute();

private:
    void processInput(GLFWwindow* window);
    void framebuffer_size_callback(GLFWwindow* window, int width, int height);
};