#include "globalThings.h"


bool g_StartUp(GLFWwindow* pWindow)
{
	::g_pShaderLoader = new cShaderLoader();

	::g_pFlyCamera = new cFlyCamera();
		
	::g_pShaderManager = new cShaderManager();

	::g_pTheLights = new cLightManager();

	::g_pTextureManager = new cBasicTextureManager();

	::g_pVAOManager = new cVAOManager();

	::g_pSceneManager = new cSceneManager(::g_pTheLights, ::g_pVAOManager, ::g_pTextureManager);

	return true;
}
