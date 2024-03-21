#pragma once
#include<iostream>
class BaseAudioSource
{

	virtual ~BaseAudioSource() {};

	virtual void PlayAudio() = 0;
	virtual void PauseAudio() = 0;
	virtual void StopAudio() = 0;


};

