#include "shader.h"

#include <iostream>

Shader::Shader(GLenum type){
	m_id= glCreateShader(type);
}

Shader::~Shader(){
	glDeleteShader(m_id);
}

bool Shader::compile(const char* code, std::ostream& ost)const{
	glShaderSource(m_id, 1, &code, nullptr);
	glCompileShader(m_id);

	GLint success;
	glGetShaderiv(m_id, GL_COMPILE_STATUS, &success);
	if(!success){
		char infoLog[1024];
		glGetShaderInfoLog(m_id, 1024, nullptr, infoLog);
		ost << infoLog << std::endl;
	}
	return static_cast<bool>(success);
}
