#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Shader.cpp";

//#include "learn_1_common.cpp"
//#include "learn_2_texture.cpp"
#include "learn_light.h"

int main(int argc, char** argv)
{
	learn_light second = learn_light();
	second.execute();
	
	return 0;
}

