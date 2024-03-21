#pragma once
#include "iCommand.h"
#include <string>

class Command : public iCommand
{
public:
	Command();
	virtual  ~Command();

	 virtual void Start();
	 virtual void Update(float deltatime);
	 virtual void SetStarted(bool isStarted);

	 virtual bool IsComplete();
	 virtual bool IsStarted();
	 std::string GetCommandID();
	 std::string commandId;

	 bool updatedOnce = false;
	 bool isinprogress = false;
protected:

	bool isStart = false;
};

