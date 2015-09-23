

#include "DepthPeelingScene.h"

DPScene::DPScene(int width, int height, const char * title):
	Scene(width, height, title)
{
	this->width = width;
	this->height = height;
}

void DPScene::mouseButtonCallback(int button, int action, int mods)
{
	double x, y;
	glfwGetCursorPos(window, &x, &y);
	camera.SetPos(button, action, x, y);
}

void DPScene::cursorPositionCallback(double x, double y)
{
	camera.Move2D(x, y);
}

void DPScene::keyCallback(int key, int scancode, int action, int mods)
{
	switch (key)
	{
	case GLFW_KEY_W:
		camera.Move(FORWARD);
		break;
	case GLFW_KEY_A:
		camera.Move(LEFT);
		break;
	case GLFW_KEY_S:
		camera.Move(BACK);
		break;
	case GLFW_KEY_D:
		camera.Move(RIGHT);
		break;
	case GLFW_KEY_LEFT_CONTROL:
		camera.Move(DOWN);
		break;
	case GLFW_KEY_SPACE:
		camera.Move(UP);
		break;
	}
}

void DPScene::initializeScene()
{
	ADSShader = Shader::LoadShaderFromFile("shader/ADS");
	models.push_back(std::unique_ptr<Model>{new Model{ "models/", "armadillo.model" }});
	models.push_back(std::unique_ptr<Model>{new Model{ "models/", "teapot.model" }});
	models[0]->setPosition(glm::vec3{ 3,0,0 });

	light.eyecoords = glm::vec4{ 0,3,0,1 };
	light.La = glm::vec3{ 0.2,0.2,0.2 };
	light.Ld = glm::vec3{ 0.8,0.8,0.8 };
	light.Ls = glm::vec3{ 0.7,0.8,0.7 };

	camera.SetClipping(0.1, 100);
	camera.SetPosition(glm::vec3{ 0,0,5 });
	camera.SetViewport(0, 0, width, height);

	glClearColor(119 / 255.0, 136 / 255.0, 153 / 255.0, 1);
}

void DPScene::process(double t)
{
	camera.Update();
}

void DPScene::render()
{
	glfwMakeContextCurrent(window);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	glUseProgram(ADSShader);

	glUniform4fv(0, 1, glm::value_ptr(light.eyecoords));
	glUniform3fv(1, 1, glm::value_ptr(light.La)); 
	glUniform3fv(2, 1, glm::value_ptr(light.Ld));
	glUniform3fv(3, 1, glm::value_ptr(light.Ls));



	for (int i = 0; i < models.size(); i++)
		models[i]->render(ADSShader, camera);

	glfwSwapBuffers(window);
}
