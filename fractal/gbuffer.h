#ifndef GBUFFER_H
#define GBUFFER_H

#include <GL/glew.h>

class GBuffer
{
public:
	GBuffer(int w, int h);
	~GBuffer();

	inline GLuint id()const{return m_id;}

	void bind_textures()const;

private:
	GLuint m_id;
	GLuint m_z0_texture;
	GLuint m_zn_texture;
	GLuint m_n_texture;
};

#endif // GBUFFER_H
