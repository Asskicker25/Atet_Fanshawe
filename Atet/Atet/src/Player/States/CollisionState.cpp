#include <Graphics/Debugger.h>

#include "CollisionState.h"
#include "../PlayerController.h"
#include "../../WorldObjectFactory/AxisChanger.h"

void Player::CollisionState::Start()
{
	InputManager::GetInstance().AddListener(this);

	mPlayerController->AssignCollisionCallback([this](PhysicsObject* other)
		{
			if (mCanChangeAxis && !mAxisChanged)
			{
				mPlayerController->mCurrentAxisChanger = (AxisChanger*)other;
				ChangeAxis();
				mAxisChanged = true;
			}
		});
}

void Player::CollisionState::Update()
{
}

void Player::CollisionState::Render()
{
}

void Player::CollisionState::Cleanup()
{
}


void Player::CollisionState::OnKeyPressed(const int& key)
{
	if (key == GLFW_KEY_SPACE)
	{
		mCanChangeAxis = true;
	}
}

void Player::CollisionState::OnKeyReleased(const int& key)
{
	if (key == GLFW_KEY_SPACE)
	{
		mCanChangeAxis = false;
		mAxisChanged = false;
	}
}

void Player::CollisionState::OnKeyHeld(const int& key)
{

}

void Player::CollisionState::ChangeAxis()
{
	ChangeState(ePlayerState::AXIS_CHANGE);

}
