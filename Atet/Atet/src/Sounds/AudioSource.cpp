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
	mAudioManager->Load3DAudio("Assets/Audios/assassins.mp3");

}

void AudioSource::PlayAudio()
{
	int channelId3 = mAudioManager->PlayAudio("Assets/Audios/assassins.mp3", 3);
	mAudioManager->SetChannelVolume(channelId3, 0.5f);

}

void AudioSource::Death()
{
	int channelId3 = mAudioManager->PlayAudio("Assets/Audios/Death.mp3", 3);
	mAudioManager->SetChannelVolume(channelId3, 0.5f);

}
