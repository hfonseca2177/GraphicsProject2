#pragma once
#include "GLCommon.h"
//Responsible to load shaders used in the scene
class cShaderLoader
{
private:
	
	cShaderManager* shaderManager;
	//Map all shader variables
	void MapShaderVariables(GLuint& program);
	//Get created shader pointer
	cShaderManager::cShaderProgram* GetLoadedShader();
public:
	//load shader profiles
	void LoadShaders(GLuint& program, cShaderManager* _shaderManager);
	int GetModelLocation();
	int GetViewLocation();
	int GetProjectionLocation();
	int GetModelInverseTransposeLocation();
};
