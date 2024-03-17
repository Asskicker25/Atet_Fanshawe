#include "PlayerHealthManager.h"
#include "../SQLlite/SQLManager.h"

PlayerHealthManager::PlayerHealthManager()
{
}

PlayerHealthManager::~PlayerHealthManager()
{
}

void PlayerHealthManager::Intialize(const std::string& playerId)
{
    SetPlayerId(playerId);

    int healthCount = GetPlayerHealthFromDatabase();

    if (healthCount == -1)
    {
        SetPlayerHealth(5);
    }
    else
    {
        mPlayerHealthCount = healthCount;
    }
}

void PlayerHealthManager::SetPlayerHealthToDataBase(int healthValue)
{
    SQLManager::GetInstance().SetPlayerHealth(mPlayerId, healthValue);
}

void PlayerHealthManager::SetPlayerId(const std::string& playerId)
{
    mPlayerId = playerId;
}

void PlayerHealthManager::SetPlayerHealth(int lives)
{
    mPlayerHealthCount = lives;

    SetPlayerHealthToDataBase(mPlayerHealthCount);
}

void PlayerHealthManager::ReduceLivesCountby(int lives)
{
    mPlayerHealthCount -= lives;
}

const std::string PlayerHealthManager::GetPlayerId()
{
    return mPlayerId;
}

int PlayerHealthManager::GetPlayerHealthFromDatabase()
{
    return SQLManager::GetInstance().GetPlayerHealth(mPlayerId);
}

int PlayerHealthManager::GetPlayerHealthCount()
{
    return mPlayerHealthCount;
}
