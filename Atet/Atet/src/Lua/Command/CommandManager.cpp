#include "CommandManager.h"
#include <iostream>

CommandManager::CommandManager()
{
	//currentCommandGroup = new CommandGroup(SERIES,1);
}

CommandManager::~CommandManager()
{
	
}

CommandManager& CommandManager::GetInstance()
{
	static CommandManager instance;
	return instance;
}





void CommandManager::AddCommands( Command* command)
{
	if (currentCommandGroup == nullptr)
	{
		std::cout << " Command Group is NULL" << std::endl;
		return;
	}
	if (currentCommandGroup->groupType == SERIES)
	{
		currentCommandGroup->AddSerialCommand(command);
		CurrentCommand = command;

		//command->commandGroup = currentCommandGroup;
	}
	else
	{
		currentCommandGroup->AddParallelCommand(command);
		CurrentCommand = command;
	}
}

void CommandManager::BeginCommandGroup()
{
	currentCommandGroup = new CommandGroup(SERIES, 1);
}

void CommandManager::BeginCommandGroup( const CommandGroupType& type,  const int& groupId)
{
	CommandGroup* group = new CommandGroup(type, groupId);
	if (currentCommandGroup != nullptr)
	{
		
		group->parentCommandGroup = currentCommandGroup;
	}
	commandGroupList.push_back(group);
		currentCommandGroup = group;
}

void CommandManager::EndCommandGroup(const int& groupId)
{
	currentCommandGroup->Start();
	
	currentCommandGroup = currentCommandGroup->parentCommandGroup;;

}

void CommandManager::Start()
{
	if (!commandGroupList.empty())
	{
		//for (size_t i = 0; i < commandGroupList.size(); i++)
		//{
		//	//commandGroupList[i]->Start();  // Start for firstSerial command and All the parallel commands list.
		//}
	}	
}

void CommandManager::Update(float deltatime)
{
	if (!commandGroupList.empty())
	{
		for (size_t i = 0; i < commandGroupList.size(); i++)
		{

			if (commandGroupList[i]->isCollisionTrigger)
			{
				commandGroupList[i]->Update(deltatime);
			}
			

			if (commandGroupList[i]->isDone())
			{
				 // Remove commandGroup from list after done
			}
		}
	}
}

CommandGroup* CommandManager::GetLastCommandGroup()
{
	return commandGroupList[commandGroupList.size() - 1];
}

CommandGroup* CommandManager::GetCommandGroupIndex(int index)
{
	return commandGroupList[index];
}

bool CommandManager::isCommandExists(Command* command)
{

	/*for (std::vector<CommandGroup*>::const_iterator groupIter = commandGroupList.begin(); groupIter != commandGroupList.end(); ++groupIter)
	{
		
		if ((*groupIter)->isCommandExists(command))
		{
			return true;
		}
	}*/

	
	return false;
}