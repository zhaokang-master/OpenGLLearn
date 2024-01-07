#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Shader.cpp";

class  learn_1_common
{
public:
	int execute()
	{
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
		if (window == NULL)
		{
			std::cout << "Failed to Create GLFW Window" << std::endl;
			glfwTerminate();
			return -1;
		}
		glfwMakeContextCurrent(window);

		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
			std::cout << "Failed to initialize GLAD" << std::endl;
			return -1;
		}
		//开始绘制

		////顶点着色器
		//unsigned int  vertextShader = glCreateShader(GL_VERTEX_SHADER);
		//glShaderSource(vertextShader, 1, &vertextShaderSource, NULL);
		////编译器glsl
		//glCompileShader(vertextShader);

		////检查编译结果
		//int success;
		//char infoLog[512];
		//glGetShaderiv(vertextShader, GL_COMPILE_STATUS, &success);
		//if (!success)
		//{
		//	glGetShaderInfoLog(vertextShader, 512, NULL, infoLog);
		//	std::cout << "Compile vertext Shader Failed" << infoLog << std::endl;
		//}
		////片元着色器
		//unsigned int fragShader = glCreateShader(GL_FRAGMENT_SHADER);
		//glShaderSource(fragShader, 1, &fragmentShaderSource, NULL);
		//glCompileShader(fragShader);
		//glGetShaderiv(fragShader, GL_COMPILE_STATUS, &success);
		//if (!success) {
		//	glGetShaderInfoLog(fragShader, 512, NULL, infoLog);
		//	std::cout << "compile frage shaer failed" << infoLog << std::endl;
		//}

		////创建Shader程序
		//unsigned int shaderProgra = glCreateProgram();
		//glAttachShader(shaderProgra, vertextShader);
		//glAttachShader(shaderProgra, fragShader);
		//glLinkProgram(shaderProgra);

		////linkError
		//glGetProgramiv(shaderProgra, GL_LINK_STATUS, &success);
		//if (!success) {
		//	glGetProgramInfoLog(shaderProgra, 512, NULL, infoLog);
		//	std::cout << "shader program link failed" << infoLog << std::endl;
		//}

		////delete
		//glDeleteShader(vertextShader);
		//glDeleteShader(fragShader);
		Shader myShader = Shader("test1.vs", "test1.fs");
		//数据
		float vertices[] = {
			 0.5f,  0.5f, 0.0f,  // top right
			 0.5f, -0.5f, 0.0f,  // bottom right
			-0.5f, -0.5f, 0.0f,  // bottom left
			-0.5f,  0.5f, 0.0f   // top left 
		};
		unsigned int indices[] = {  // note that we start from 0!
			0, 1, 3,  // first Triangle
			1, 2, 3   // second Triangle
		};
		unsigned int VBO, VAO, EBO;
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &EBO);
		glBindVertexArray(VAO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glBindVertexArray(0);

		/*glViewport(0, 0, 800, 600);
		glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);*/
		//线框模式
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		while (!glfwWindowShouldClose(window))
		{
			processInput(window);
			//glUseProgram(shaderProgra);
			myShader.use();
			float timeValue = glfwGetTime();
			float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
			myShader.SetVec4("outColor", 0.0, greenValue, 0.0, 1.0);
			//可以直接使用VAO了
			glBindVertexArray(VAO);
			//glDrawArrays(GL_TRIANGLES, 0, 3);
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
			glfwSwapBuffers(window);
			glfwPollEvents();
			/*glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);*/
		}

		glDeleteVertexArrays(1, &VAO);
		glDeleteBuffers(1, &VBO);
		//glDeleteProgram(shaderProgra);
		myShader.tryDetele();
		glfwTerminate();

		return 0;
	}

private:
	void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
		glViewport(0, 0, width, height);
	}


	void processInput(GLFWwindow* window) {
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
			glfwSetWindowShouldClose(window, true);
		}
	}
};




