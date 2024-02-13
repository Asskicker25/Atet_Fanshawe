#include "WorldObjectFactory.h"
#include "Floor.h"

WorldObjectFactory::WorldObjectFactory()
{
	CachedModels();

}

BaseWorldObject* WorldObjectFactory::CreateFloor(int type)
{
	BaseWorldObject* newObject = nullptr;

	if (type == 0)
	{
		newObject = new Floor();
		newObject->CopyFromModel(*floorModelOne, true);
	}
	else if (type == 1)
	{
		newObject = new Floor();
		newObject->CopyFromModel(*floorModelTwo, true);
	}

	return newObject;

}

void WorldObjectFactory::CachedModels()
{
	floorModelOne = new Floor("res/Models/DefaultQuad.fbx", false);
	floorModelOne->transform.SetScale(glm::vec3(0.5));

	floorModelTwo = new Floor("res/Models/DefaultQuad.fbx", false);
	floorModelTwo->transform.SetScale(glm::vec3(0.1));

}
