#include "IdleState.h"

Player::IdleState::IdleState()
{
	InputManager::GetInstance().AddListener(this);
}

void Player::IdleState::Start()
{
}

void Player::IdleState::Update()
{
}

void Player::IdleState::Render()
{
}

void Player::IdleState::Cleanup()
{
}

void Player::IdleState::OnKeyPressed(const int& key)
{
	if (key == GLFW_KEY_SPACE)
	{
		ChangeState(ePlayerState::RUN);
	}
}

void Player::IdleState::OnKeyReleased(const int& key)
{
}

void Player::IdleState::OnKeyHeld(const int& key)
{
	if (key == GLFW_KEY_A || key == GLFW_KEY_D)
	{
		ChangeState(ePlayerState::RUN);
	}
}
