#include <Graphics/Panels/ImguiDrawUtils.h>
#include <Graphics/MathUtils.h>
#include <Physics/PhysicsEngine.h>

#include "CameraController.h"
#include "../Player/PlayerController.h"

using namespace Player;
using namespace MathUtilities;

CameraController::CameraController(PlayerController* player)
{
	mPlayer = player;

	name = "Camera Controller";

	InitializeEntity(this);
}

void CameraController::Start()
{
}

void CameraController::Update(float deltaTime)
{
	mTimeStep += deltaTime;

	if (mTimeStep < PhysicsEngine::GetInstance().fixedStepTime) return;

	mTimeStep = 0;

	HandleRotation(deltaTime);
	HandlePosition(deltaTime);

	mCameraRight = GetMainCamera()->transform.GetRight();


}

void CameraController::Render()
{
}

void CameraController::OnDestroy()
{
}

void Player::CameraController::OnPropertyDraw()
{
	Entity::OnPropertyDraw();

	ImGui::Checkbox("###CameraControllerEnabled", &isEnabled);
	ImGui::SameLine();
	if (!ImGui::TreeNodeEx("CameraController", ImGuiTreeNodeFlags_DefaultOpen))
	{
		return;
	}

	ImGuiUtils::DrawBool("FlipCamera", mFlipCamera);
	ImGuiUtils::DrawFloat("Distance", mDistance);
	ImGuiUtils::DrawFloat("PosLerpSpeed", mPosLerpSpeed);
	ImGuiUtils::DrawFloat("RotLerpSpeed", mRotLerpSpeed);
	ImGuiUtils::DrawVector3ImGui("FollowOffset", mFollowOffset, 0, mColumnWidth);
	ImGuiUtils::DrawVector3ImGui("LookAtOffset", mLookAtOffset, 0, mColumnWidth);
	ImGuiUtils::DrawVector3ImGui("CameraRight", mCameraRight, 0, mColumnWidth);

	ImGui::TreePop();
}

void Player::CameraController::HandlePosition(float dt)
{
	float dir = mPlayer->mPlayerFaceDir * (mFlipCamera ? -1 : 1);

	mCameraPos = mPlayer->transform.position - mPlayer->transform.GetRight() * mDistance * dir;
	mCameraPos += mFollowOffset;
	mCameraPos = MathUtils::Lerp(GetMainCamera()->transform.position, mCameraPos, dt * mPosLerpSpeed);

	GetMainCamera()->transform.SetPosition(mCameraPos);
}

void Player::CameraController::HandleRotation(float dt)
{
	float dir = 1;

	mCameraDir = (mPlayer->transform.position + mLookAtOffset) - GetMainCamera()->transform.position;
	mCameraDir = glm::normalize(mCameraDir);

	glm::quat rotationQuat = glm::quatLookAt(mCameraDir * dir, glm::vec3(0, 1, 0));
	glm::quat rotation = glm::slerp(GetMainCamera()->transform.quaternionRotation, rotationQuat,
		glm::clamp(dt * mRotLerpSpeed, 0.0f, 1.0f));

	GetMainCamera()->transform.SetQuatRotation(rotation);
}
