#include "globalThings.h"

cFlyCamera* g_pFlyCamera = NULL;
cVAOManager* g_pVAOManager = NULL;
cShaderManager* g_pShaderManager = NULL;
cBasicTextureManager* g_pTextureManager = NULL;
cLightManager* g_pTheLights = NULL;
std::vector< cMesh* > g_vec_pMeshes;
cMesh* g_pDebugSphere = NULL;
bool g_bShowDebugShere = true;
unsigned int g_selectedObject = 0;
unsigned int g_selectedLight = 0;
glm::vec3 g_heightMapUVOffsetRotation = glm::vec3(0.0f, 0.0f, 0.0f);
std::string g_TitleText = "";

bool g_FindObjectByUniqueID(unsigned int uniqueID_toFind, cMesh*& theObjectIFound);

cMesh* g_findObjectByUniqueID(unsigned int uniqueID_toFind)
{
    for ( unsigned int index = 0; index != ::g_vec_pMeshes.size(); index++ )
    {
        if ( ::g_vec_pMeshes[index]->getUniqueID() == uniqueID_toFind )
        {
            return ::g_vec_pMeshes[index];
        }
    }
    return NULL;
}

bool g_findObjectByUniqueID( unsigned int uniqueID_toFind, cMesh &theObjectIFound )
{
    for ( unsigned int index = 0; index != ::g_vec_pMeshes.size(); index++ )
    {
        if ( ::g_vec_pMeshes[index]->getUniqueID() == uniqueID_toFind )
        {
            // Dereferences and returns a stack based copy
            theObjectIFound = *(::g_vec_pMeshes[index]);
            return true;
        }
    }
    return false;
}

bool g_FindObjectByUniqueID(unsigned int uniqueID_toFind, cMesh* &theObjectIFound)
{
    for ( unsigned int index = 0; index != ::g_vec_pMeshes.size(); index++ )
    {
        if ( ::g_vec_pMeshes[index]->getUniqueID() == uniqueID_toFind )
        {
            // Returns a pointer to the object
            theObjectIFound = ::g_vec_pMeshes[index];
            return true;
        }
    }
    return false;
}

// If not found, return NULL (0)
cMesh* g_findObjectByFriendlyName(std::string NametoFind)
{
    for ( unsigned int index = 0; index != ::g_vec_pMeshes.size(); index++ )
    {
        cMesh* pMeshToTest = ::g_vec_pMeshes[index];

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
    for ( unsigned int index = 0; index != ::g_vec_pMeshes.size(); index++ )
    {
        cMesh* pMeshToTest = ::g_vec_pMeshes[index];

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


