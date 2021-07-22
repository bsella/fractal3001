#include "gbuffer.h"

GBuffer::GBuffer()
{
	glGenFramebuffers(1, &m_id);
	glBindFramebuffer(GL_FRAMEBUFFER, m_id);

	glGenTextures(1, &m_z_texture);
	glBindTexture(GL_TEXTURE_2D, m_z_texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RG32F, 640, 640, 0, GL_RG, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_z_texture, 0);

	glGenTextures(1, &m_i_texture);
	glBindTexture(GL_TEXTURE_2D, m_i_texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_R32UI, 640, 640, 0, GL_RED_INTEGER, GL_UNSIGNED_INT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, m_i_texture, 0);

	GLenum draw_buffers[] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1};
	glDrawBuffers(2, draw_buffers);

	glFlush();
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
}
GBuffer::~GBuffer()
{
	glDeleteTextures(1, &m_i_texture);
	glDeleteTextures(1, &m_z_texture);
	glDeleteFramebuffers(1, &m_id);
}

void GBuffer::bind_textures()const
{glEnable(GL_TEXTURE_2D);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_z_texture);
	glReadBuffer(GL_COLOR_ATTACHMENT0);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, m_i_texture);
	glReadBuffer(GL_COLOR_ATTACHMENT1);
}
