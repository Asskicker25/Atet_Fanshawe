#pragma once

#include <Animation/PhysicsSkeletonObject.h>

class BaseWorldAnimatedObject : public PhysicsSkeletonObject
{
public:

	virtual ~BaseWorldAnimatedObject() {};

	BaseWorldAnimatedObject() = default;
	BaseWorldAnimatedObject(const std::string& modelPath, bool addToEntity = true);
};

