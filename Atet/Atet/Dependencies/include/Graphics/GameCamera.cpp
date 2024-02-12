#include "GameCamera.h"
#include "CameraSystem.h"

GameCamera::GameCamera()
{
	CameraSystem::GetInstance().AddCamera(this);
}

GameCamera::~GameCamera()
{
	CameraSystem::GetInstance().RemoveCamera(this);
}
