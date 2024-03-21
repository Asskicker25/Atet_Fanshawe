#include "SoundCommand.h"
#include "../../Sounds/AudioSource.h"
SoundCommand::SoundCommand()
{
	std::cout << "Sound is Playing" << std::endl;
	
}

SoundCommand::~SoundCommand()
{


}

void SoundCommand::Start()
{
	
}

void SoundCommand::Update(float deltatime)
{
}

void SoundCommand::SetStarted(bool isStarted)
{
}

bool SoundCommand::IsComplete()
{
	return false;
}

bool SoundCommand::IsStarted()
{
	return false;
}

void SoundCommand::Play()
{

	AudioSource* source = new AudioSource();
	source->PlayAudio();
}
