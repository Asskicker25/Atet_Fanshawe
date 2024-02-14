#pragma once

#include "BaseWorldObject.h"

class AxisChanger : public BaseWorldObject
{
public:
	AxisChanger() = default;
	AxisChanger(const std::string path, bool addToEntity = true);

	virtual void OnPropertyDraw();

	bool GetCameraFlip();
	bool GetPlayerFlip();

	void SetUsed() { mUsed = !mUsed; }

	bool mUsed = false;

	bool mCameraFlips[2] = { false, false };
	bool mPlayerFlips[2] = { false, false };

private:

	void DrawBoolArray(std::string label, bool* mArray);
};

