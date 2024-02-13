#pragma once
#include <Graphics/Model.h>

class BaseWorldObject : public Model
{

public:

	virtual ~BaseWorldObject() {};

	BaseWorldObject() = default;
	BaseWorldObject(const std::string& modelPath, bool addToEntity = true);
};

