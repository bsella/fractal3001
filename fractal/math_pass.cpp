﻿#include "math_pass.h"
#include "../shader.h"

const char fragment_shader_code[]=
"#version 330\n\
uniform float zoom;\n\
uniform float center_x;\n\
uniform float center_y;\n\
layout (location = 0) out vec2 last_z;\n\
layout (location = 1) out uint iteration_count;\n\
in vec2 texCoord;\n\
\n\
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
	float x = center_x + texCoord.x*zoom - zoom * 0.5;\n\
	float y = center_y + texCoord.y*zoom - zoom * 0.5;\n\
	\n\
	complex z;\n\
	z.a = x;\n\
	z.b = y;\n\
	complex c = z;\n\
	for(iteration_count =0u ; iteration_count < 200u; iteration_count++){\n\
		if(mag2(z)>bailout){\n\
			break;\n\
		}\n\
		z = add(mul(z,z),c);\n\
	}\n\
	last_z = vec2(z.a,z.b);\n\
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