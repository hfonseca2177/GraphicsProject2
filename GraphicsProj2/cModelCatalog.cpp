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
        config.sourceFile = obj["sourceFile"].GetString();
        config.name = obj["name"].GetString();
        config.positionX = obj["positionX"].GetFloat();
        config.positionY = obj["positionY"].GetFloat();
        config.positionZ = obj["positionZ"].GetFloat();
        config.scale = obj["scale"].GetFloat();
        config.red = obj["red"].GetFloat();
        config.blue = obj["blue"].GetFloat();
        config.green = obj["green"].GetFloat();
        config.overrideColor = obj["overrideColor"].GetBool();
        config.enabled = obj["enabled"].GetBool();
        config.lairLabel = obj["lairLabel"].GetString();
        config.lootable = obj["lootable"].GetBool();
    }

    void cModelCatalog::LoadModels(GLuint& program, cVAOManager& gVAOManager)
    {
        //load scene configuration
        std::string  modelIndex = "assets/models/scene.json";
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
                model->load(config, program, gVAOManager);
                models.push_back(model);
            }
        }
    
    }

    std::vector<cModel*> cModelCatalog::GetModels()
    {
        return models;
    }