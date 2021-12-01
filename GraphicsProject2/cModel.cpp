#include <iostream>
#include <glm/gtc/matrix_transform.hpp>
#include "cModel.h"



void cModel::load(sModelConfig config, GLuint& program, cVAOManager* gVAOManager, cBasicTextureManager* gTextureManager)
{
    this->name = config.sourceFile;
    this->mesh = new cMesh();
    this->mesh->meshName = config.sourceFile;
    this->mesh->orientationXYZ.y = config.radians;
    this->mesh->positionXYZ.x = config.positionX;
    this->mesh->positionXYZ.y = config.positionY;
    this->mesh->positionXYZ.z = config.positionZ;
    this->mesh->scale = config.scale;
    this->mesh->bDontLight = false;
    this->mesh->friendlyName = config.name;
    this->mesh->textureNames[0] = config.textureName;
    this->mesh->textureRatios[0] = 1.f;

    //Load the vertices
    if (gVAOManager->LoadModelIntoVAO(config.sourceFile, this->drawInfo, program))
    {
        std::cout << "Loaded the model: " << this->drawInfo.meshName << std::endl;
        std::cout << this->drawInfo.numberOfVertices << " vertices loaded" << std::endl;
        std::cout << this->drawInfo.numberOfTriangles << " triangles loaded" << std::endl;
    }
    else
    {
        std::cout << "Error: Didn't load the model OK" << std::endl;
    }

    //Add texture to the manager
    gTextureManager->Create2DTextureFromBMPFile(config.textureName, true);

}

std::string cModel::GetName()
{
    return this->name;
}

cMesh* cModel::GetMesh()
{
    return this->mesh;
}

sModelDrawInfo  cModel::GetDrawInfo() {
    return this->drawInfo;
}

glm::mat4 cModel::GetModelTransformation()
{
    glm::mat4 trasformation;

    
    trasformation = glm::mat4(1.0f);
        
    // Translate or "move" the object somewhere
    glm::mat4 matTranslate = glm::translate(glm::mat4(1.0f),
        this->mesh->positionXYZ);
        
    // Rotation around the Z axis
    glm::mat4 rotateZ = glm::rotate(glm::mat4(1.0f),
        this->mesh->orientationXYZ.z,
        glm::vec3(0.0f, 0.0f, 1.0f));

    // Rotation around the Y axis
    glm::mat4 rotateY = glm::rotate(glm::mat4(1.0f),
        this->mesh->orientationXYZ.y,
        glm::vec3(0.0f, 1.0f, 0.0f));

    // Rotation around the X axis
    glm::mat4 rotateX = glm::rotate(glm::mat4(1.0f),
        this->mesh->orientationXYZ.x,
        glm::vec3(1.0f, 0.0f, 0.0f));

    // Scale the model
    glm::mat4 matScale = glm::scale(glm::mat4(1.0f),
        glm::vec3(this->mesh->scale,  // Scale in X
            this->mesh->scale,  // Scale in Y
            this->mesh->scale));// Scale in Z

    trasformation = trasformation * matTranslate;
    trasformation = trasformation * rotateZ;
    trasformation = trasformation * rotateY;
    trasformation = trasformation * rotateX;
    trasformation = trasformation * matScale;

    return trasformation;
}
