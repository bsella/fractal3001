#ifndef FRAMEBUFFERPASS_H
#define FRAMEBUFFERPASS_H

#include "render_pass.h"
#include "shader.h"

#include <memory>
class Shader;

class FullscreenPass : public RenderPass
{
public:
	FullscreenPass();
	virtual ~FullscreenPass();

	void render()const override;

private:
	static std::unique_ptr<Shader> singleton_vertex_shader;
	static unsigned int count;
	static GLuint vao;
	static GLuint vbo;
};

#endif // FRAMEBUFFERPASS_H
