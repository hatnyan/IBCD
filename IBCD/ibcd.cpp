#include "ibcd.h"
#include "SampleScene.h"
#include "DepthPeelingScene.h"
#include "FBOPracticeScene.h"

int main()
{
	g_App.preInitializeApplication();
	g_App.addScene(new FBOPracticeScene(800, 600, "DP Scene"));
	g_App.postInitializeApplication();
	
	g_App.runLoop();
	g_App.terminateApplication();

	return 0;
}