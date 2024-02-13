#pragma once

#include <Graphics/InputManager/InputManager.h>

#include "BaseState.h"

namespace Player
{
	class RunState : public BaseState, public iInputListener
	{
	public:

		RunState();

		// Inherited via BaseState
		void Start() override;
		void Update() override;
		void Render() override;
		void Cleanup() override;

		// Inherited via iInputListener
		void OnKeyPressed(const int& key) override;
		void OnKeyReleased(const int& key) override;
		void OnKeyHeld(const int& key) override;
	};
}


