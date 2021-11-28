#include <iostream>
#include <glm/gtc/matrix_transform.hpp>

#include "cModel.h"
#include "cVAOManager.h"


void cModel::load(sModelConfig config, GLuint& program, cVAOManager& gVAOManager)
{
    this->name = config.sourceFile;
    this->mesh = new cMesh();
    this->mesh->meshName = config.sourceFile;
    this->mesh->orientationXYZ.z = config.radians;
    this->mesh->positionXYZ.x = config.positionX;
    this->mesh->positionXYZ.y = config.positionY;
    this->mesh->positionXYZ.z = config.positionZ;
    this->mesh->scale = config.scale;
    this->lairLabel = config.lairLabel;
    this->lootable = config.lootable;
    this->looted = false;

    if (config.overrideColor)
    {
        this->mesh->bOverriveVertexColourHACK = true;
        this->mesh->vertexColourOverrideHACK = glm::vec3(config.red, config.green, config.blue);
    }

    if (gVAOManager.LoadModelIntoVAO(config.sourceFile, this->drawInfo, program))
    {
        std::cout << "Loaded the model: " << this->drawInfo.meshName << std::endl;
        std::cout << this->drawInfo.numberOfVertices << " vertices loaded" << std::endl;
        std::cout << this->drawInfo.numberOfTriangles << " triangles loaded" << std::endl;
    }
    else
    {
        std::cout << "Error: Didn't load the model OK" << std::endl;
    }

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

bool cModel::IsLootable()
{
    return this->lootable;
}

std::string cModel::GetLairLabel()
{
    return this->lairLabel;
}

void cModel::SetLooted(bool _looted)
{
    this->looted = _looted;
}
