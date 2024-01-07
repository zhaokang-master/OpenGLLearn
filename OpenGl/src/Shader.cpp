#ifndef SHADER_H
#define SHADER_H

#include<glad/glad.h>
#include<string>
#include<fstream>
#include<sstream>
#include<iostream>

#include <glm/glm.hpp>;
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shader {
public:
	unsigned int ID;
	Shader(const char* vertextPath, const char* fragementPath) {
		//read
		char path1[256];
		const char* basePath = "../Shader/";
		strcpy(path1, basePath);
		strcat(path1, vertextPath);
		char path2[256];
		strcpy(path2, basePath);
		strcat(path2, fragementPath);
		std::string vertextCode;
		std::string fragementCode;
		std::ifstream vShaderFile;
		std::ifstream fShaderFile;

		vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

		//read
		try
		{
			vShaderFile.open(path1);
			fShaderFile.open(path2);
			std::stringstream vShaderStream, fShaderStream;
			vShaderStream << vShaderFile.rdbuf();
			fShaderStream << fShaderFile.rdbuf();
			vShaderFile.close();
			fShaderFile.close();
			vertextCode = vShaderStream.str();
			fragementCode = fShaderStream.str();

		}
		catch (const std::exception& e)
		{
			std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLT_READ: " << e.what() << std::endl;
		}

		//链接和编译
		const char* vShaderCode = vertextCode.c_str();
		const char* fShaderCode = fragementCode.c_str();
		unsigned int vertext, fragment;
		vertext = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertext, 1, &vShaderCode, NULL);
		glCompileShader(vertext);
		checkCompileError(vertext, "VERTEXT");

		//fragment 
		fragment = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragment, 1, &fShaderCode, NULL);
		glCompileShader(fragment);
		checkCompileError(fragment, "FRAGMENT");

		//创建ShaderProgram
		ID = glCreateProgram();
		glAttachShader(ID, vertext);
		glAttachShader(ID, fragment);
		glLinkProgram(ID);
		checkCompileError(ID, "PROGRAAM");

		//link之后可以删除创建的shader资源
		glDeleteShader(vertext);
		glDeleteShader(fragment);

	}


	void use() {
		glUseProgram(ID);
	}

	void tryDetele() {
		glDeleteProgram(ID);
	}

	//修改uniform的值
	void SetBool(const std::string& name, bool value) {
		glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
	}

	void SetInt(const std::string& name, int value) {
		glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
	}

	void SetFloat(const std::string& name, float value) {
		glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
	}

	void SetVec4(const std::string& name, float x, float y, float z, float w) {
		glUniform4f(glGetUniformLocation(ID, name.c_str()), x, y, z, w);
	}
	void SetVec3(const std::string& name, float x, float y, float z) {
		glUniform3f(glGetUniformLocation(ID, name.c_str()), x, y, z);
	}

	void SetMat4(const std::string& name, glm::mat4 trans) {
		glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, glm::value_ptr(trans));
	}

	void SetMatrixArray(const std::string& name, int index, glm::mat4 trans) {
		GLuint transformLocation = glGetUniformLocation(ID, name.c_str());
		glUniformMatrix4fv(transformLocation + index, 1, GL_FALSE, glm::value_ptr(trans));
	}

private:
	void checkCompileError(unsigned int shader, std::string type) {
		int success;
		char infoLog[1024];
		if (type != "PROGRAM") {
			glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
			if (!success) {
				glGetShaderInfoLog(shader, 1024, NULL, infoLog);
				std::cout << "ERROR:SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n" << std::endl;
			}
		}
		else
		{
			glGetProgramiv(shader, GL_LINK_STATUS, &success);
			if (!success)
			{
				glGetProgramInfoLog(shader, 1024, NULL, infoLog);
				std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
			}
		}
	}

};
#endif