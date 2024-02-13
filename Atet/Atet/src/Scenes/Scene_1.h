#pragma once

#include <Graphics/Scene/SceneManager.h>
#include <Graphics/ApplicationWindow.h>
#include "../WorldObjectFactory/WorldObjectFactory.h"

using namespace Scene;

class Scene_1 : public BaseScene
{
	// Inherited via BaseScene
	void Start() override;
	void Update() override;
	void Render() override;

private:

	WorldObjectFactory* m_Floor = new WorldObjectFactory();
};

