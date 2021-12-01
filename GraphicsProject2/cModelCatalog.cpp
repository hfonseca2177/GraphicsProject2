#include "cModelCatalog.h"
#include <string>
#include <iostream>

#include "cModel.h"
#include "cVAOManager.h"
#include "JsonUtils.h"

// json
#include "rapidjson/filereadstream.h"
#include "rapidjson/document.h"
    
    void ReadConfig(const rapidjson::Value& obj, sModelConfig& config)
    {
        //coming from scene index ready   
        config.name = obj["name"].GetString();
        config.sourceFile = obj["sourceFile"].GetString();
        config.textureName = obj["textureName"].GetString();
        config.positionX = obj["positionX"].GetFloat();
        config.positionY = obj["positionY"].GetFloat();
        config.positionZ = obj["positionZ"].GetFloat();
        config.radians = obj["radians"].GetFloat();
        config.scale = obj["scale"].GetFloat();
        config.enabled = obj["enabled"].GetBool();
    }

    void cModelCatalog::LoadModels(GLuint& program, cVAOManager* gVAOManager, cBasicTextureManager* gTextureManager)
    {
        //load scene configuration
        std::string  modelIndex = "scene.json";
        rapidjson::Document scene = ReadFromJson(modelIndex);
        for (SizeType i = 0; i < scene["Objects"].Size(); i++)
        {
            //read model configuration
            sModelConfig config;
            ReadConfig(scene["Objects"][i], config);
            //if enabled loads mesh and drawinfo into VAO
            if(config.enabled)
            {
                cModel* model = new cModel();
                model->load(config, program, gVAOManager, gTextureManager);
                models.push_back(model);
            }
        }
    
    }

    std::vector<cModel*> cModelCatalog::GetModels()
    {
        return models;
    }