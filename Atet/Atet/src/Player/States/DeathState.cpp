#include "DeathState.h"
#include "../PlayerController.h"

void Player::DeathState::Start()
{
	mPlayerController->PlayAnimation("Death");
	mPlayerController->Kill();
	mPlayerController->mPlayerHealthManager.SetPlayerHealth(mPlayerController->mPlayerHealthManager.GetPlayerHealthCount() - 1);
	printf("Player Live Reduced\n");
	printf("Current Lives : %u", mPlayerController->mPlayerHealthManager.GetPlayerHealthCount());

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
