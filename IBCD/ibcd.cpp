#include "ibcd.h"
#include "SampleScene.h"

int main()
{
	g_App.preInitializeApplication();
	g_App.addScene(new SampleScene(800, 600, "Sample Scene"));
	g_App.postInitializeApplication();
	
	g_App.runLoop();
	g_App.terminateApplication();

	return 0;
}