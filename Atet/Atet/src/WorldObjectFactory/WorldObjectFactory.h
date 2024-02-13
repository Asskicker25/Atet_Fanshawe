#pragma once
#include "../WorldObjectFactory/BaseWorldObject.h"

class WorldObjectFactory
{
public:

	WorldObjectFactory();

	BaseWorldObject* CreateFloor(int type = 0);



private:

	void CachedModels();


	BaseWorldObject* floorModelOne = nullptr;
	BaseWorldObject* floorModelTwo = nullptr;


};

