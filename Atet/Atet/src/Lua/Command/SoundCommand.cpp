#include "SoundCommand.h"
SoundCommand::SoundCommand()
{
	
}

SoundCommand::SoundCommand(AudioSource* audio, std::string soundName)
{

	this->audioSource = audio;
	this->soundName = soundName;
}

SoundCommand::~SoundCommand()
{


}

void SoundCommand::Start()
{
	
}

void SoundCommand::Update(float deltatime)
{
	if (soundName == "Die")
	{
		if (!isInvoked)
		{
			Play();
			isInvoked = true;
		}
	}
	if (soundName == "Add")
	{
		if (!isInvoked)
		{
			std::cout << "Second Audio Playing" << std::endl;
			isInvoked = true;
		}
	}
	

}

void SoundCommand::SetStarted(bool isStarted)
{
}

bool SoundCommand::IsComplete()
{
	return isInvoked;
}

bool SoundCommand::IsStarted()
{
	return false;
}

void SoundCommand::Play()
{
	std::cout << "Sound is Playing" << std::endl;

	AudioSource* source = new AudioSource();
	source->PlayAudio();
}
