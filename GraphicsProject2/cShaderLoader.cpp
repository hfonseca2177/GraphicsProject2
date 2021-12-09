#include "cShaderManager.h"
#include "cShaderLoader.h"
#include <iostream>

const char* DEFAULT_SHADER = "Shader#1";
const char* MAT_MODEL = "matModel";
const char* MAT_VIEW = "matView";
const char* MAT_PROJECTION = "matProjection";
const char* MAT_MODEL_INVERSE = "matModelInverseTranspose";


void cShaderLoader::LoadShaders(GLuint& program, cShaderManager* _shaderManager)
{
    this->shaderManager = _shaderManager;

    cShaderManager::cShader vertShader;
    vertShader.fileName = "assets/shaders/vertShader_01.glsl";

    cShaderManager::cShader fragShader;
    fragShader.fileName = "assets/shaders/fragShader_01.glsl";

    cShaderManager::cShader geomShader;
    geomShader.fileName = "assets/shaders/geomShader.glsl";

    if (shaderManager->createProgramFromFile(DEFAULT_SHADER, vertShader, geomShader, fragShader))
    {
        std::cout << "Shader compiled OK" << std::endl;         
        // Set the "program" variable to the one the Shader Manager used...
        program = shaderManager->getIDFromFriendlyName(DEFAULT_SHADER);
    }
    else
    {
        std::cout << "Error making shader program: " << std::endl;
        std::cout << shaderManager->getLastError() << std::endl;
    }

    MapShaderVariables(program);
}

void cShaderLoader::MapShaderVariables(GLuint& program)
{

    cShaderManager::cShaderProgram* pShaderProc = GetLoadedShader();

    pShaderProc->mapUniformName_to_UniformLocation[MAT_MODEL] = glGetUniformLocation(program, MAT_MODEL);
    pShaderProc->mapUniformName_to_UniformLocation[MAT_VIEW] = glGetUniformLocation(program, MAT_VIEW);
    pShaderProc->mapUniformName_to_UniformLocation[MAT_PROJECTION] = glGetUniformLocation(program, MAT_PROJECTION);
    pShaderProc->mapUniformName_to_UniformLocation[MAT_MODEL_INVERSE] = glGetUniformLocation(program, MAT_MODEL_INVERSE);
    pShaderProc->mapUniformName_to_UniformLocation["wholeObjectSpecularColour"] = glGetUniformLocation(program, "wholeObjectSpecularColour");
    pShaderProc->mapUniformName_to_UniformLocation["theLights[0].position"] = glGetUniformLocation(program, "wholeObjectSpecularColour");
    
}

cShaderManager::cShaderProgram* cShaderLoader::GetLoadedShader()
{
    return this->shaderManager->pGetShaderProgramFromFriendlyName(DEFAULT_SHADER);
    
}

int cShaderLoader::GetModelLocation()
{
    return GetLoadedShader()->getUniformID_From_Name(MAT_MODEL);
}

int cShaderLoader::GetViewLocation()
{
    return GetLoadedShader()->getUniformID_From_Name(MAT_VIEW);
}

int cShaderLoader::GetProjectionLocation()
{
    return GetLoadedShader()->getUniformID_From_Name(MAT_PROJECTION);
}

int cShaderLoader::GetModelInverseTransposeLocation()
{
    return GetLoadedShader()->getUniformID_From_Name(MAT_MODEL_INVERSE);
}
