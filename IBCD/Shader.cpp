#include "easylogging++.h"

#include <fstream>
#include <filesystem>
#include <iostream>
#include <vector>


#include <GL\glew.h>
#include "ibcdexcept.h"
#include "Shader.h"

using namespace std::tr2::sys;

GLuint Shader::LoadShaderFromFile(const char * pathname)
{
	GLuint vShader, fShader, gShader;
	
	path p = pathname;
	path vertPath = p;
	vertPath += ".vert";
	vertPath = absolute(vertPath);
	
	if (!exists(vertPath)) {
		throw file_not_found(vertPath.string());
	}

	std::ifstream vertFile(vertPath, std::ifstream::binary);
	if (vertFile) {
		vertFile.seekg(0, vertFile.end);
		int length = vertFile.tellg();
		vertFile.seekg(0, vertFile.beg);

		char * buf = new char[length];

		vertFile.read(buf, length);
		if (!vertFile) {
			delete[] buf;
			throw std::runtime_error("file reading error occured.");
		}
		vertFile.close();

		vShader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vShader, 1, &buf, &length);
		delete[] buf;
		glCompileShader(vShader);
		GLint isCompiled = 0;
		glGetShaderiv(vShader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE) {
			GLint maxLength = 0;
			glGetShaderiv(vShader, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(vShader, maxLength, &maxLength, &infoLog[0]);

			glDeleteShader(vShader);
			LOG(INFO) << infoLog.data();

			throw shader_compile_error("vShader compile failed.");
		}

	}

	path fragPath = p;
	fragPath += ".frag";
	fragPath = absolute(fragPath);

	if (!exists(fragPath)) {
		throw file_not_found(fragPath.string());
	}

	std::ifstream fragFile(fragPath, std::ifstream::binary);
	if (fragFile) {
		fragFile.seekg(0, fragFile.end);
		int length = fragFile.tellg();
		fragFile.seekg(0, fragFile.beg);
		char *buf = new char[length];
		fragFile.read(buf, length);
		if (!fragFile) {
			delete[] buf;
			throw std::runtime_error("file reading error occured.");
		}
		fragFile.close();

		fShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fShader, 1, &buf, &length);
		delete[] buf;
		glCompileShader(fShader);
		GLint isCompiled = 0;
		glGetShaderiv(fShader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE) {
			GLint maxLength = 0;
			glGetShaderiv(fShader, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(fShader, maxLength, &maxLength, &infoLog[0]);

			glDeleteShader(fShader);
			LOG(INFO) << infoLog.data();

			throw shader_compile_error("fShader compile failed.");
		}
	}

	// Compilation succeeded.
	GLuint program = glCreateProgram();
	glAttachShader(program, vShader);
	glAttachShader(program, fShader);
	glLinkProgram(program);

	GLint isLinked = 0;
	glGetProgramiv(program, GL_LINK_STATUS, &isLinked);
	if (isLinked == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);
		std::vector<GLchar> infoLog(maxLength);
		glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);
		glDeleteProgram(program);
		glDeleteShader(vShader);
		glDeleteShader(fShader);

		throw shader_compile_error("program linking failed.");

	}

	glDetachShader(program, vShader);
	glDetachShader(program, fShader);
	
	return program;
}


