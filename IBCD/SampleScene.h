#pragma once

#include <GL\glew.h>
#include <glm\glm.hpp>
#include <tiny_obj_loader.h>
#include "Camera.h"
#include "Scene.h"

class SampleScene : public Scene
{
public:
	SampleScene(int width, int height, const char* title);

	virtual void mouseButtonCallback(int button, int action, int mods);
	virtual void cursorPositionCallback(double x, double y);
	virtual void keyCallback(int key, int scancode, int action, int mods);

	virtual void initializeScene();
	virtual void process(double t);
	virtual void render();

private:
	GLuint phongShader;
	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> materials;
	GLuint EBO, VAO, VBO;
	int width, height;
	double time;
	Camera camera;

};
