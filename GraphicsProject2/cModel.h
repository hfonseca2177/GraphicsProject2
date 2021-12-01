#pragma once
#include<string>
#include <glad/glad.h>
#include "cVAOManager.h"
#include "cMesh.h"
#include "TextureMapping/cBasicTextureManager.h"

//Struct for configuration options for the given model
struct sModelConfig
{
	std::string name;
	std::string sourceFile;
	std::string textureName;
	float positionX;
	float positionY;
	float positionZ;
	float scale;
	float radians;
	bool enabled;

};
//Abstracts all 3D Model operations needed to represent it on the scene
class cModel
{
private :
	std::string name;
	sModelDrawInfo drawInfo;
	cMesh* mesh;
public:
	//Load Model configuration and  file source
	void load(sModelConfig config, GLuint& program, cVAOManager* gVAOManager, cBasicTextureManager* gTextureManager);
	//Return the name of the model
	std::string GetName();
	//Returns the mesh properties
	cMesh* GetMesh();
	//returns the VAO Draw information
	sModelDrawInfo GetDrawInfo();
	//Returns the model matrix transformation
	glm::mat4 GetModelTransformation();
};