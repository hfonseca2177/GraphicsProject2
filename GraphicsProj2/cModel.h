#pragma once
#include<string>
#include <glad/glad.h>

#include "cVAOManager.h"
#include "cMesh.h"

//Struct for configuration options for the given model
struct sModelConfig
{
	std::string name;
	std::string sourceFile;
	float positionX;
	float positionY;
	float positionZ;
	float scale;
	float radians;
	float red;
	float green;
	float blue;
	bool overrideColor;
	bool enabled;
	std::string lairLabel;
	bool lootable;

};
//Abstracts all 3D Model operations needed to represent it on the scene
class cModel
{
private :
	std::string name;
	sModelDrawInfo drawInfo;
	cMesh* mesh;
	std::string lairLabel;
	bool lootable;
	bool looted;
public:
	//Load Model configuration and  file source
	void load(sModelConfig config, GLuint& program, cVAOManager& gVAOManager);
	//Return the name of the model
	std::string GetName();
	//Returns the mesh properties
	cMesh* GetMesh();
	//returns the VAO Draw information
	sModelDrawInfo GetDrawInfo();
	//Returns the model matrix transformation
	glm::mat4 GetModelTransformation();
	//Verifies if the model is lootable therefore interactable with the game
	bool IsLootable();
	//Return the lair label to be presented
	std::string GetLairLabel();
	//Change the lootable visual flag
	void SetLooted(bool _looted);

};