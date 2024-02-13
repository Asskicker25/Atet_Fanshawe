#include "Atet_Application.h"
#include "Scenes/Scene_1.h"

void Atet_Application::SetUp()
{
	viewportCamera->InitializeCamera(PERSPECTIVE, windowWidth, windowHeight, 0.1f, 100.0f, 45.0f);

	viewportCamera->transform.SetPosition(glm::vec3(0, 20, 7));
	viewportCamera->transform.SetRotation(glm::vec3(-55, 0, 0));

	Renderer::GetInstance().renderMode = SHADED;

	imGuiPanelEnable = true;

	BaseScene* scene_1 = new Scene_1();

	SceneManager::GetInstance().AddScene("Scene_1", scene_1);

	SceneManager::GetInstance().ChangeScene("Scene_1");

}

void Atet_Application::Update()
{
	if (applicationPlay)
	{
		PhysicsEngine::GetInstance().Update(Timer::GetInstance().deltaTime);
	}
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
