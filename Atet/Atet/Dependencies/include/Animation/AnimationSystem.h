#pragma once
#include <vector>
#include <functional>
#include "AnimatedObject.h"
#include "AnimationSequence.h"

class AnimationSystem : public Entity
{

public:
	AnimationSystem();

	static AnimationSystem& GetInstance();

	void Initialize();

	void AddAnimatedObject(BaseAnimationHelper* animObject);
	void RemoveAnimatedObject(BaseAnimationHelper* animObject);
	void UpdateAnimations(float deltaTime);
	void TogglePlayAndPause();

	glm::vec3 HandleKeyFrames_Vector3(double time, std::vector<BaseKeyFrame<glm::vec3>>& keyFrames,
		std::function<void(glm::vec3)> OnValueApply = nullptr, std::function<void(glm::vec4)>OnColorChange = nullptr);

	glm::quat HandleKeyFrames_Quaternion(double time, std::vector<BaseKeyFrame<glm::vec3>>& keyFrames,
		std::function<void(glm::quat)> OnValueApply = nullptr, std::function<void(glm::vec4)>OnColorChange = nullptr);

	//AnimationSequence* currentSequence = nullptr;

	float animationSpeed = 1;
	float currentTime = 0;

private:

	void HandleAnimation(BaseAnimationHelper* animObject);
	void HandleEventInvoke(BaseAnimationHelper* animObject);

	

	std::vector<BaseAnimationHelper*> listOfAnimatedObjects;
	
	bool isPlaying = false;

	// Inherited via Entity
	void Start() override;
	void Update(float deltaTime) override;
	void OnDestroy() override;

	// Inherited via Entity
	void Render() override;
};

