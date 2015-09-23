#pragma once

#include "easylogging++.h"

#include <vector>
#include <memory>

#include <GL\glew.h>
#include <glm\glm.hpp>
#include <tiny_obj_loader.h>

#include "Light.h"
#include "Model.h"
#include "Camera.h"
#include "Scene.h"
#include "Shader.h"

class DPScene : public Scene
{
public:
	DPScene(int width, int height, const char* title);

	virtual void mouseButtonCallback(int button, int action, int mods);
	virtual void cursorPositionCallback(double x, double y);
	virtual void keyCallback(int key, int scancode, int action, int mods);

	virtual void initializeScene();
	virtual void process(double t);
	virtual void render();

private:
	GLuint ADSShader;
	std::vector<std::unique_ptr<Model>> models;
	int width, height;
	double time;
	Camera camera;
	Light light;
};
#pragma once
