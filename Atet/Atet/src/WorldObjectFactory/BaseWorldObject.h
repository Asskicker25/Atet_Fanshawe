#pragma once
#include <Physics/PhysicsObject.h>

class BaseWorldObject : public PhysicsObject
{

public:

	virtual ~BaseWorldObject() {};

	BaseWorldObject() = default;
	BaseWorldObject(const std::string& modelPath, bool addToEntity = true);
};

