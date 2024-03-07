#include <Graphics/EntityManager/EntityManager.h>

#include "Scene_1.h"
#include "../AppSettings.h"
#include "../Player/PlayerController.h"
#include "../WorldObjectFactory/AxisChanger.h"

using namespace Player;

void Scene_1::Start()
{
	GameCamera* mainCamera = new GameCamera();
	mainCamera->InitializeCamera(PERSPECTIVE, GAME_RESOLUTION_WIDTH, GAME_RESOLUTION_HEIGHT, 0.1f, 100.0f, 45.0f);
	mainCamera->transform.SetPosition(glm::vec3(-3.3, 3, 7.5f));
	mainCamera->transform.SetRotation(glm::vec3(-12.1, 0, 0.0f));

	Light* dirLight = new Light();
	dirLight->transform.SetScale(glm::vec3(0.1f));
	dirLight->transform.SetPosition(glm::vec3(0, 0, 3));
	dirLight->InitializeLight(Directional);

	BaseWorldObject* floor_1 = worldFactory->CreateFloor(0);
	floor_1->name = "Floor_1";
	floor_1->transform.SetRotation(glm::vec3(90, 0, 0));
	floor_1->transform.SetScale(glm::vec3(10, 1, 1));

	BaseWorldObject* floor_2 = worldFactory->CreateFloor(0);
	floor_2->name = "Floor_2";
	floor_2->transform.SetPosition(glm::vec3(9, 0, -7));
	floor_2->transform.SetRotation(glm::vec3(90, 0, 0));
	floor_2->transform.SetScale(glm::vec3(1, 6, 1));

	BaseWorldObject* floor_3 = worldFactory->CreateFloor(0);
	floor_3->name = "Floor_3";
	floor_3->transform.SetPosition(glm::vec3(15, 0, -12));
	floor_3->transform.SetRotation(glm::vec3(90, 0, 0));
	floor_3->transform.SetScale(glm::vec3(5, 1, 1));

	BaseWorldObject* axisChanger_1 = worldFactory->CreateAxisChanger();
	axisChanger_1->name = "AxisChanger_1";
	axisChanger_1->transform.SetPosition(glm::vec3(9, 0.6, 0));
	((AxisChanger*)axisChanger_1)->mCameraFlips[0] = true;
	((AxisChanger*)axisChanger_1)->mPlayerFlips[0] = true;

	BaseWorldObject* axisChanger_2 = worldFactory->CreateAxisChanger();
	axisChanger_2->name = "AxisChanger_2";
	axisChanger_2->transform.SetPosition(glm::vec3(9, 0.6, -11.75));
	((AxisChanger*)axisChanger_2)->mCameraFlips[0] = true;
	((AxisChanger*)axisChanger_2)->mCameraFlips[1] = true;

	BaseWorldAnimatedObject* spikeTrap = worldFactory->CreateTrap();
	spikeTrap->name = "SpikeTrap";

	PlayerController* playerController = new PlayerController();
	playerController->transform.SetPosition(glm::vec3( - 3.0, 0, 0));
	
}

void Scene_1::Update()
{
}

void Scene_1::Render()
{
}
