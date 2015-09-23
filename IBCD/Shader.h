#pragma once
#include "easylogging++.h"

#include <fstream>
#include <filesystem>
#include <iostream>
#include <vector>


#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include "ibcdexcept.h"

class Shader
{
public:
	static GLuint LoadShaderFromFile(const char*path);


};
