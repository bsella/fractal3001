#ifndef GBUFFER_H
#define GBUFFER_H

#include <GL/glew.h>

class GBuffer
{
public:
	GBuffer();
	~GBuffer();

	inline GLuint id()const{return m_id;}

	void bind_textures()const;

private:
	GLuint m_id;
	GLuint m_z_texture;
	GLuint m_i_texture;
};

#endif // GBUFFER_H
