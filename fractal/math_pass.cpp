#include "math_pass.h"
#include "../shader.h"

const char fragment_shader_code[]=
"#version 330\n\
uniform float zoom;\n\
uniform float center_x;\n\
uniform float center_y;\n\
layout (location = 0) out vec2 z0;\n\
layout (location = 1) out vec2 zn;\n\
layout (location = 2) out uint iteration_count;\n\
in vec2 texCoord;\n\
\n\
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
	z0.x = center_x + texCoord.x*zoom - zoom * 0.5;\n\
	z0.y = center_y + texCoord.y*zoom - zoom * 0.5;\n\
	\n\
	zn = z0;\n\
	for(iteration_count =0u ; iteration_count < 200u; iteration_count++){\n\
		if(mag2(zn)>bailout){\n\
			break;\n\
		}\n\
		zn = add(mul(zn,zn),z0);\n\
	}\n\
}\n";

FractalMathPass::FractalMathPass() : FullscreenPass()
{
	Shader fragment_shader(GL_FRAGMENT_SHADER);
	if(fragment_shader.compile(fragment_shader_code)){
		glAttachShader(id(), fragment_shader.id());
		glLinkProgram(id());

		m_zoom_location = glGetUniformLocation(id(), "zoom");
		m_x_location = glGetUniformLocation(id(), "center_x");
		m_y_location = glGetUniformLocation(id(), "center_y");
	}
}

void FractalMathPass::render()const
{
	glUniform1f(m_zoom_location, zoom);
	glUniform1f(m_x_location, center_x);
	glUniform1f(m_y_location, center_y);
	FullscreenPass::render();
}
