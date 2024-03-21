#pragma once
#include "BaseState.h"
#include <Graphics/InputManager/InputManager.h>

class MovableObject;

namespace Player
{
	class CheckForMoveObjectState : public BaseState, public iInputListener
	{
	public:
		// Inherited via BaseState
		void Start() override;
		void Update() override;
		void Render() override;
		void Cleanup() override;


		virtual void OnKeyPressed(const int& key);
		virtual void OnKeyReleased(const int& key);

		bool mMoveInputPressed = false;
		bool mPlayerToMoveObject = false;

	private:
		bool IsPlayerNearObject(MovableObject* object);
	};

}
	
