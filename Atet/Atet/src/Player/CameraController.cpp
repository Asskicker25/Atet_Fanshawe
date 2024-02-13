#include <Graphics/Panels/ImguiDrawUtils.h>
#include <Graphics/MathUtils.h>

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
	HandlePosition(deltaTime);
	HandleRotation(deltaTime);
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

	ImGuiUtils::DrawFloat("Distance", mDistance);
	ImGuiUtils::DrawFloat("LerpSpeed", mLerpSpeed);
	ImGuiUtils::DrawVector3ImGui("Offset", mOffset, 0, mColumnWidth);

	ImGui::TreePop();
}

void Player::CameraController::HandlePosition(float dt)
{
	mCameraPos = mPlayer->transform.position -  mPlayer->transform.GetRight() * mDistance * mPlayer->mPlayerFaceDir;
	mCameraPos += mOffset;
	mCameraPos = MathUtils::Lerp(GetMainCamera()->transform.position, mCameraPos, dt * mLerpSpeed);

	GetMainCamera()->transform.SetPosition(mCameraPos);
}

void Player::CameraController::HandleRotation(float dt)
{
}
