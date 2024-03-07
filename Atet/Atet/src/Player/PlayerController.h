#pragma once

#include <Physics/PhysicsObject.h>
#include <Animation/PhysicsSkeletonObject.h>

#include "ePlayerAxis.h"
#include "States/ePlayerState.h"
#include "PlayerData.h"
#include "States/BaseState.h"
#include "CameraController.h"
#include "../WorldObjectFactory/AxisChanger.h"


namespace Player
{
	class PlayerController : public PhysicsSkeletonObject
	{
	public:

		PlayerController();

		void AddState(ePlayerState stateType, BaseState* state);
		void AddAlwaysState(BaseState* state);
		void RemoveState(ePlayerState state);
		void ChangeState(ePlayerState state);

		BaseState* GetState(ePlayerState state);
		BaseState* GetCurrentState();

		void Start() override;
		void Update(float deltaTime) override;
		void Render() override;
		void OnPropertyDraw() override;

		void ChangeAxis(ePlayerAxis axis);

		void Kill();

		bool mDead = false;

		float mMoveDir = 0;
		float mPlayerFaceDir = 1;
		float mRotLerpSpeed = 10;

		PlayerData mPlayerData;

		ePlayerAxis mCurrentAxis = ePlayerAxis::X;
		ePlayerState mCurrentState = ePlayerState::IDLE;

		CameraController* mCameraController = nullptr;

		AxisChanger* mCurrentAxisChanger = nullptr;

	private:

		int mCurrentStateInt = 0;
		int mCurrentAxisInt = 0;


		const char* stateStrings[2] = { "IDLE", "RUN" };
		const char* axisStrings[2] = { "X", "Z" };
		
		std::vector<BaseState*> mListOfAlwaysStates;
		std::unordered_map<ePlayerState, BaseState*> mListOfStates;

	};

}

