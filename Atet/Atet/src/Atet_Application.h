#pragma once

#include <Graphics/ApplicationWindow.h>
#include <Physics/PhysicsEngine.h>
#include "Sounds/AudioSource.h"
#include "Lua/LuaHandler.h"

class Atet_Application : public ApplicationWindow
{
	// Inherited via ApplicationWindow
	void SetUp() override;
	void Update() override;
	void Render() override;
	void ProcessInput(GLFWwindow* window) override;
	void KeyCallBack(GLFWwindow* window, int& key, int& scancode, int& action, int& mods) override;
	void MouseButtonCallback(GLFWwindow* window, int& button, int& action, int& mods) override;

	// Inherited via ApplicationWindow
	void Shutdown() override;
	void OnPlayStateChanged(bool state) override;

	LuaHandler* WorldLuaHandler;
};

