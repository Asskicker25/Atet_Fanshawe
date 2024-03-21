#pragma once
#include "BaseState.h"
#include <Graphics/Camera/CameraSystem.h>

class MovableObject;

namespace Player
{
	class ObjectMoveState : public BaseState
	{
	public:
		// Inherited via BaseState
		void Start() override;
		void Update() override;
		void Render() override;
		void Cleanup() override;

		MovableObject* mMovableObject = nullptr;

	private:

		enum class ePushPullAnim
		{
			NONE = 0,
			PUSH = 1,
			PULL = 2
		};

		void MoveToLeft();
		void MoveToRight();

		bool HandleInput();
		void HandleMovement();
		void HandleRotation();
		void HandleAnimation();

		bool mIsLeft = false;
		ePushPullAnim mCurrentAnim = ePushPullAnim::NONE;

		const std::string mPullAnim = "Pull";
		const std::string mPushAnim = "Push";

		glm::vec3 mInitOffset = glm::vec3(0);
		glm::vec3 mObjectOffset = glm::vec3(0);

		inline Camera* GetMainCamera() const { return CameraSystem::GetInstance().GetMainCamera(); }
	};
}
