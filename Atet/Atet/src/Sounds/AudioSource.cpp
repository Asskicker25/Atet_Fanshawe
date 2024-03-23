#include "AudioSource.h"

AudioSource::AudioSource()
{
	mAudioManager->Initialize();
	LoadAudio();
}

AudioSource::~AudioSource()
{

	mAudioManager->Destroy();
}

void AudioSource::LoadAudio()
{
	mAudioManager->Load3DAudio("Assets/Audios/Background.mp3");
	mAudioManager->Load3DAudio("Assets/Audios/Death.mp3");

}

void AudioSource::BackgroundAudio()
{
	channelId = mAudioManager->PlayAudio("Assets/Audios/Background.mp3", 1);
	mAudioManager->SetChannelVolume(channelId,0.2f);

}

void AudioSource::StopAudio()
{
	mAudioManager->SetChannelStop(channelId);
}

void AudioSource::Death()
{
	int channelId3 = mAudioManager->PlayAudio("Assets/Audios/Death.mp3", 3);
	mAudioManager->SetChannelVolume(channelId3, 0.5f);

}
