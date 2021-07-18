#include "render_pass.h"

RenderPass::RenderPass(){
	m_program_id = glCreateProgram();
}

RenderPass::~RenderPass(){
	glDeleteProgram(m_program_id);
}

void RenderPass::use()const{
	glUseProgram(m_program_id);
}
