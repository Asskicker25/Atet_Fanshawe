#pragma once
#include <Graphics/Debugger.h>
#include "ePlayerState.h"

namespace Player
{
	class PlayerController;
	//enum class ePlayerState;

	class BaseState
	{
	public:
		
		virtual void Start() = 0;
		virtual void Update() = 0;
		virtual void Render() = 0;
		virtual void Cleanup() = 0;
		
		void ChangeState(ePlayerState state);

		PlayerController* mPlayerController = nullptr;
	};
}

