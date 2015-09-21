#include "easylogging++.h"

INITIALIZE_EASYLOGGINGPP

#include <stdexcept>

#include <GL\glew.h>
#include <GL\wglew.h>
#include <GLFW\glfw3.h>
#include <glm\glm.hpp>
#include <tiny_obj_loader.h>


#include "Scene.h"

#include "Application.h"

Application& g_App = Application::getInstance();

Application::Application()
{

}

Application & Application::getInstance()
{
	static Application app;
	return app;
}

void Application::preInitializeApplication()
{
	glfwSetErrorCallback(errorCallback);
	if (!glfwInit())
		throw std::runtime_error("glfwInit failed.");

	glfwSetMonitorCallback(monitorCallback);

}

void Application::postInitializeApplication()
{
	GLenum error = glewInit();
	if (GLEW_OK != error)
	{
		throw std::runtime_error("glewInit failed.");
	}
	for (int i = 0; i < scenes.size(); i++) {
		scenes[i]->initializeScene();
	}
}

void Application::terminateApplication()
{
	for (int i = 0; i < scenes.size(); i++) {
		delete scenes[i];
	}
	glfwTerminate();
}

void Application::addScene(Scene * scene)
{
	scenes.push_back(scene);

	glfwSetWindowPosCallback(scene->window, windowPosCallback);
	glfwSetWindowSizeCallback(scene->window, windowSizeCallback);
	glfwSetFramebufferSizeCallback(scene->window, frameBufferSizeCallback);
	glfwSetWindowCloseCallback(scene->window, windowCloseCallback);
	glfwSetWindowRefreshCallback(scene->window, windowRefreshCallback);
	glfwSetWindowFocusCallback(scene->window, windowFocusCallback);
	glfwSetWindowIconifyCallback(scene->window, windowIconifyCallback);
	glfwSetMouseButtonCallback(scene->window, mouseButtonCallback);
	glfwSetCursorPosCallback(scene->window, cursorPositionCallback);
	glfwSetCursorEnterCallback(scene->window, cursorEnterCallback);
	glfwSetScrollCallback(scene->window, scrollCallback);
	glfwSetKeyCallback(scene->window, keyCallback);
	glfwSetCharCallback(scene->window, charCallback);
	glfwSetCharModsCallback(scene->window, charModsCallback);
	glfwSetDropCallback(scene->window, dropCallback);

}

void Application::runLoop()
{
	double current;
	running = true;
	while (running) {
		current = glfwGetTime();
		for (int i = 0; i < scenes.size(); i++)
		{
			scenes[i]->process(current);
			scenes[i]->render();
			if (glfwWindowShouldClose(scenes[i]->window))
				running = false;
		}
		glfwPollEvents();
	}
}


void Application::errorCallback(int error, const char * description)
{

}

void Application::windowPosCallback(GLFWwindow * window, int x, int y)
{
	Scene* s = (Scene*)glfwGetWindowUserPointer(window);
	s->windowPosCallback(x, y);
}

void Application::windowSizeCallback(GLFWwindow * window, int width, int height)
{
	Scene* s = (Scene*)glfwGetWindowUserPointer(window);
	s->windowSizeCallback(width, height);
}

void Application::frameBufferSizeCallback(GLFWwindow * window, int width, int height)
{
	Scene* s = (Scene*)glfwGetWindowUserPointer(window);
	s->frameBufferSizeCallback(width, height);
}

void Application::windowCloseCallback(GLFWwindow * window)
{
	Scene* s = (Scene*)glfwGetWindowUserPointer(window);
	s->windowCloseCallback();
}

void Application::windowRefreshCallback(GLFWwindow * window)
{
	Scene* s = (Scene*)glfwGetWindowUserPointer(window);
	s->windowRefreshCallback();
}

void Application::windowFocusCallback(GLFWwindow * window, int focused)
{
	Scene* s = (Scene*)glfwGetWindowUserPointer(window);
	s->windowFocusCallback(focused);
}

void Application::windowIconifyCallback(GLFWwindow * window, int iconified)
{
	Scene* s = (Scene*)glfwGetWindowUserPointer(window);
	s->windowIconifyCallback(iconified);
}

void Application::mouseButtonCallback(GLFWwindow * window, int button, int action, int mods)
{
	Scene* s = (Scene*)glfwGetWindowUserPointer(window);
	s->mouseButtonCallback(button, action, mods);
}

void Application::cursorPositionCallback(GLFWwindow * window, double x, double y)
{
	Scene* s = (Scene*)glfwGetWindowUserPointer(window);
	s->cursorPositionCallback(x, y);
}

void Application::cursorEnterCallback(GLFWwindow * window, int entered)
{
	Scene* s = (Scene*)glfwGetWindowUserPointer(window);
	s->cursorEnterCallback(entered);
}

void Application::scrollCallback(GLFWwindow * window, double x, double y)
{
	Scene* s = (Scene*)glfwGetWindowUserPointer(window);
	s->scrollCallback(x, y);
}

void Application::keyCallback(GLFWwindow * window, int key, int scancode, int action, int mods)
{
	Scene* s = (Scene*)glfwGetWindowUserPointer(window);
	s->keyCallback(key, scancode, action, mods);
}

void Application::charCallback(GLFWwindow * window, unsigned int codepoint)
{
	Scene* s = (Scene*)glfwGetWindowUserPointer(window);
	s->charCallback(codepoint);
}

void Application::charModsCallback(GLFWwindow * window, unsigned int codepoint, int mods)
{
	Scene* s = (Scene*)glfwGetWindowUserPointer(window);
	s->charModsCallback(codepoint, mods);
}

void Application::dropCallback(GLFWwindow * window, int count, const char ** paths)
{
	Scene* s = (Scene*)glfwGetWindowUserPointer(window);
	s->dropCallback(count, paths);
}

void Application::monitorCallback(GLFWmonitor * monitor, int event)
{
}
