#include "AxisChangeState.h"
#include "../PlayerController.h"
#include "../../WorldObjectFactory/AxisChanger.h"

void Player::AxisChangeState::Start()
{
	ePlayerAxis currentAxis = mPlayerController->mCurrentAxis;

	AxisChanger* currentAxisChange = mPlayerController->mCurrentAxisChanger;

	mPlayerController->ChangeAxis(currentAxis == ePlayerAxis::X ?
		ePlayerAxis::Z : ePlayerAxis::X);

	mPlayerController->mCameraController->mFlipCamera = currentAxisChange->GetCameraFlip();
	mPlayerController->mPlayerFaceDir = currentAxisChange->GetPlayerFlip() ? 1 : - 1;
	mPlayerController->mPlayerFaceDir *= mPlayerController->mCameraController->mFlipCamera ? -1 : 1;


	float rotationY = mPlayerController->mCurrentAxis == ePlayerAxis::X ?
		mPlayerController->mPlayerFaceDir == 1 ? 90 : -90 :
		mPlayerController->mPlayerFaceDir == 1 ? 0 : 180;

	mPlayerController->transform.SetRotation(glm::vec3(0, rotationY, 0));

	currentAxisChange->SetUsed();

	ChangeState(ePlayerState::IDLE);
}

void Player::AxisChangeState::Update()
{
}

void Player::AxisChangeState::Render()
{
}

void Player::AxisChangeState::Cleanup()
{
}
