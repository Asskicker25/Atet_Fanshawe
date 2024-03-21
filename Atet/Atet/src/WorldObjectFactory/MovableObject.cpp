#include "MovableObject.h"
#include <Graphics/Panels/ImguiDrawUtils.h>

MovableObject::MovableObject(const std::string& modelPath, bool addToEntity)
	: BaseWorldObject(modelPath, addToEntity)
{

}

void MovableObject::OnPropertyDraw()
{
	Model::OnPropertyDraw();

	if (!ImGui::TreeNodeEx("MovableObject", ImGuiTreeNodeFlags_DefaultOpen))
	{
		return;
	}

	ImGuiUtils::DrawFloat("Offset", mPosOffset);

	ImGui::TreePop();
}

void MovableObject::Render()
{
	Renderer::GetInstance().DrawSphere(GetLeftPosition(), 0.1f, glm::vec4(1, 0, 0, 1));
	Renderer::GetInstance().DrawSphere(GetRightPosition(), 0.1f, glm::vec4(0, 0, 1, 1));
}

glm::vec3 MovableObject::GetLeftPosition()
{
	return transform.position - ( transform.GetRight() * mPosOffset);
}

glm::vec3 MovableObject::GetRightPosition()
{
	return transform.position + (transform.GetRight() * mPosOffset);
}
