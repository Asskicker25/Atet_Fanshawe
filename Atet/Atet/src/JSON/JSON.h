#pragma once
#include <iostream>
#include <fstream>
#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>

#include "../Player/PlayerData.h"

class JSON
{
public:
	static bool ReadPlayerData(const std::string& filename, PlayerData& playerData);

	static bool WritePlayerData(const std::string& filename, PlayerData& playerData);
};

