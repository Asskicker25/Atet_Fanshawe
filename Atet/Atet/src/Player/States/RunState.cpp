#include "RunState.h"

Player::RunState::RunState()
{
	InputManager::GetInstance().AddListener(this);
}

void Player::RunState::Start()
{
}

void Player::RunState::Update()
{
	Debugger::Print("Run");
}

void Player::RunState::Render()
{
}

void Player::RunState::Cleanup()
{
}

void Player::RunState::OnKeyPressed(const int& key)
{
}

void Player::RunState::OnKeyReleased(const int& key)
{
}

void Player::RunState::OnKeyHeld(const int& key)
{
}
