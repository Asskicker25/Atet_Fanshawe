#include "BaseWorldAnimatedObject.h"

BaseWorldAnimatedObject::BaseWorldAnimatedObject(const std::string& modelPath, bool addToEntity)
{
	LoadModel(modelPath, !addToEntity);
}
