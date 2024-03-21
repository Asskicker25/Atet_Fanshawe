#pragma once
#include "BaseWorldObject.h"

class MovableObject : public BaseWorldObject
{
public:
	MovableObject() = default;
	MovableObject(const std::string& modelPath, bool addToEntity = true);

	virtual void OnPropertyDraw() override;
	virtual void Render();

	float mPosOffset = 0.8f;
	glm::vec3 GetLeftPosition();
	glm::vec3 GetRightPosition();

};

