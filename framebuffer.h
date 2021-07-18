#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

#include <GL/glew.h>

class Framebuffer
{
public:
	Framebuffer(int w, int h);
	~Framebuffer();

	void resize(int w, int h);

	inline GLuint id()const{return m_fbo;}
	inline GLuint texture_id()const{return m_fbo_texture;}

private:
	GLuint m_fbo, m_fbo_texture, m_rbo_depth;
};

#endif // FRAMEBUFFER_H
