#pragma once

#include <Graphics/EntityManager/EntityManager.h>
#include <Graphics/CameraSystem.h>


namespace Player
{
	class PlayerController;

	class CameraController : public Entity
	{
	public:
		CameraController(PlayerController* player);

		// Inherited via Entity
		void Start() override;
		void Update(float deltaTime) override;
		void Render() override;
		void OnDestroy() override;
		void OnPropertyDraw() override;

	private:

		inline Camera* GetMainCamera() const { return CameraSystem::GetInstance().GetMainCamera(); }

		void HandlePosition(float dt);
		void HandleRotation(float dt);


		float mDistance = 7;
		float mLerpSpeed = 10;
		float mColumnWidth = 150;

		glm::vec3 mCameraPos;
		glm::vec3 mOffset = glm::vec3(0,3.5f,0);

		PlayerController* mPlayer = nullptr;

	};

}


