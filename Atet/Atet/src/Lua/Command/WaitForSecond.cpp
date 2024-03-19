#include "WaitForSeconds.h"
#include <iostream>
WaitForSeconds::WaitForSeconds(float time)
{
	this->time = time;
}

WaitForSeconds::~WaitForSeconds()
{
}

void WaitForSeconds::Start()
{
	timeStep = 0;
	
}

void WaitForSeconds::Update(float deltatime)
{
	timeStep += deltatime;
}

void WaitForSeconds::SetStarted(bool isStarted)
{
}

bool WaitForSeconds::IsComplete()
{
	if (timeStep >= time)
	{
		return true;
	}
	return false;
}

bool WaitForSeconds::IsStarted()
{
	return isStart;
}
