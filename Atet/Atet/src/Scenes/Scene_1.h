#pragma once

#include <Graphics/Scene/SceneManager.h>
#include <Graphics/ApplicationWindow.h>

using namespace Scene;

class Scene_1 : public BaseScene
{
	// Inherited via BaseScene
	void Start() override;
	void Update() override;
	void Render() override;
};

