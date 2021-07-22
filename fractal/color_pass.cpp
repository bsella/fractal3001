#include "color_pass.h"
#include "../shader.h"

const char fragment_shader_code[]=
"#version 330\n\
uniform sampler2D last_z;\n\
uniform usampler2D iteration_count;\n\
out vec4 fragColor;\n\
in vec2 texCoord;\n\
const float bailout = 300;\n\
\n\
struct complex{\n\
	float a;\n\
	float b;\n\
};\n\
\n\
complex add(complex c1, complex c2){\n\
	complex ret;\n\
	ret.a = c1.a + c2.a;\n\
	ret.b = c1.b + c2.b;\n\
	return ret;\n\
}\n\
\n\
complex mul(complex c1, complex c2){\n\
	complex ret;\n\
	ret.a = c1.a*c2.a - c1.b*c2.b;\n\
	ret.b = c1.a*c2.b + c1.b*c2.a;\n\
	return ret;\n\
}\n\
\n\
float mag2(complex c){\n\
	return c.a*c.a + c.b*c.b;\n\
}\n\
\n\
float mag(complex c){\n\
	return sqrt(mag2(c));\n\
}\n\
\n\
float mag_norm(complex c){\n\
	return log(mag2(c)/bailout)/log(bailout);\n\
}\n\
\n\
float arg(complex c){\n\
	return 2 * atan(c.b / (c.a + sqrt(mag2(c))));\n\
}\n\
\n\
float arg_norm(complex c){\n\
	return arg(c)/6.282 + 0.5;\n\
}\n\
\n\
void main(){\n\
	complex z;\n\
	z.a = texture(last_z, texCoord).x;\n\
	z.b = texture(last_z, texCoord).y;\n\
	uint i = texture(iteration_count, texCoord).r;\n\
	if(i<200u){\n\
		fragColor = vec4(arg_norm(z), mag_norm(z), float(i)/20.0,1);\n\
	}else{\n\
		fragColor = vec4(z.a, z.b, 0,1);\n\
	}\n\
}\n";

FractalColorPass::FractalColorPass() : FullscreenPass()
{
	Shader fragment_shader(GL_FRAGMENT_SHADER);
	if(fragment_shader.compile(fragment_shader_code)){
		glAttachShader(id(), fragment_shader.id());
		glLinkProgram(id());

		m_last_z     = glGetUniformLocation(id(), "last_z");
		m_iterations = glGetUniformLocation(id(), "iteration_count");
	}
}

void FractalColorPass::render()const
{
	glUniform1i(m_last_z, 0);
	glUniform1i(m_iterations, 1);
	FullscreenPass::render();
}
