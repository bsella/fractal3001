#include "color_pass.h"
#include "../shader.h"

const char fragment_shader_code[]=
"#version 330\n\
uniform sampler2D z0;\n\
uniform sampler2D zn;\n\
uniform usampler2D n;\n\
out vec4 fragColor;\n\
in vec2 texCoord;\n\
const float bailout = 300;\n\
\n\
vec2 add(vec2 c1, vec2 c2){\n\
	return vec2(c1.x + c2.x, c1.y + c2.y);\n\
}\n\
\n\
vec2 mul(vec2 c1, vec2 c2){\n\
	return vec2(c1.x*c2.x - c1.y*c2.y, c1.x*c2.y + c1.y*c2.x);\n\
}\n\
\n\
float mag2(vec2 c){\n\
	return c.x*c.x + c.y*c.y;\n\
}\n\
\n\
float mag(vec2 c){\n\
	return sqrt(mag2(c));\n\
}\n\
\n\
float mag_norm(vec2 c){\n\
	return log(mag2(c)/bailout)/log(bailout);\n\
}\n\
\n\
float arg(vec2 c){\n\
	return 2 * atan(c.y / (c.x + sqrt(mag2(c))));\n\
}\n\
\n\
float arg_norm(vec2 c){\n\
	return arg(c)/6.282 + 0.5;\n\
}\n\
\n\
void main(){\n\
	vec2 z0= texture(z0, texCoord).rg;\n\
	vec2 z= texture(zn, texCoord).rg;\n\
	uint i = texture(n, texCoord).r;\n\
	if(i<200u){\n\
		fragColor = vec4(arg_norm(z), mag_norm(z), float(i)/20.0,1);\n\
	}else{\n\
		fragColor = vec4(z, arg_norm(z),1);\n\
	}\n\
}\n";

FractalColorPass::FractalColorPass() : FullscreenPass()
{
	Shader fragment_shader(GL_FRAGMENT_SHADER);
	if(fragment_shader.compile(fragment_shader_code)){
		glAttachShader(id(), fragment_shader.id());
		glLinkProgram(id());

		m_z0 = glGetUniformLocation(id(), "z0");
		m_zn = glGetUniformLocation(id(), "zn");
		m_n  = glGetUniformLocation(id(), "n");
	}
}

void FractalColorPass::render()const
{
	glUniform1i(m_z0, 0);
	glUniform1i(m_zn, 1);
	glUniform1i(m_n, 2);
	FullscreenPass::render();
}
