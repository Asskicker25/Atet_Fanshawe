#include "BaseState.h"
#include "ePlayerState.h"
#include "../PlayerController.h"

using namespace Player;

void BaseState::ChangeState(ePlayerState state)
{
	mPlayerController->ChangeState(state);
}
