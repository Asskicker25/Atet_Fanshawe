#pragma once
#include "AudioManager.h"


class AudioSource
{
public:

	AudioSource();
	~AudioSource();


	void LoadAudio();

	void PlayAudio();

	void PauseAudio();
	
	void StopAudio();

	void Death();

	
private:

	AudioManager* mAudioManager = new AudioManager();


};

