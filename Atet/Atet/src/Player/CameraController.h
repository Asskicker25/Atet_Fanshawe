#pragma once

#include <Graphics/EntityManager/EntityManager.h>
#include <Graphics/Camera/CameraSystem.h>


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

		bool mFlipCamera = false;

	private:

		inline Camera* GetMainCamera() const { return CameraSystem::GetInstance().GetMainCamera(); }

		void HandlePosition(float dt);
		void HandleRotation(float dt);

		float mTimeStep = 0;
		float mDistance = 7;
		float mPosLerpSpeed = 8;
		float mRotLerpSpeed = 100;
		float mColumnWidth = 150;

		glm::vec3 mCameraPos;
		glm::vec3 mCameraDir;
		glm::vec3 mFollowOffset = glm::vec3(0,3.5f,0);
		glm::vec3 mLookAtOffset = glm::vec3(0,1.3f,0);
		glm::vec3 mCameraRight;

		PlayerController* mPlayer = nullptr;

	};

}


