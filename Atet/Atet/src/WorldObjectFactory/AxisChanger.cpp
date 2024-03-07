#include <Graphics/Panels/ImguiDrawUtils.h>

#include "AxisChanger.h"

AxisChanger::AxisChanger(const std::string path, bool addToEntity) 
	: BaseWorldObject(path, addToEntity)
{
	userData = this;
	tag = "AxisChanger";
}

void AxisChanger::OnPropertyDraw()
{
	PhysicsObject::OnPropertyDraw();

	if (!ImGui::TreeNodeEx("AxisChanger", ImGuiTreeNodeFlags_DefaultOpen))
	{
		return;
	}

	DrawBoolArray("CameraFlips", &mCameraFlips[0]);
	DrawBoolArray("PlayerFlips", &mPlayerFlips[0]);

	ImGui::TreePop();

}

bool AxisChanger::GetCameraFlip()
{
	return mUsed ? mCameraFlips[1] : mCameraFlips[0];
}

bool AxisChanger::GetPlayerFlip()
{
	return mUsed ? mPlayerFlips[1] : mPlayerFlips[0];
}

void AxisChanger::DrawBoolArray(std::string label, bool* mArray)
{
	if (!ImGui::TreeNodeEx(label.c_str(), ImGuiTreeNodeFlags_DefaultOpen))
	{
		return;
	}

	std::string localLabel = label + "_"; 

	ImGuiUtils::DrawBool((localLabel + std::to_string(1)).c_str(), mArray[0]);
	ImGuiUtils::DrawBool((localLabel + std::to_string(2)).c_str(), mArray[1]);

	ImGui::TreePop();
}
