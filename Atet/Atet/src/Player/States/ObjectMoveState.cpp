#include "ObjectMoveState.h"
#include "../PlayerController.h"
#include "../../WorldObjectFactory/MovableObject.h"

#include <Graphics/InputManager/InputManager.h>
#include <Graphics/Timer.h>

void Player::ObjectMoveState::Start()
{
	mMovableObject = mPlayerController->mCurrentMovableObject;



	mInitOffset = mMovableObject->transform.position - mPlayerController->transform.position;

	if (mPlayerController->mCurrentAxis == ePlayerAxis::X)
	{
		if (mInitOffset.x > 0)
		{
			MoveToLeft();
		}
		else
		{
			MoveToRight();
		}
	}
	else
	{
		if (mInitOffset.z > 0)
		{
			MoveToRight();
		}
		else
		{
			MoveToLeft();
		}
	}

	mObjectOffset = mPlayerController->transform.position - mMovableObject->transform.position;

	mPlayerController->PlayAnimation("Push");


}

void Player::ObjectMoveState::Update()
{
	if (!HandleInput())
	{
		mPlayerController->velocity = glm::vec3(0);
		mPlayerController->mIsPlaying = false;
		return;
	}

	HandleMovement();
	HandleAnimation();

	mMovableObject->transform.position = mPlayerController->transform.position - mObjectOffset;

	mPlayerController->mIsPlaying = true;
}

void Player::ObjectMoveState::Render()
{
}

void Player::ObjectMoveState::Cleanup()
{
	mPlayerController->transform.position.x = mMovableObject->transform.position.x -  mInitOffset.x;
	mPlayerController->transform.position.z = mMovableObject->transform.position.z - mInitOffset.z;
	mPlayerController->mIsPlaying = true;
	mCurrentAnim = ePushPullAnim::NONE;
}

void Player::ObjectMoveState::MoveToLeft()
{
	glm::vec3 movePos = mMovableObject->GetLeftPosition();
	movePos.y = mPlayerController->transform.position.y;
	mPlayerController->transform.position = movePos;
	mIsLeft = true;
	HandleRotation();

}

void Player::ObjectMoveState::MoveToRight()
{
	glm::vec3 movePos = mMovableObject->GetRightPosition();
	movePos.y = mPlayerController->transform.position.y;
	mPlayerController->transform.position = movePos;
	mIsLeft = false;
	HandleRotation();
}

bool Player::ObjectMoveState::HandleInput()
{
	mPlayerController->mMoveDir = InputManager::GetInstance().GetAxisX();

	if (mPlayerController->mMoveDir == 0)
	{
		return false;
	}

	return true;
}

void Player::ObjectMoveState::HandleMovement()
{
	glm::vec3 mCameraRight = GetMainCamera()->transform.GetRight();

	glm::vec3 dir = mPlayerController->mCurrentAxis == ePlayerAxis::X ? glm::vec3(mCameraRight.x, 0, 0) :
		glm::vec3(0, 0, mCameraRight.z);

	dir = glm::normalize(dir);
	dir *= mPlayerController->mMoveDir;

	mPlayerController->velocity = dir
		* mPlayerController->mPlayerData.pushPullSpeed * 100.0f * Timer::GetInstance().deltaTime;
}

void Player::ObjectMoveState::HandleRotation()
{
	mPlayerController->mPlayerFaceDir = mIsLeft ? 1 : -1;
	mPlayerController->mPlayerFaceDir *= mPlayerController->mCameraController->mFlipCamera ? -1 : 1;


	float rotationY = mPlayerController->mCurrentAxis == ePlayerAxis::X ?
		mPlayerController->mPlayerFaceDir == 1 ? 89 : -89 :
		mPlayerController->mPlayerFaceDir == 1 ? 0 : 180;

	glm::vec3 newRotation = glm::vec3(0, rotationY, 0);

	mPlayerController->transform.SetRotation(newRotation);
}

void Player::ObjectMoveState::HandleAnimation()
{
	if (mIsLeft)
	{
		if (mPlayerController->mMoveDir > 0)
		{
			if (mCurrentAnim == ePushPullAnim::PUSH) return;

			mPlayerController->PlayAnimation(mPushAnim);
			mCurrentAnim = ePushPullAnim::PUSH;
		}
		else
		{
			if (mCurrentAnim == ePushPullAnim::PULL) return;

			mPlayerController->PlayAnimation(mPullAnim);
			mCurrentAnim = ePushPullAnim::PULL;
		}
		
	}
	else
	{
		if (mPlayerController->mMoveDir > 0)
		{
			if (mCurrentAnim == ePushPullAnim::PULL) return;
			mPlayerController->PlayAnimation(mPullAnim);
			mCurrentAnim = ePushPullAnim::PULL;
		}
		else
		{
			if (mCurrentAnim == ePushPullAnim::PUSH) return;

			mPlayerController->PlayAnimation(mPushAnim);
			mCurrentAnim = ePushPullAnim::PUSH;
		}
	}
}

