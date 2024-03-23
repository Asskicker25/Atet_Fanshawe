#include <Graphics/Panels/ImguiDrawUtils.h>

#include "PlayerController.h"
#include "../JSON/JSON.h"
#include "States/IdleState.h"
#include "States/RunState.h"
#include "States/AxisChangeState.h"
#include "States/CollisionState.h"
#include "States/DeathState.h"
#include "States/CheckForMoveObjectState.h"
#include "States/ObjectMoveState.h"
#include "../Lua/Command/CommandManager.h"

using namespace Player;

PlayerController::PlayerController()
{
	JSON::ReadPlayerData("Assets/JsonConfig/PlayerData.json", mPlayerData);


	name = "PlayerController";
	userData = this;

	LoadModel(mPlayerData.modelPath);

	shader = Renderer::GetInstance().skeletalAnimShader;

	transform.SetRotation(glm::vec3(0, 90, 0));
	transform.SetScale(glm::vec3(0.01));

	InitializePhysics(AABB, DYNAMIC, TRIGGER, true);

	AddState(ePlayerState::IDLE, new IdleState());
	AddState(ePlayerState::RUN, new RunState());
	AddState(ePlayerState::DEATH, new DeathState());
	AddState(ePlayerState::AXIS_CHANGE, new AxisChangeState());
	AddState(ePlayerState::OBJECT_MOVE, new ObjectMoveState());
		
	AddAlwaysState(new CollisionState());
	AddAlwaysState(new CheckForMoveObjectState());

	LoadAndAddAnimationClip("Assets/Animation/Player_Run.fbx", "Run");
	LoadAndAddAnimationClip("Assets/Animation/Player_Death.fbx", "Death", false);
	LoadAndAddAnimationClip("Assets/Animation/Player_Idle.fbx", "Idle");
	LoadAndAddAnimationClip("Assets/Animation/Player_Push.fbx", "Push");
	LoadAndAddAnimationClip("Assets/Animation/Player_Pull.fbx", "Pull");

	mIsPlaying = true;


	mCameraController = new CameraController(this);

	mPlayerHealthManager.Intialize(modelId);
	system("cls");

	printf("Current Lives : %u\n", mPlayerHealthManager.GetPlayerHealthCount());


	//int health = mPlayerHealthManager.GetPlayerHealthCount();

}

void Player::PlayerController::AddState(ePlayerState stateType, BaseState* state)
{
	mListOfStates[stateType] = state;
	state->mPlayerController = this;
}

void Player::PlayerController::AddAlwaysState(BaseState* state)
{
	mListOfAlwaysStates.push_back(state);

	state->mPlayerController = this;
	state->Start();
}

void Player::PlayerController::RemoveState(ePlayerState state)
{
	mListOfStates.erase(state);
}

void Player::PlayerController::ChangeState(ePlayerState state)
{
	/*if (mCurrentState != state)
	{
	}*/
	GetCurrentState()->Cleanup();

	mCurrentState = state;
	mCurrentStateInt = (int)mCurrentState;

	GetCurrentState()->Start();


}

BaseState* Player::PlayerController::GetState(ePlayerState state)
{
	return mListOfStates[state];
}

BaseState* Player::PlayerController::GetCurrentState()
{
	return mListOfStates[mCurrentState];
}

void Player::PlayerController::Start()
{
	GetCurrentState()->Start();
}

void Player::PlayerController::Update(float deltaTime)
{
	PhysicsSkeletonObject::Update(deltaTime);

	if (mDead) return;

	GetCurrentState()->Update();

	for (BaseState* state : mListOfAlwaysStates)
	{
		state->Update();
	}
}

void Player::PlayerController::Render()
{
	GetCurrentState()->Render();
	for (BaseState* state : mListOfAlwaysStates)
	{
		state->Render();
	}
}

void Player::PlayerController::OnPropertyDraw()
{
	Model::OnPropertyDraw();

	ImGui::Checkbox("###PlayerControllerEnabled", &isEnabled);
	ImGui::SameLine();
	if (!ImGui::TreeNodeEx("PlayerController", ImGuiTreeNodeFlags_DefaultOpen))
	{
		return;
	}

	if (ImGuiUtils::DrawDropDown("State", mCurrentStateInt, stateStrings, 5))
	{
		ChangeState((ePlayerState)mCurrentStateInt);
	}

	if (ImGuiUtils::DrawDropDown("Axis", mCurrentAxisInt, axisStrings, 2))
	{
		mCurrentAxis = (ePlayerAxis)mCurrentAxisInt;
	}

	ImGuiUtils::DrawFloat("FaceDir", mPlayerFaceDir);
	ImGuiUtils::DrawFloat("MoveDir", mMoveDir);
	ImGuiUtils::DrawFloat("RotLerpSpeed", mRotLerpSpeed);

	ImGui::TreePop();
}

void Player::PlayerController::ChangeAxis(ePlayerAxis axis)
{
	mCurrentAxis = axis;
	mCurrentAxisInt = (int)mCurrentAxis;
}

void Player::PlayerController::AddMovableObject(MovableObject* object)
{
	mListOfMovableObjects.push_back(object);
}

void Player::PlayerController::Kill()
{
	mDead = true;
	isPhysicsEnabled = false;

	if (!CommandManager::GetInstance().GetLastCommandGroup()->isCollisionTrigger)
	{
		std::cout << "inside Collision Trigger" << std::endl;
		CommandManager::GetInstance().GetCommandGroupIndex(1)->isCollisionTrigger = true;
	}
}

