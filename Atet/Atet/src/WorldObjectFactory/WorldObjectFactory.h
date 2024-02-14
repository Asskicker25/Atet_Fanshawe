#pragma once

#include "BaseWorldObject.h"

class WorldObjectFactory
{
public:

	WorldObjectFactory();

	BaseWorldObject* CreateFloor(int type = 0);
	BaseWorldObject* CreateAxisChanger();

private:

	void CachedModels();

	BaseWorldObject* mAxisChanger	= nullptr;
	BaseWorldObject* mFloorModelOne = nullptr;
	BaseWorldObject* mFloorModelTwo = nullptr;


};

