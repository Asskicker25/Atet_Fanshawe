#include "RenderTexture.h"

RenderTexture::RenderTexture()
{
}

void RenderTexture::InitializeRenderTexture(FrameBufferSpecification specs)
{
	mFrameBuffer = new FrameBuffer(specs);
}
