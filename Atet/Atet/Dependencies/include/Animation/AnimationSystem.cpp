#include "AnimationSystem.h"
#include <glm/gtx/easing.hpp>


AnimationSystem::AnimationSystem()
{
	InitializeEntity(this);

	name = "AnimationSystem";
}

AnimationSystem& AnimationSystem::GetInstance()
{
	static AnimationSystem instance;
	return instance;
}

void AnimationSystem::Initialize()
{
}

void AnimationSystem::AddAnimatedObject(BaseAnimationHelper* animObject)
{
	listOfAnimatedObjects.push_back(animObject);
}

void AnimationSystem::RemoveAnimatedObject(BaseAnimationHelper* animObject)
{
	listOfAnimatedObjects.erase(std::remove(listOfAnimatedObjects.begin(),
		listOfAnimatedObjects.end(), animObject), listOfAnimatedObjects.end());
}

void AnimationSystem::Start()
{
}

void AnimationSystem::Update(float deltaTime)
{
	UpdateAnimations(deltaTime);
}

void AnimationSystem::OnDestroy()
{
}

void AnimationSystem::Render()
{
}

void AnimationSystem::UpdateAnimations(float deltaTime)
{
	if (!isPlaying) return;

	currentTime += deltaTime;

	//if (currentSequence == nullptr) return;

	//currentSequence->CalculateTime(deltaTime * animationSpeed);

	for (BaseAnimationHelper* animObject : listOfAnimatedObjects)
	{
		if (!animObject->IsAnimationAvailable() || !animObject->canAnimate 
			|| animObject->GetCurrentAnimationClip() == nullptr) continue;

		animObject->GetCurrentAnimationClip()->time = currentTime;
		HandleAnimation(animObject);
		HandleEventInvoke(animObject);
	}
}

void AnimationSystem::TogglePlayAndPause()
{
	isPlaying = !isPlaying;
}

void AnimationSystem::HandleAnimation(BaseAnimationHelper* animObject)
{
	AnimationClip* animationClip = animObject->GetCurrentAnimationClip();

	HandleKeyFrames_Vector3(animationClip->time, animationClip->listOfPositionKeyFrames, [animObject](glm::vec3 value)
		{
			animObject->SetAnimatedPosition(value);
		}, 

		[animObject](glm::vec4 color)
		{
			if (animObject->showEasingColor)
			{
				animObject->SetBaseColor(color);
			}
		});
	HandleKeyFrames_Quaternion(animationClip->time, animationClip->listOfRotationKeyFrames, [animObject](glm::quat value)
		{
			animObject->SetAnimatedRotation(value);
		});

	HandleKeyFrames_Vector3(animationClip->time, animationClip->listOfScaleKeyFrames, [animObject](glm::vec3 value)
		{
			animObject->SetAnimatedScale(value);
		});
}

void AnimationSystem::HandleEventInvoke(BaseAnimationHelper* animObject)
{
	/*AnimationClip* clip = animObject->GetCurrentAnimationClip();

	for (KeyFrameEvent* keyFrameEvent : clip->listOfKeyFrameEvents)
	{
		if (keyFrameEvent->isEventTriggered) continue;

		switch (currentSequence->sequenceState)
		{
		case NORMAL:

			if (clip->time >= keyFrameEvent->eventTime)
			{
				if(keyFrameEvent->OnEventTrigger != nullptr) { keyFrameEvent->OnEventTrigger(); }

				keyFrameEvent->isEventTriggered = true;
			}

			break;
		case REVERSE:

			if (clip->time <= keyFrameEvent->eventTime)
			{
				if (keyFrameEvent->OnEventTrigger != nullptr) { keyFrameEvent->OnEventTrigger(); }
				keyFrameEvent->isEventTriggered = true;
			}

			break;
		}
	}*/
}

glm::vec3 AnimationSystem::HandleKeyFrames_Vector3(double time, std::vector<BaseKeyFrame<glm::vec3>>& keyFrames, 
	std::function<void(glm::vec3)> OnValueApply, std::function<void(glm::vec4)>OnColorChange)
{
	if (keyFrames.size() == 0) return glm::vec3(0);

	if (keyFrames.size() == 1)
	{
		if (OnValueApply != nullptr)
		{
			OnValueApply(keyFrames[0].mValue);
		}

		if (OnColorChange != nullptr) { OnColorChange(glm::vec4(1)); }

		return keyFrames[0].mValue;
	}

	int keyFrameEndIndex = 0;
	for (; keyFrameEndIndex < keyFrames.size(); keyFrameEndIndex++)
	{
		if (keyFrames[keyFrameEndIndex].mTime > time)
		{
			break;
		}
	}

	if (keyFrameEndIndex >= keyFrames.size())
	{
		if (OnValueApply != nullptr)
		{
			OnValueApply(keyFrames[keyFrameEndIndex - 1].mValue);
		}

		if (OnColorChange != nullptr) { OnColorChange(glm::vec4(1)); }
		return keyFrames[keyFrameEndIndex - 1].mValue;
	}

	int keyFrameStartIndex = keyFrameEndIndex - 1;

	BaseKeyFrame<glm::vec3> startKeyFrame = keyFrames[keyFrameStartIndex];
	BaseKeyFrame<glm::vec3> endKeyFrame = keyFrames[keyFrameEndIndex];

	float percent = (time - startKeyFrame.mTime) / (endKeyFrame.mTime - startKeyFrame.mTime);

	float result = 0.0f;

	switch (endKeyFrame.mEasingType)
	{
	case EasingType::Linear:
		result = percent;

		if (OnColorChange != nullptr) { OnColorChange(glm::vec4(1)); }

		break;

	case EasingType::SineEaseIn:
		result = glm::sineEaseIn(percent);

		if (OnColorChange != nullptr) { OnColorChange(glm::vec4(0.7f, 0, 0, 1)); }
		
		break;

	case EasingType::SineEaseOut: 
		result = glm::sineEaseOut(percent);

		if (OnColorChange != nullptr) { OnColorChange(glm::vec4(1.0f, 1.0f, 0, 1)); }
		
		break;

	case EasingType::SineEaseInOut:
		result = glm::sineEaseInOut(percent);
		if (OnColorChange != nullptr) { OnColorChange(glm::vec4(0, 0.7f, 0, 1)); }
	
		break;

	}

	glm::vec3 delta = endKeyFrame.mValue - startKeyFrame.mValue;

	glm::vec3 endValue = startKeyFrame.mValue + delta * result;

	if (OnValueApply != nullptr)
	{
		OnValueApply(endValue);
	}
	
	return endValue;

}

glm::quat AnimationSystem::HandleKeyFrames_Quaternion(double time, std::vector<BaseKeyFrame<glm::vec3>>& keyFrames,
	std::function<void(glm::quat)> OnValueApply, std::function<void(glm::vec4)>OnColorChange)
{
	if (keyFrames.size() == 0) return glm::quat(glm::radians(glm::vec3(0)));

	if (keyFrames.size() == 1)
	{
		glm::quat quaternionRotation = glm::quat(glm::radians(keyFrames[0].mValue));

		if (OnValueApply != nullptr)
		{
			OnValueApply(quaternionRotation);
		}
		
		return quaternionRotation;
	}

	int keyFrameEndIndex = 0;
	for (; keyFrameEndIndex < keyFrames.size(); keyFrameEndIndex++)
	{
		if (keyFrames[keyFrameEndIndex].mTime > time)
		{
			break;
		}
	}

	if (keyFrameEndIndex >= keyFrames.size())
	{
		glm::quat quaternionRotation = glm::quat(glm::radians(keyFrames[keyFrameEndIndex - 1].mValue));


		if (OnValueApply != nullptr)
		{
			OnValueApply(quaternionRotation);
		}
		return quaternionRotation;
	}

	int keyFrameStartIndex = keyFrameEndIndex - 1;

	BaseKeyFrame<glm::vec3> startKeyFrame = keyFrames[keyFrameStartIndex];
	BaseKeyFrame<glm::vec3> endKeyFrame = keyFrames[keyFrameEndIndex];

	float percent = (time - startKeyFrame.mTime) / (endKeyFrame.mTime - startKeyFrame.mTime);

	float result = 0.0f;

	switch (endKeyFrame.mEasingType)
	{
	case EasingType::Linear:
		result = percent;

		break;

	case EasingType::SineEaseIn:
		result = glm::sineEaseIn(percent);
		break;

	case EasingType::SineEaseOut:
		result = glm::sineEaseOut(percent);
		break;

	case EasingType::SineEaseInOut:
		result = glm::sineEaseInOut(percent);
		break;

	}

	glm::quat startRotation = glm::quat(glm::radians(startKeyFrame.mValue));
	glm::quat endRotation = glm::quat(glm::radians(endKeyFrame.mValue));

	glm::quat quaternionRotation = glm::slerp(startRotation, endRotation, result);
	
	if (OnValueApply != nullptr)
	{
		OnValueApply(quaternionRotation);
	}

	return quaternionRotation;
}


