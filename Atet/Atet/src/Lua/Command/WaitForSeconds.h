#pragma once

#include "Command.h"

class WaitForSeconds  : public Command
{
public:

	WaitForSeconds(float time);
	~WaitForSeconds();

	 void Start() override;
	 void Update(float deltatime) override;
	 void SetStarted(bool isStarted) override;

	  bool IsComplete() override;
	  bool IsStarted() override;

private:

	float time;
	float timeStep= 0;

};

