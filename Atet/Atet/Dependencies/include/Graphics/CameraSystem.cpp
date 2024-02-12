#include "CameraSystem.h"

CameraSystem& CameraSystem::GetInstance()
{
	static CameraSystem instance;
	return instance;
}

void CameraSystem::AddCamera(Camera* camera)
{
	mListOfCameras.push_back(camera);

	if (camera->renderTexture != nullptr) return;

	mainCamera = camera;
}

void CameraSystem::RemoveCamera(Camera* camera)
{
	mListOfCameras.erase(std::remove(mListOfCameras.begin(), mListOfCameras.end(), camera), 
		mListOfCameras.end());
}

Camera* CameraSystem::GetMainCamera()
{
	return mainCamera;
}
