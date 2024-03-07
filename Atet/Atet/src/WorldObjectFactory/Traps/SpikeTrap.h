#pragma once

#include "../BaseWorldAnimatedObject.h"

class SpikeTrap : public BaseWorldAnimatedObject
{
public:

	SpikeTrap();
	SpikeTrap(const std::string& modelPath, bool addToEntity = true); 

	virtual void Update(float deltaTime) override;

private:
	void Initialize();

	void SpikeUp();
	void SpikeDown();

	void HandleSpikeUp(float deltaTime);
	void HandleSpikeDown(float deltaTime);
	void HandleSpike(float deltaTime);

	bool mSpikeUp = false;
	bool mSpikeDown = false;

	bool mIsSpikeUp = false;

	float mCurrentTimeStep = 0;

	static constexpr float SPIKE_UP_VALUE = 0.5f;
	static constexpr float SPIKE_DOWN_VALUE = 1.0f;

	static constexpr float SPIKE_UP_INTERVAL = 1.5f;
	static constexpr float SPIKE_DOWN_INTERVAL = 0.55f;

	static constexpr float SPIKE_UP_SPEED = 5.0f;
	static constexpr float SPIKE_DOWN_SPEED = 1.0f;

};

