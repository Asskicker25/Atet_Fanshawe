#include "Command.h"

Command::Command()
{
}

Command::~Command()
{
}

void Command::Start()
{
}

void Command::Update(float deltatime)
{
}

void Command::SetStarted(bool isStarted)
{
	isStart = isStarted;
}

bool Command::IsComplete()
{
	return false;
}

bool Command::IsStarted()
{
	return isStart;
}

std::string Command::GetCommandID()
{
	return commandId;
}
