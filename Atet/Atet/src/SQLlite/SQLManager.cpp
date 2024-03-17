#include "SQLManager.h"

SQLManager::SQLManager()
{
}

SQLManager::~SQLManager()
{
}

SQLManager& SQLManager::GetInstance()
{
	static SQLManager instance;

	return instance;
}

void SQLManager::Initialize()
{
    int rc = sqlite3_open("playerStat.db", &mDatabase);

    if (rc != SQLITE_OK) 
    {
        std::cerr << "Error opening SQLite database: " << sqlite3_errmsg(mDatabase) << std::endl;
        return;
    }

    std::cout << "SQLite database opened successfully." << std::endl;

  
    const char* createTableSQL = "CREATE TABLE IF NOT EXISTS PlayerStats ("
        "playerId TEXT PRIMARY KEY,"
        "health INTEGER"
        ");";

    char* errorMessage;
    rc = sqlite3_exec(mDatabase, createTableSQL, NULL, 0, &errorMessage);

    if (rc != SQLITE_OK)
    {
        std::cerr << "Error creating PlayerStats table: " << errorMessage << std::endl;
        sqlite3_free(errorMessage);
        sqlite3_close(mDatabase);
        return;
    }
    else 
    {
        std::cout << "PlayerStats table created successfully." << std::endl;
    }
}

void SQLManager::Close()
{
    sqlite3_close(mDatabase);
}

void SQLManager::SetPlayerHealth(const std::string& playerId, int healthValue)
{
    // SQL query to update or insert players health with Id

    const char* query = "INSERT OR REPLACE INTO PlayerStats (playerId, health) VALUES (?, ?);";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(mDatabase, query, -1, &stmt, nullptr) == SQLITE_OK) 
    {
        sqlite3_bind_text(stmt, 1, playerId.c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_int(stmt, 2, healthValue);
        sqlite3_step(stmt);
        sqlite3_finalize(stmt);
    }
}

int SQLManager::GetPlayerHealth(const std::string& playerId)
{
    int health = -1;
    sqlite3_stmt* stmt;

    // SQL query to select the health wiht player id

    const char* query = "SELECT health FROM PlayerStats WHERE playerId = ?;";

    if (sqlite3_prepare_v2(mDatabase, query, -1, &stmt, nullptr) == SQLITE_OK) 
    {
        sqlite3_bind_text(stmt, 1, playerId.c_str(), -1, SQLITE_TRANSIENT);

        if (sqlite3_step(stmt) == SQLITE_ROW) 
        {
            health = sqlite3_column_int(stmt, 0);
        }
        sqlite3_finalize(stmt);
    }

    return health;
}


