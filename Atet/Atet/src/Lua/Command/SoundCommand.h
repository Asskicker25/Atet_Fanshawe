#pragma once
#include "Command.h"
#include <iostream>
#include "../../Sounds/AudioSource.h"

class SoundCommand : public Command
{
public:
	SoundCommand();
	SoundCommand(AudioSource* audio, std::string soundName);
	~SoundCommand();

	void Start() override;
	void Update(float deltatime) override;
	void SetStarted(bool isStarted) override;

	bool IsComplete() override;
	bool IsStarted() override;

	void Play();
	void Die();

private:
	AudioSource* audioSource;
	std::string soundName;
	float time;
	float timeStep;
	bool isInvoked = false;
};

