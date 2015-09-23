#pragma once

#include "easylogging++.h"

#include <string>
#include <vector>

#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <tiny_obj_loader.h>
#include <glm\glm.hpp>

#include "Camera.h"

class Model
{
public:
	Model(std::string basePath, std::string name);

	void setPosition(glm::vec3 p);
	void setMaterial(tinyobj::material_t material);

	void render(GLuint program, Camera& cam);
	
private:
	tinyobj::mesh_t  mesh;
	tinyobj::material_t material;

	GLuint VAO, VBO, EBO;

	glm::vec3 position;
	glm::quat rotation;
	glm::mat4 modelMatrix;
	glm::mat4 MV;
	glm::mat3 normalMatrix;
	glm::mat4 MVP;
};
