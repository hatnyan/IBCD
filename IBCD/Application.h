#pragma once

#include <memory>
#include <vector>

struct GLFWwindow;
struct GLFWmonitor;
class Scene;
class Window;

class Application
{
public:
	static Application& getInstance();

	void preInitializeApplication();
	void postInitializeApplication();
	void terminateApplication();
	void addScene(Scene* scene);
	void runLoop();

	static void errorCallback(int error, const char* description);
	static void windowPosCallback(GLFWwindow* window, int x, int y);
	static void windowSizeCallback(GLFWwindow* window, int width, int height);
	static void frameBufferSizeCallback(GLFWwindow* window, int width, int height);
	static void windowCloseCallback(GLFWwindow* window);
	static void windowRefreshCallback(GLFWwindow* window);
	static void windowFocusCallback(GLFWwindow* window, int focused);
	static void windowIconifyCallback(GLFWwindow* window, int iconified);
	static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
	static void cursorPositionCallback(GLFWwindow* window, double x, double y);
	static void cursorEnterCallback(GLFWwindow* window, int entered);
	static void scrollCallback(GLFWwindow* window, double x, double y);
	static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void charCallback(GLFWwindow* window, unsigned int codepoint);
	static void charModsCallback(GLFWwindow* window, unsigned int codepoint, int mods);
	static void dropCallback(GLFWwindow* window, int count, const char** paths);
	static void monitorCallback(GLFWmonitor* monitor, int event);


	
private:
	Application();

private:
	std::vector<Scene*> scenes;
	bool running;
};

extern Application& g_App;
