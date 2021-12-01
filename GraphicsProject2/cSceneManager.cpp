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
	//Dark to represent dark side of the moon
   this->lightManager->theLights[0].position = glm::vec4(20.0f, -35.0f, 50.0f, 1.0f);
   this->lightManager->theLights[0].diffuse *= 0.001f;
   this->lightManager->theLights[0].param1.x = 2.0f;
   this->lightManager->theLights[0].direction = glm::vec4(20.0f, -15.0f, 380.0f, 1.0f);
   this->lightManager->theLights[0].param1.y = 5.0f;
   this->lightManager->theLights[0].param1.z = 5.0f;
   this->lightManager->theLights[0].atten.y = 0.0001f;
   this->lightManager->theLights[0].atten.z = 0.00001f;
   this->lightManager->theLights[0].param2.x = 1.0f;

   //Give some luninosite near vehicle
   this->lightManager->theLights[1].position = glm::vec4(0.0f, 45.0f, 768.0f, 1.f);
   this->lightManager->theLights[1].diffuse = glm::vec4(0.9922f, 0.9843f, 0.8275f, 1.0f);
   this->lightManager->theLights[1].param1.x = 1.0f;
   this->lightManager->theLights[1].direction = glm::vec4(-0.0f, -15.0f, 0.0f, 1.f);
   this->lightManager->theLights[1].param1.y = 5.0f;
   this->lightManager->theLights[1].param1.z = 5.0f;
   this->lightManager->theLights[1].atten.y = 0.0001f;
   this->lightManager->theLights[1].atten.z = 0.00001f;
   this->lightManager->theLights[1].param2.x = 1.0f;

   //Blusih for carrier 
   this->lightManager->theLights[2].position = glm::vec4(-380.0f, 185.0f, 680.0f, 1.f);
   this->lightManager->theLights[2].diffuse = glm::vec4(0.0022f, 0.0033f, 0.9843f, 1.0f);
   this->lightManager->theLights[2].param1.x = 3.0f;
   this->lightManager->theLights[2].direction = glm::vec4(-0.0f, -5.0f, 0.0f, 1.f);
   this->lightManager->theLights[2].atten.y = 0.0001f;
   this->lightManager->theLights[2].atten.z = 0.00001f;
   this->lightManager->theLights[2].param2.x = 1.0f;


   this->lightManager->theLights[3].position = glm::vec4(-20.0f, 10.f, -380.0f, 1.f);
   this->lightManager->theLights[3].diffuse = glm::vec4(0.1f, 0.0f, 0.0f, 1.0f);
   this->lightManager->theLights[3].param1.x = 1.0f;
   this->lightManager->theLights[3].direction = glm::vec4(0.0f, 0.0f, -380.0f, 1.f);   
   this->lightManager->theLights[3].atten.y = 0.001f;
   this->lightManager->theLights[3].atten.z = 0.0001f;
   this->lightManager->theLights[3].param2.x = 1.0f;

   this->lightManager->theLights[4].position = glm::vec4(-20.0f, 0.f, 0.0f, 1.f);
   this->lightManager->theLights[4].diffuse = glm::vec4(0.1f, 0.0f, 0.0f, 1.0f);
   this->lightManager->theLights[4].param1.x = 1.0f;
   this->lightManager->theLights[4].direction = glm::vec4(70.0f, 450.0f, 188.0f, 1.f);
   this->lightManager->theLights[4].atten.y = 0.0001f;
   this->lightManager->theLights[4].atten.z = 0.00001f;
   this->lightManager->theLights[4].param2.x = 1.0f;

   //More carrier lights
   this->lightManager->theLights[5].position = glm::vec4(-380.0f, 185.0f, 1680.0f, 1.f);
   this->lightManager->theLights[5].diffuse = glm::vec4(0.0022f, 0.0033f, 0.9843f, 1.0f);
   this->lightManager->theLights[5].param1.x = 3.0f;
   this->lightManager->theLights[5].direction = glm::vec4(-0.0f, -5.0f, 0.0f, 1.f);
   this->lightManager->theLights[5].atten.y = 0.0001f;
   this->lightManager->theLights[5].atten.z = 0.00001f;
   this->lightManager->theLights[5].param2.x = 1.0f;

   this->lightManager->theLights[6].position = glm::vec4(-380.0f, 185.0f, 2380.0f, 1.f);
   this->lightManager->theLights[6].diffuse = glm::vec4(0.0022f, 0.0033f, 0.9843f, 1.0f);
   this->lightManager->theLights[6].param1.x = 3.0f;
   this->lightManager->theLights[6].direction = glm::vec4(-0.0f, -5.0f, 0.0f, 1.f);
   this->lightManager->theLights[6].atten.y = 0.0001f;
   this->lightManager->theLights[6].atten.z = 0.00001f;
   this->lightManager->theLights[6].param2.x = 1.0f;
}

void cSceneManager::LoadSceneModels(GLuint& program)
{
	this->modelCatalog->LoadModels(program, this->VAOManager, this->textureManager);
}

std::vector<cModel*> cSceneManager::GetModels()
{
	return this->modelCatalog->GetModels();
}