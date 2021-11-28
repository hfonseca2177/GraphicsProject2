#include <rapidjson/filereadstream.h>
#include <rapidjson/document.h>
#include <string>

using namespace rapidjson;

Document ReadFromJson(const std::string& filePath)
{
	
	FILE* fp = 0;
	fopen_s(&fp, filePath.c_str(), "rb"); // non-Windows use "r"

	char readBuffer[65536];
	FileReadStream is(fp, readBuffer, sizeof(readBuffer));

	Document d;
	d.ParseStream(is);
	
	fclose(fp);
	return d;
}