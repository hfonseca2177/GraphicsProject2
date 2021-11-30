#include "globalThings.h"


bool g_StartUp(GLFWwindow* pWindow)
{

	::g_pFlyCamera = new cFlyCamera();
		
	::g_pShaderManager = new cShaderManager();

	::g_pTheLights = new cLightManager();

	::g_pTextureManager = new cBasicTextureManager();

	::g_pVAOManager = new cVAOManager();

	return true;
}
