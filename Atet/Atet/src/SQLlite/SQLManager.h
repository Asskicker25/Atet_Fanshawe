#pragma once
#include "sqlite3.h"
#include <iostream>
#include <string>
class SQLManager
{
public:

	SQLManager();
	~SQLManager();

	static SQLManager& GetInstance();

	void Initialize();
	void Close();
	
	void SetPlayerHealth(const std::string& playerId, int healthValue);
	int GetPlayerHealth(const std::string& playerId);
private:
	sqlite3* mDatabase;
};

