#include "JSON.h"

bool JSON::ReadPlayerData(const std::string& filename, PlayerData& player)
{
    std::ifstream inputFile(filename);
    if (!inputFile.is_open())
    {
        std::cout << "Error: Unable to open file " << filename << std::endl;
        return false;
    }

    std::string jsonData((std::istreambuf_iterator<char>(inputFile)), std::istreambuf_iterator<char>());
    inputFile.close();

    rapidjson::Document doc;
    doc.Parse(jsonData.c_str());


    if (doc.HasParseError())
    {
        std::cout << "Error: JSON parsing failed with code " << doc.GetParseError() << std::endl;
        return false;
    }

    if (doc.HasMember("modelPath") && doc["modelPath"].IsString() && doc.HasMember("lives") && doc["lives"].IsInt() &&
        doc.HasMember("speed") && doc["speed"].IsFloat())
    {
        player.modelPath = doc["modelPath"].GetString();
        player.lives = doc["lives"].GetInt();
        player.speed = doc["speed"].GetFloat();
        return true;
    }

    std::cout << "Error: JSON file does not contain valid PlayerData." << std::endl;
    return false;
}

bool JSON::WritePlayerData(const std::string& filename, PlayerData& playerData)
{
    rapidjson::Document doc;
    doc.SetObject();

    rapidjson::Value modelPathValue(playerData.modelPath.c_str(), doc.GetAllocator());
    doc.AddMember("modelPath", modelPathValue, doc.GetAllocator());

    doc.AddMember("lives", playerData.lives, doc.GetAllocator());
    doc.AddMember("speed", playerData.speed, doc.GetAllocator());


    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    doc.Accept(writer);

    std::ofstream outputFile(filename);
    if (!outputFile.is_open())
    {
        std::cerr << "Error: Unable to open file " << filename << " for writing." << std::endl;
        return false;
    }

    outputFile << buffer.GetString() << std::endl;
    outputFile.close();

    std::cout << "PlayerData written to " << filename << " successfully!" << std::endl;

    return true;
}

