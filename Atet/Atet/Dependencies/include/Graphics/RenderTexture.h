#pragma once

#include "Debugger.h"
#include "FrameBuffer.h"

class RenderTexture
{
public:
	RenderTexture();

	void InitializeRenderTexture(FrameBufferSpecification specs);

	FrameBuffer* mFrameBuffer = nullptr;

};

