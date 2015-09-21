#pragma once

#include "Application.h"

struct GLFWwindow;
struct GLFWmonitor;

class Scene
{
public:
	Scene(int width, int height, const char* title);
	virtual ~Scene();

	virtual void windowPosCallback(int x, int y);
	virtual void windowSizeCallback(int width, int height);
	virtual void frameBufferSizeCallback(int width, int height);
	virtual void windowCloseCallback();
	virtual void windowRefreshCallback();
	virtual void windowFocusCallback(int focused);
	virtual void windowIconifyCallback(int iconified);
	virtual void mouseButtonCallback(int button, int action, int mods);
	virtual void cursorPositionCallback(double x, double y);
	virtual void cursorEnterCallback(int entered);
	virtual void scrollCallback(double x, double y);
	virtual void keyCallback(int key, int scancode, int action, int mods);
	virtual void charCallback(unsigned int codepoint);
	virtual void charModsCallback(unsigned int codepoint, int mods);
	virtual void dropCallback(int count, const char** paths);
	
	virtual void initializeScene() = 0;
	virtual void process(double t) = 0;
	virtual void render() = 0;
	
	GLFWwindow* window;
};