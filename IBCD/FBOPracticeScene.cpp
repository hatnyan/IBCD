

#include "FBOPracticeScene.h"

#define DIVIDE 1

FBOPracticeScene::FBOPracticeScene(int width, int height, const char * title) :
	Scene(width, height, title)
{
	this->width = width;
	this->height = height;
}

void FBOPracticeScene::mouseButtonCallback(int button, int action, int mods)
{
	double x, y;
	glfwGetCursorPos(window, &x, &y);
	camera.SetPos(button, action, x, y);
}

void FBOPracticeScene::cursorPositionCallback(double x, double y)
{
	camera.Move2D(x, y);
}

void FBOPracticeScene::keyCallback(int key, int scancode, int action, int mods)
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

void FBOPracticeScene::initializeScene()
{
	ADSShader = Shader::LoadShaderFromFile("shader/ADS");
	models.push_back(std::unique_ptr<Model>{new Model{ "models/", "armadillo.model" }});
	models.push_back(std::unique_ptr<Model>{new Model{ "models/", "teapot.model" }});
	models[0]->setPosition(glm::vec3{ 3,0,0 });

	/******************************************************************************/
	quadShader = Shader::LoadShaderFromFile("shader/quad");
	
	glGenVertexArrays(1, &quadVAO);
	glBindVertexArray(quadVAO);
	glGenBuffers(1, &quadVBO);
	glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
	static const GLfloat quad_data[] =
	{
		-1,-1,
		1,-1,
		1,1,
		-1,1,
		0,0,
		1,0,
		1,1,
		0,1
	};
	glBufferData(GL_ARRAY_BUFFER, sizeof(quad_data), quad_data, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 2, GL_FLOAT, false, 0, 0);
	glVertexAttribPointer(1, 2, GL_FLOAT, false, 0, (const void*)(sizeof(float) * 8));
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	/******************************************************************************/

	light.eyecoords = glm::vec3{ 0,3,0 };
	light.La = glm::vec3{ 0.5,0.5,0.5 };
	light.Ld = glm::vec3{ 0.8,0.8,0.8 };
	light.Ls = glm::vec3{ 0.7,0.8,0.7 };

	camera.SetClipping(0.1, 100);
	camera.SetPosition(glm::vec3{ 0,0,5 });
	camera.SetViewport(0, 0, width, height);

	glClearColor(119 / 255.0, 136 / 255.0, 153 / 255.0, 1);
	glClearDepth(1);

	glGenFramebuffers(1, &FrameBuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, FrameBuffer);
	glGenTextures(1, &depthTexture);
	glBindTexture(GL_TEXTURE_2D, depthTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT24, width / DIVIDE, height / DIVIDE, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
	/*glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);*/
	
	glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, depthTexture, 0);
	glDrawBuffer(GL_NONE);

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		throw std::runtime_error("Framebuffer status");
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void FBOPracticeScene::process(double t)
{
	camera.Update();
}

void FBOPracticeScene::render()
{
	glfwMakeContextCurrent(window);


	glEnable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);
	glEnable(GL_STENCIL_TEST);

	glUseProgram(ADSShader);

	glUniform3fv(0, 1, glm::value_ptr(light.eyecoords));
	glUniform3fv(1, 1, glm::value_ptr(light.La));
	glUniform3fv(2, 1, glm::value_ptr(light.Ld));
	glUniform3fv(3, 1, glm::value_ptr(light.Ls));

	glBindFramebuffer(GL_FRAMEBUFFER, FrameBuffer);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	glViewport(0, 0, width / DIVIDE, height / DIVIDE);
	models[0]->render(ADSShader, camera);
	models[1]->render(ADSShader, camera);
	glViewport(0, 0, width, height);
	
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	glBindVertexArray(quadVAO);
	glUseProgram(quadShader);
	
	glBindTexture(GL_TEXTURE_2D, depthTexture);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

	glfwSwapBuffers(window);
}
