#include "CommandGroup.h"
#include "WaitForSeconds.h"

CommandGroup::CommandGroup() : groupType(SERIES), groupId(0)
{
	
}

CommandGroup::CommandGroup(const CommandGroupType& groupType, const int& groupId) /*: groupType(groupType), groupId(groupId)*/
{
	this->groupType = groupType;
	this->groupId = groupId;
}

CommandGroup::~CommandGroup()
{
}

void CommandGroup::AddSerialCommand(Command* command)
{
	serialCommandsList.push_back(command);
}

void CommandGroup::AddParallelCommand(Command* command)
{
	parallelCommandsList.push_back(command);
}

void CommandGroup::AddCommandGroup(const CommandGroup& commandGroup)
{
	commandGroupsList.push_back(commandGroup);
}

void CommandGroup::UpdateSerialCommands(float deltaTime)
{
	for (Command* command : serialCommandsList)
	{
		if (command->IsComplete()) continue;

		if (!command->isinprogress)
		{
			command->Start();
			command->isinprogress =true;
		}

		command->Update(deltaTime);
		command->updatedOnce = true;
		//command->updatedOnce = true;

		return;
	}
	/*if (!serialCommandsList.empty())
	{
		Command* currentCommand = *this->serialCommandsList.begin();

		if (!currentCommand->IsStarted())
		{
			currentCommand->Start();
			currentCommand->SetStarted(true);
		}
		currentCommand->Update(deltaTime);

		if (currentCommand->IsComplete())
		{
			this->serialCommandsList.erase(this->serialCommandsList.begin());
			
			delete currentCommand;
		}
	}*/
}

void CommandGroup::UpdateParallelCommands(float deltaTime)
{


	for (Command* command : parallelCommandsList)
	{
		if (command == nullptr)
		{
			continue;
		}

		if (WaitForSeconds* waitCommand = dynamic_cast<WaitForSeconds*>(command))
		{
			if (!command->IsComplete())
			{
				command->Update(deltaTime);
				command->updatedOnce = true;
				command->isinprogress =true;
				return;
			}
		}

		if (!command->isinprogress)
		{
			command->Start();
			command->isinprogress =true;
		}
		if (command->IsComplete())
		{
			continue;	
		}

		command->Update(deltaTime);
		command->updatedOnce = true;
	}
	//for (size_t i = 0; i < this->parallelCommandsList.size(); i++)
	//{

	//	
	//	{

	//	}

	//	//if wait is complete
	//	//continue
	//	//else 
	//		// wait for secons update update

	//		return;
	//	parallelCommandsList[i]->Update(deltaTime);
	//}
}

void CommandGroup::Update(float deltaTime)
{
	if (groupType ==SERIES)
	{
		UpdateSerialCommands(deltaTime);
	}
	else if(groupType ==PARALLEL)
	{
		UpdateParallelCommands(deltaTime);
	}
	
	
}

void CommandGroup::Start()
{
	if (groupType ==SERIES)
	{
		StartForSerialCommand();
	}
	else if(groupType ==PARALLEL)
	{
		StartForParallelCommands();
	}

	
}

void CommandGroup::StartForParallelCommands()
{
	
	if (parallelCommandsList.size()>0)
	{
		for (Command* command : parallelCommandsList)
		{
			if (command == nullptr) continue;

			if (WaitForSeconds* waitCommand = dynamic_cast<WaitForSeconds*>(command))
			{
				command->Start();
				command->isinprogress =true;
				if (!command->IsComplete()) return;
			}

			command->Start();
			command->isinprogress =true;
		}
	}
	
	
	
	/*if (parallelCommandsList.size()>0)
	{
		for (size_t i = 0; i < parallelCommandsList.size(); i++)
		{
			if (!parallelCommandsList[i]->IsStarted())
			{
				parallelCommandsList[i]->Start();
				parallelCommandsList[i]->SetStarted(true);
			}
		}
	}*/
	
}

void CommandGroup::StartForSerialCommand()
{

	
	if (serialCommandsList.size()>0)
	{
		for (Command* command : serialCommandsList)
		{

			if (command->IsComplete()) continue;
			command->Start();
			command->isinprogress=true;

			return;
		}
	}
	
	/*if (!serialCommandsList.empty())
	{
		Command* FirstSerialCommand = *this->serialCommandsList.begin();
		if (!FirstSerialCommand->IsStarted())
		{
			FirstSerialCommand->Start();
			FirstSerialCommand->SetStarted(true);
		}

	}*/
}

void CommandGroup::SetGroupID(const int& groupID)
{
	this->groupId = groupID;
}

int CommandGroup::GetGroupID() const
{
	return groupId;
}

bool CommandGroup::isDone()
{
	bool isDone = true;

	if (true)
	{

	}
	return false;
}
