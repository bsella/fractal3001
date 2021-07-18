#pragma once

#include <GL/glew.h>
#include <iostream>

class Shader{
public:
	Shader(GLenum type);
	~Shader();

	inline GLuint id()const{return m_id;}

	bool compile(const char* code, std::ostream& = std::cerr)const;

private:
	GLuint m_id=0;
};

