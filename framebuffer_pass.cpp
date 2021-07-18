#include "framebuffer_pass.h"
#include "framebuffer.h"

const GLfloat quad[]=
{
	-1.f,-1.f,
	 1.f,-1.f,
	-1.f, 1.f,
	 1.f, 1.f
};

const unsigned int quad_indices[]=
{
	0,1,2,
	2,1,3
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

unsigned int FramebufferPass::count = 0;
std::unique_ptr<Shader> FramebufferPass::singleton_vertex_shader;

static GLuint vao;
static GLuint vbo;
static GLuint ebo;

FramebufferPass::FramebufferPass() : RenderPass()
{
	if(count == 0)
	{
		// init vertex shader
		singleton_vertex_shader = std::make_unique<Shader>(GL_VERTEX_SHADER);
		singleton_vertex_shader->compile(vertex_shader_code);

		// init buffers
		glGenVertexArrays(1, &vao);
		glGenBuffers(1, &vbo);
		glGenBuffers(1, &ebo);

		glBindVertexArray(vao);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(quad), quad, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (GLvoid*)0);
		glEnableVertexAttribArray(0);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(quad_indices), quad_indices, GL_STATIC_DRAW);
	}
	glAttachShader(id(), singleton_vertex_shader->id());
	count++;
}

FramebufferPass::~FramebufferPass()
{
	count--;
	glDetachShader(m_program_id, singleton_vertex_shader->id());
	if(count == 0)
	{
		// free buffers
		glDeleteBuffers(1, &ebo);
		glDeleteBuffers(1, &vbo);
		glDeleteVertexArrays(1, &vao);

		// free vertex shader
		singleton_vertex_shader.reset();
	}
}

void FramebufferPass::render()const
{
	glBindVertexArray(vao);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void FramebufferPass::draw_on(Framebuffer& fb) const
{
}
