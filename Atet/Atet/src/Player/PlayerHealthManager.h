#pragma once
#include<string>

class PlayerHealthManager
{
public:

	PlayerHealthManager();
	~PlayerHealthManager();

	void Intialize(const std::string& playerId);
	void SetPlayerId(const std::string& playerId);
	void SetPlayerHealth(int lives);
	void ReduceLivesCountby(int lives = 1);

	const std::string GetPlayerId();
	int GetPlayerHealthCount();

private:

	  void SetPlayerHealthToDataBase(int healthValue);
	  int GetPlayerHealthFromDatabase();

	  std::string mPlayerId;
	  int mPlayerHealthCount;
};

