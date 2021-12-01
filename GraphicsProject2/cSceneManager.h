#pragma once
#include "cLightManager.h"
#include "cModelCatalog.h"
#include "cVAOManager.h"
#include "TextureMapping/cBasicTextureManager.h"

class cSceneManager
{
private:
	cLightManager* lightManager;
	cVAOManager* VAOManager;
	cBasicTextureManager* textureManager;
	cModelCatalog* modelCatalog;
public:
	cSceneManager(cLightManager* _lightManager, cVAOManager* _VAOManager, cBasicTextureManager* _textureManager);
	virtual ~cSceneManager();
	void LoadSceneModels(GLuint& program);
	void SetupLights();
	std::vector<cModel*> GetModels();

};