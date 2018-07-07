#include "Framebuffer.h"

Framebuffer::Framebuffer(const std::shared_ptr<Texture>& colorTex,
		const std::shared_ptr<Texture>& depthTex)
{

	colorTexture = colorTex;
	depthTexture = depthTex;

	glGenFramebuffers(1, &idFramebuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, idFramebuffer);

	if (colorTexture)
	{
		glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, colorTexture->getId(), 0);
		glDrawBuffer(GL_COLOR_ATTACHMENT0);
	}

	if (depthTexture)
	{
		glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, depthTexture->getId(), 0);
		glDrawBuffer(GL_NONE);
	}

	
}

Framebuffer::~Framebuffer()
{
	colorTexture = nullptr;
	depthTexture = nullptr;

	glDeleteFramebuffers(1, &idFramebuffer);
}

const std::shared_ptr<Texture>& Framebuffer::getColorTexture() const
{
	return colorTexture;
}

const std::shared_ptr<Texture>& Framebuffer::getDepthTexture() const
{
	return depthTexture;
}

void Framebuffer::bind() const
{
	glBindFramebuffer(GL_FRAMEBUFFER, idFramebuffer);

	if (colorTexture == nullptr)
		glDrawBuffer(GL_NONE);
	else
		glDrawBuffer(GL_COLOR_ATTACHMENT0);

	
	//glDrawBuffer(GL_NONE);
	//glReadBuffer(GL_NONE);
}

void Framebuffer::bindScreen()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}