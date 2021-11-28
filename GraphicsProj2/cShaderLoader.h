#pragma once
#include "GLCommon.h"
//Responsible to load shaders used in the scene
class cShaderLoader
{
public:
	//load shader profiles
	void LoadShaders(GLuint& program);
};
