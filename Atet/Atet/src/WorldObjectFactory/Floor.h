#pragma once

#include "BaseWorldObject.h"

class Floor :public BaseWorldObject
{
public:

	Floor() = default;
	Floor(const std::string& modelPath, bool addToEntity = true) : BaseWorldObject(modelPath, addToEntity) {};

};

