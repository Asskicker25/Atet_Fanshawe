#pragma once

#include "CommandGroup.h"
class CommandManager
{
public:
	CommandManager();
	~CommandManager();

	static CommandManager& GetInstance();


	void AddCommands(Command* command);
	void BeginCommandGroup();
	void BeginCommandGroup(const CommandGroupType& type = SERIES, const int &groupId =0);
	void EndCommandGroup(const int& groupId);

	void Start();
	void Update(float deltatime);



	Command* CurrentCommand = nullptr;
	CommandGroup* currentCommandGroup = nullptr;

	CommandGroup* GetLastCommandGroup();
	CommandGroup* GetCommandGroupIndex(int index);

	bool isCommandExists(Command* command);
private:


	
	std::vector<CommandGroup*> commandGroupList;
	
};


