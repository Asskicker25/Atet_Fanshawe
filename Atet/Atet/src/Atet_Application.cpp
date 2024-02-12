#include "Atet_Application.h"

#include"JSON/JSON.h"

void Atet_Application::SetUp()
{
	viewportCamera->InitializeCamera(PERSPECTIVE, windowWidth, windowHeight, 0.1f, 100.0f, 45.0f);

	viewportCamera->transform.SetPosition(glm::vec3(0, 0, 10));

	Renderer::GetInstance().renderMode = SHADED;

	imGuiPanelEnable = true;

	GameCamera* mainCamera = new GameCamera();
	mainCamera->InitializeCamera(PERSPECTIVE, gameResolutionWidth, gameResolutionHeight, 0.1f, 100.0f, 45.0f);
	mainCamera->transform.SetPosition(glm::vec3(0, 0, 10));


	Light* dirLight = new Light();
	dirLight->transform.SetScale(glm::vec3(0.1f));
	dirLight->transform.SetPosition(glm::vec3(0, 0, 3));
	dirLight->InitializeLight(Directional);

#pragma region JSON

	PlayerData playerData;
	playerData.lives = 1;
	playerData.modelPath = "Model/Player.fbx";
	playerData.speed = 10;

	JSON::WritePlayerData("res/JsonConfig/Playerdata.json", playerData);


	PlayerData newplayerData;
	JSON::ReadPlayerData("res/JsonConfig/Playerdata.json", newplayerData);

	std::cout << "Model path:" << newplayerData.modelPath << std::endl;
	std::cout << "lives:" << newplayerData.lives << std::endl;
	std::cout << "speed:" << newplayerData.speed << std::endl;
#pragma endregion

}

void Atet_Application::Update()
{
}

void Atet_Application::Render()
{
}

void Atet_Application::ProcessInput(GLFWwindow* window)
{
}

void Atet_Application::KeyCallBack(GLFWwindow* window, int& key, int& scancode, int& action, int& mods)
{
}

void Atet_Application::MouseButtonCallback(GLFWwindow* window, int& button, int& action, int& mods)
{
}
