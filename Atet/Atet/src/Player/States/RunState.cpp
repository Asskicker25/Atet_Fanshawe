#include "RunState.h"
#include "../PlayerController.h"
#include <Graphics/Timer.h>

void Player::RunState::OnKeyPressed(const int& key)
{
}

void Player::RunState::OnKeyReleased(const int& key)
{
}

void Player::RunState::OnKeyHeld(const int& key)
{
}


Player::RunState::RunState()
{
	InputManager::GetInstance().AddListener(this);
}

void Player::RunState::Start()
{
}

void Player::RunState::Update()
{
	if (!HandleInput()) return;

	HandleMovement();
	HandleRotation();

	
}

void Player::RunState::Render()
{
}

void Player::RunState::Cleanup()
{
}

bool Player::RunState::HandleInput()
{
	mPlayerController->mMoveDir = InputManager::GetInstance().GetAxisX();

	if (mPlayerController->mMoveDir == 0)
	{
		ChangeState(ePlayerState::IDLE);
		return false;
	}

	return true;
}

void Player::RunState::HandleMovement()
{
	glm::vec3 mCameraRight = GetMainCamera()->transform.GetRight();

	glm::vec3 dir = mPlayerController->mCurrentAxis == ePlayerAxis::X ? glm::vec3(mCameraRight.x, 0, 0) :
		glm::vec3(0, 0, mCameraRight.z);

	dir = glm::normalize(dir);
	dir *= mPlayerController->mMoveDir;


	mPlayerController->transform.position += dir 
		* mPlayerController->mPlayerData.speed * Timer::GetInstance().deltaTime;
}

void Player::RunState::HandleRotation()
{
	mPlayerController->mPlayerFaceDir = mPlayerController->mMoveDir;
	mPlayerController->mPlayerFaceDir *= mPlayerController->mCameraController->mFlipCamera ? -1 : 1;


	float rotationY = mPlayerController->mCurrentAxis == ePlayerAxis::X ?
		mPlayerController->mPlayerFaceDir == 1 ? 90 : -90 :
		mPlayerController->mPlayerFaceDir == 1 ? 0 : 180;

	mPlayerController->transform.SetRotation(glm::vec3(0, rotationY, 0));


}

