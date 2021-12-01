#pragma once

#include <vector>
#include "cModel.h"
#include <glad/glad.h>
#include "cVAOManager.h"
#include "TextureMapping/cBasicTextureManager.h"

//Loads all 3D models that will be presented on the scene
class cModelCatalog
{
private:
	std::vector<cModel*> models;
public:
	//Load scene models configuration and source files
	void LoadModels(GLuint& program, cVAOManager* gVAOManager, cBasicTextureManager* gTextureManager);
	//Returns the model list that will be rendered
	std::vector<cModel*> GetModels();
};