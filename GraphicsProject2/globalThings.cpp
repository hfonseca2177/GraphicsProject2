#include "globalThings.h"

cFlyCamera* g_pFlyCamera = NULL;
cVAOManager* g_pVAOManager = NULL;
cSceneManager* g_pSceneManager = NULL;
cShaderManager* g_pShaderManager = NULL;
cShaderLoader* g_pShaderLoader = NULL;
cBasicTextureManager* g_pTextureManager = NULL;
cLightManager* g_pTheLights = NULL;

unsigned int g_selectedObject = 0;
unsigned int g_selectedLight = 0;
glm::vec3 g_heightMapUVOffsetRotation = glm::vec3(0.0f, 0.0f, 0.0f);
std::string g_TitleText = "";
//
bool g_FindObjectByUniqueID(unsigned int uniqueID_toFind, cMesh*& theObjectIFound);

cMesh* g_findObjectByUniqueID(unsigned int uniqueID_toFind)
{
    //Scene loaded models
    std::vector<cModel*> models = ::g_pSceneManager->GetModels();
    
    for ( unsigned int index = 0; index != models.size(); index++ )
    {
        if (models[index]->GetMesh()->getUniqueID() == uniqueID_toFind )
        {
            return models[index]->GetMesh();
        }
    }
    return NULL;
}

bool g_findObjectByUniqueID( unsigned int uniqueID_toFind, cMesh &theObjectIFound )
{
    //Scene loaded models
    std::vector<cModel*> models = ::g_pSceneManager->GetModels();

    for ( unsigned int index = 0; index != models.size(); index++ )
    {
        if (models[index]->GetMesh()->getUniqueID() == uniqueID_toFind )
        {
            // Dereferences and returns a stack based copy
            theObjectIFound = *(models[index]->GetMesh());
            return true;
        }
    }
    return false;
}

bool g_FindObjectByUniqueID(unsigned int uniqueID_toFind, cMesh* &theObjectIFound)
{
    //Scene loaded models
    std::vector<cModel*> models = ::g_pSceneManager->GetModels();

    for ( unsigned int index = 0; index != models.size(); index++ )
    {
        if (models[index]->GetMesh()->getUniqueID() == uniqueID_toFind )
        {
            // Returns a pointer to the object
            theObjectIFound = models[index]->GetMesh();
            return true;
        }
    }
    return false;
}

// If not found, return NULL (0)
cMesh* g_findObjectByFriendlyName(std::string NametoFind)
{
    //Scene loaded models
    std::vector<cModel*> models = ::g_pSceneManager->GetModels();

    for ( unsigned int index = 0; index != models.size(); index++ )
    {
        cMesh* pMeshToTest = models[index]->GetMesh();

        // Is functionally the same thing as using a reference:
        //cMesh& meshToTest = g_vecMeshes[index];

        if ( pMeshToTest->friendlyName == NametoFind )
        {
            return pMeshToTest;
        }
    }
    // DIDN'T find it, return NULL
    return NULL;
}

cMesh* g_FindObjectByUniqueID(unsigned int uniqueID_toFind)
{
    //Scene loaded models
    std::vector<cModel*> models = ::g_pSceneManager->GetModels();

    for ( unsigned int index = 0; index != models.size(); index++ )
    {
        cMesh* pMeshToTest = models[index]->GetMesh();

        // Is functionally the same thing as using a reference:
        //cMesh& meshToTest = g_vecMeshes[index];

        if ( pMeshToTest->getUniqueID() == uniqueID_toFind )
        {
            return pMeshToTest;
        }
    }
    // DIDN'T find it, return NULL
    return NULL;
}


