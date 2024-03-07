#include "SpikeTrap.h"

#include <Graphics/MathUtils.h>

using namespace MathUtilities;

SpikeTrap::SpikeTrap()
{
	Initialize();
}

SpikeTrap::SpikeTrap(const std::string& modelPath, bool addToEntity) : BaseWorldAnimatedObject(modelPath, addToEntity)
{
	Initialize();
}

void SpikeTrap::Update(float deltaTime)
{
	PhysicsSkeletonObject::Update(deltaTime);

	HandleSpike(deltaTime);
	HandleSpikeUp(deltaTime);
	HandleSpikeDown(deltaTime);
}

void SpikeTrap::Initialize()
{
	mIsPlaying = true;
	mControlTime = true;
	isPhysicsEnabled = false;
	mControlTimeParam = 1;

	userData = this;
	tag = "Trap";
}

void SpikeTrap::SpikeUp()
{
	mSpikeUp = true;
	mCurrentTimeStep = 0;
	mControlTimeParam = SPIKE_DOWN_VALUE;
	isPhysicsEnabled = true;
}

void SpikeTrap::SpikeDown()
{
	mSpikeDown = true;
	mCurrentTimeStep = 0;
	mControlTimeParam = SPIKE_UP_VALUE;
}

void SpikeTrap::HandleSpikeUp(float deltaTime)
{
	if (!mSpikeUp) return;

	mCurrentTimeStep += deltaTime * SPIKE_UP_SPEED;

	mControlTimeParam = MathUtils::Remap(mCurrentTimeStep, 0, 1, SPIKE_DOWN_VALUE, SPIKE_UP_VALUE);

	if (mCurrentTimeStep > 1)
	{
		mSpikeUp = false;
		mIsSpikeUp = true;
		mCurrentTimeStep = 0;
	}
}

void SpikeTrap::HandleSpikeDown(float deltaTime)
{
	if (!mSpikeDown) return;

	mCurrentTimeStep += deltaTime * SPIKE_DOWN_SPEED;
	mControlTimeParam = MathUtils::Remap(mCurrentTimeStep, 0, 1, SPIKE_UP_VALUE, SPIKE_DOWN_VALUE);


	if (mCurrentTimeStep > 1)
	{
		mSpikeDown = false;
		mIsSpikeUp = false;
		isPhysicsEnabled = false;
		mCurrentTimeStep = 0;
	}
}

void SpikeTrap::HandleSpike(float deltaTime)
{
	if (mSpikeUp || mSpikeDown) return;

	mCurrentTimeStep += deltaTime;

	if (mCurrentTimeStep > (mIsSpikeUp ? SPIKE_DOWN_INTERVAL : SPIKE_UP_INTERVAL))
	{
		if (mIsSpikeUp)
		{
			SpikeDown();
		}
		else
		{
			SpikeUp();
		}
	}
}
