#pragma once
#include "Command.h"
#include <iostream>

class SoundCommand : public Command
{
public:
	SoundCommand();
	~SoundCommand();

	void Start() override;
	void Update(float deltatime) override;
	void SetStarted(bool isStarted) override;

	bool IsComplete() override;
	bool IsStarted() override;

	void Play();

private:

	float time;
	float timeStep;
};

