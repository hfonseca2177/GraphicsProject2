#include "cSceneManager.h"

cSceneManager::~cSceneManager()
{
	delete modelCatalog;
}

cSceneManager::cSceneManager(cLightManager* _lightManager, cVAOManager* _VAOManager, cBasicTextureManager* _textureManager)
{
	this->VAOManager = _VAOManager;
	this->textureManager = _textureManager;
	this->lightManager = _lightManager;
	this->modelCatalog = new cModelCatalog();
}

void cSceneManager::SetupLights()
{
   this->lightManager->theLights[0].position = glm::vec4(20.0f, -35.0f, 50.0f, 1.0f);
   this->lightManager->theLights[0].diffuse *= 0.001f;
   this->lightManager->theLights[0].param1.x = 2.0f;
   this->lightManager->theLights[0].direction = glm::vec4(20.0f, -15.0f, 380.0f, 1.0f);
   this->lightManager->theLights[0].param1.y = 5.0f;
   this->lightManager->theLights[0].param1.z = 5.0f;
   this->lightManager->theLights[0].atten.y = 0.0001f;
   this->lightManager->theLights[0].atten.z = 0.00001f;
   this->lightManager->theLights[0].param2.x = 1.0f;

   this->lightManager->theLights[1].position = glm::vec4(0.0f, 45.0f, 0.0f, 1.f);
   this->lightManager->theLights[1].diffuse = glm::vec4(0.9922f, 0.9843f, 0.8275f, 1.0f);
   this->lightManager->theLights[1].param1.x = 2.0f;
   this->lightManager->theLights[1].direction = glm::vec4(-0.0f, -15.0f, 0.0f, 1.f);
   this->lightManager->theLights[1].param1.y = 5.0f;
   this->lightManager->theLights[1].param1.z = 5.0f;
   this->lightManager->theLights[1].atten.y = 0.0001f;
   this->lightManager->theLights[1].atten.z = 0.00001f;
   this->lightManager->theLights[1].param2.x = 1.0f;
}

void cSceneManager::LoadSceneModels(GLuint& program)
{
	this->modelCatalog->LoadModels(program, this->VAOManager, this->textureManager);
}

std::vector<cModel*> cSceneManager::GetModels()
{
	return this->modelCatalog->GetModels();
}