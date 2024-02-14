#include "WorldObjectFactory.h"

#include "Floor.h"
#include "AxisChanger.h"

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
		newObject->CopyFromModel(*mFloorModelOne, true);
	}
	else if (type == 1)
	{
		newObject = new Floor();
		newObject->CopyFromModel(*mFloorModelTwo, true);
	}

	return newObject;

}

BaseWorldObject* WorldObjectFactory::CreateAxisChanger()
{
	BaseWorldObject* newObject = new AxisChanger();
	newObject->CopyFromModel(*mAxisChanger, true);
	newObject->InitializePhysics(AABB, STATIC, TRIGGER);

	return newObject;
}

void WorldObjectFactory::CachedModels()
{
	mAxisChanger = new AxisChanger("res/Models/DefaultCube.fbx", false);
	mAxisChanger->shader = Renderer::GetInstance().alphaBlendShader;
	mAxisChanger->meshes[0]->material->AsMaterial()->SetBaseColor(glm::vec4(0.2,0.8,0.1f,0.2f));
	mAxisChanger->transform.SetScale(glm::vec3(0.5f));
	mAxisChanger->isGizmoItem = true;
	mAxisChanger->applyGizmoScale = false;
	mAxisChanger->name = "Axis";

	mFloorModelOne = new Floor("res/Models/DefaultQuad.fbx", false);
	mFloorModelOne->transform.SetScale(glm::vec3(0.5));

	mFloorModelTwo = new Floor("res/Models/DefaultQuad.fbx", false);
	mFloorModelTwo->transform.SetScale(glm::vec3(0.1));


}
