#include "CheckForMoveObjectState.h"
#include "../PlayerController.h"
#include "../../WorldObjectFactory/MovableObject.h"

void Player::CheckForMoveObjectState::Start()
{
	InputManager::GetInstance().AddListener(this);
}

void Player::CheckForMoveObjectState::Update()
{
	if (mPlayerToMoveObject) return;

	for (MovableObject* obj : mPlayerController->mListOfMovableObjects)
	{
		if (IsPlayerNearObject(obj))
		{
			if (mMoveInputPressed)
			{
				mPlayerController->mCurrentMovableObject = obj;
				mPlayerController->ChangeState(ePlayerState::OBJECT_MOVE);

				mPlayerToMoveObject = true;
				return;
			}
			
		}
	}

	mMoveInputPressed = false;
}

void Player::CheckForMoveObjectState::Render()
{
}

void Player::CheckForMoveObjectState::Cleanup()
{
}

void Player::CheckForMoveObjectState::OnKeyPressed(const int& key)
{
	if (key == GLFW_KEY_LEFT_CONTROL)
	{
		mMoveInputPressed = true;
	}
}

void Player::CheckForMoveObjectState::OnKeyReleased(const int& key)
{
	if (key == GLFW_KEY_LEFT_CONTROL)
	{
		mMoveInputPressed = false;
		mPlayerToMoveObject = false;

		if (mPlayerController->mCurrentState == ePlayerState::OBJECT_MOVE)
		{
			mPlayerController->ChangeState(ePlayerState::IDLE);
		}
	}
}

bool Player::CheckForMoveObjectState::IsPlayerNearObject(MovableObject* object)
{
	glm::vec3 diff = object->transform.position - mPlayerController->transform.position;
	float sqDist = glm::dot(diff, diff);

	if (sqDist < mPlayerController->mInteractDistance * mPlayerController->mInteractDistance)
	{
		return true;
	}

	return false;
}
