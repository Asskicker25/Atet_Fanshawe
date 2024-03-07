#include "DeathState.h"
#include "../PlayerController.h"

void Player::DeathState::Start()
{
	mPlayerController->PlayAnimation("Death");
	mPlayerController->Kill();
}

void Player::DeathState::Update()
{
}

void Player::DeathState::Render()
{
}

void Player::DeathState::Cleanup()
{
}
