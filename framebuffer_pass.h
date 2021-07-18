#ifndef FRAMEBUFFERPASS_H
#define FRAMEBUFFERPASS_H

#include "render_pass.h"
#include "shader.h"

#include <memory>
class Shader;
class Framebuffer;

class FramebufferPass : public RenderPass
{
public:
	FramebufferPass();
	virtual ~FramebufferPass();

	void render()const override;
	void draw_on(Framebuffer&)const;

private:
	static std::unique_ptr<Shader> singleton_vertex_shader;
	static unsigned int count;
	static GLuint vao;
	static GLuint vbo;
};

#endif // FRAMEBUFFERPASS_H
