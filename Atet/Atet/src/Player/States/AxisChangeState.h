#pragma once
#include "BaseState.h"

namespace Player
{
	class AxisChangeState :	public BaseState
	{
	public:
		// Inherited via BaseState
		void Start() override;
		void Update() override;
		void Render() override;
		void Cleanup() override;
	};

}

