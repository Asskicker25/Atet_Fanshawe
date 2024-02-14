#pragma once

#include <Graphics/InputManager/InputManager.h>
#include "BaseState.h"

namespace Player
{
	class CollisionState : public BaseState, public iInputListener
	{

	public:
		// Inherited via BaseState
		void Start() override;
		void Update() override;
		void Render() override;
		void Cleanup() override;

		// Inherited via iInputListener
		void OnKeyPressed(const int& key) override;
		void OnKeyReleased(const int& key) override;
		void OnKeyHeld(const int& key) override;

	private:
		void ChangeAxis();

		bool mAxisChanged = false;
		bool mCanChangeAxis = false;
	};
}


