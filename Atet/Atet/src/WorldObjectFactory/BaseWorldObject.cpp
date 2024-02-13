#include "BaseWorldObject.h"

BaseWorldObject::BaseWorldObject(const std::string& modelPath, bool addToEntity)
{
	LoadModel(modelPath, !addToEntity);
}
