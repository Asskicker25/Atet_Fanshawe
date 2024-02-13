#pragma once

#include <Graphics/Model.h>

#include "States/ePlayerState.h"
#include "PlayerData.h"
#include "States/BaseState.h"
#include "CameraController.h"

namespace Player
{
	class PlayerController : public Model
	{
	public:

		PlayerController();

		void AddState(ePlayerState stateType, BaseState* state);
		void RemoveState(ePlayerState state);
		void ChangeState(ePlayerState state);

		BaseState* GetState(ePlayerState state);
		BaseState* GetCurrentState();

		void Update(float deltaTime) override;
		void Render() override;
		void OnPropertyDraw() override;

		float mPlayerFaceDir = 1;

	private:

		int mCurrentStateInt = 0;

		const char* stateStrings[2] = { "IDLE", "RUN" };

		PlayerData mPlayerData;
		ePlayerState mCurrentState = ePlayerState::IDLE;

		CameraController* mCameraController = nullptr;

		std::unordered_map<ePlayerState, BaseState*> mListOfStates;

	};

}

