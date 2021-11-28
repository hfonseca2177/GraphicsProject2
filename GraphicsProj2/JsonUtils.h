#pragma once
#include <rapidjson/filereadstream.h>
#include <rapidjson/document.h>
#include <string>

using namespace rapidjson;

//Reads a file from the path and converts to a rapidjson document
Document ReadFromJson(const std::string& filePath);