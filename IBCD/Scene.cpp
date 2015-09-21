#include <stdexcept>

#include <GLFW\glfw3.h>


#include "Scene.h"

Scene::Scene(int width, int height, const char * title)
{
	window = glfwCreateWindow(width, height, title, nullptr, nullptr);
	if (!window)
		throw std::runtime_error("Window Creation failed.");
	glfwSetWindowUserPointer(window, this);

	glfwMakeContextCurrent(window);
	glfwSwapInterval(1); //vsync
}

Scene::~Scene()
{
	glfwDestroyWindow(window);
}

void Scene::windowPosCallback(int x, int y)
{
	
}

void Scene::windowSizeCallback(int width, int height)
{
}

void Scene::frameBufferSizeCallback(int width, int height)
{
}

void Scene::windowCloseCallback()
{
}

void Scene::windowRefreshCallback()
{
}

void Scene::windowFocusCallback(int focused)
{
}

void Scene::windowIconifyCallback(int iconified)
{
}

void Scene::mouseButtonCallback(int button, int action, int mods)
{
}

void Scene::cursorPositionCallback(double x, double y)
{
}

void Scene::cursorEnterCallback(int entered)
{
}

void Scene::scrollCallback(double x, double y)
{
}

void Scene::keyCallback(int key, int scancode, int action, int mods)
{
}

void Scene::charCallback(unsigned int codepoint)
{
}

void Scene::charModsCallback(unsigned int codepoint, int mods)
{
}

void Scene::dropCallback(int count, const char ** paths)
{
}


