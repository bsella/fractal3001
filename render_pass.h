#ifndef RENDER_PASS_H
#define RENDER_PASS_H

#include <GL/glew.h>

class RenderPass
{
public:
	RenderPass();
	virtual ~RenderPass();

	void use()const;
	virtual void render()const=0;

	inline GLuint id()const{return m_program_id;}

protected:
	GLuint m_program_id;
};

#endif // RENDER_PASS_H
