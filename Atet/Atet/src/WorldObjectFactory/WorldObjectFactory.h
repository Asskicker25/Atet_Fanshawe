#pragma once

#include "BaseWorldObject.h"
#include "BaseWorldAnimatedObject.h"

class WorldObjectFactory
{
public:

	WorldObjectFactory();

	BaseWorldObject* CreateFloor(int type = 0);
	BaseWorldObject* CreateAxisChanger();

	BaseWorldAnimatedObject* CreateTrap();

private:

	void CachedModels();

	BaseWorldObject* mAxisChanger	= nullptr;
	BaseWorldObject* mFloorModelOne = nullptr;
	BaseWorldObject* mFloorModelTwo = nullptr;

	BaseWorldAnimatedObject* mSpikeTrap = nullptr;

};

