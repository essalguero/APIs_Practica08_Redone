#pragma once

#include "Texture.h"
#include "Vertex.h"

#include <vector>
class Framebuffer
{
public:

	Framebuffer(const std::shared_ptr<Texture>& colorTex,
		const std::shared_ptr<Texture>& depthTex);
	~Framebuffer();
	const std::shared_ptr<Texture>& getColorTexture() const;
	const std::shared_ptr<Texture>& getDepthTexture() const;
	void bind() const;
	static void bindScreen();


private:

	std::shared_ptr<Texture> colorTexture;
	std::shared_ptr<Texture> depthTexture;

	GLuint idFramebuffer;
};