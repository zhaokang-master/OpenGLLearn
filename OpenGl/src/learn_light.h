#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Camera.h"
class  learn_light
{
public:
	static void mouse_callback(GLFWwindow* window, double xposIn, double yposIn);
	int execute();
	void processInput(GLFWwindow* window);
	static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
	static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
	static Camera camera;
	static float deltaTime;
	static float lastX;
	static float lastY;
	static bool firstMouse;
	static float lastFrame;

private:
	

};
