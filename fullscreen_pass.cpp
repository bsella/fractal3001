#include "fullscreen_pass.h"

const GLfloat quad[]=
{
	-1.f,-1.f,
	 1.f,-1.f,
	-1.f, 1.f,
	 1.f, 1.f
};

const char vertex_shader_code[]=
	"#version 330\n\
	uniform sampler2D fbo_texture;\n\
	in vec2 pos;\n\
	out vec2 texCoord;\n\
	void main(){\n\
		gl_Position = vec4(pos,0.0,1.0);\n\
		texCoord = (pos+vec2(1.0))*0.5;\n\
	}";

unsigned int FullscreenPass::count = 0;
std::unique_ptr<Shader> FullscreenPass::singleton_vertex_shader;

GLuint FullscreenPass::vao;
GLuint FullscreenPass::vbo;

FullscreenPass::FullscreenPass() : RenderPass()
{
	if(count == 0)
	{
		// init vertex shader
		singleton_vertex_shader = std::make_unique<Shader>(GL_VERTEX_SHADER);
		singleton_vertex_shader->compile(vertex_shader_code);

		// init buffers
		glGenVertexArrays(1, &vao);
		glGenBuffers(1, &vbo);

		glBindVertexArray(vao);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(quad), quad, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (GLvoid*)0);
		glEnableVertexAttribArray(0);
	}
	glAttachShader(id(), singleton_vertex_shader->id());
	count++;
}

FullscreenPass::~FullscreenPass()
{
	count--;
	glDetachShader(m_program_id, singleton_vertex_shader->id());
	if(count == 0)
	{
		// free buffers
		glDeleteBuffers(1, &vbo);
		glDeleteVertexArrays(1, &vao);

		// free vertex shader
		singleton_vertex_shader.reset();
	}
}

void FullscreenPass::render()const
{
	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}
