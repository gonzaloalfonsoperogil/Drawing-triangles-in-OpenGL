#include "Shader.h"
#include "../glew/GL/glew.h"
#include "Vertex.h"



Shader::~Shader()
{
	glDeleteProgram(m_program);
}
std::shared_ptr<Shader> Shader::create(const std::string& vertexCode, const std::string& fragmentCode)
{
	std::shared_ptr<Shader> s(new Shader(vertexCode, fragmentCode), [](Shader* p)->void { delete p; });
	if (s->getId() == 0) s = nullptr;

	return s;
}
Shader::Shader(const std::string& vertexCode, const std::string& fragmentCode)
{
	const char * Vcode = vertexCode.c_str();
	m_vShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(m_vShader, 1, &Vcode, nullptr);
	
	
	glCompileShader(m_vShader);
	glGetShaderiv(m_vShader, GL_COMPILE_STATUS, &retCode);
	if (retCode == GL_FALSE)
	{
		glGetShaderInfoLog(m_vShader, sizeof(errorLog), NULL, errorLog);
		glDeleteShader(m_vShader);
	}

	const char * Fcode = fragmentCode.c_str();
	m_fShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(m_fShader, 1, &Fcode, nullptr);
	glCompileShader(m_fShader);
	glGetShaderiv(m_fShader, GL_COMPILE_STATUS, &retCode);
	if (retCode == GL_FALSE)
	{
		glGetShaderInfoLog(m_fShader, sizeof(errorLog), NULL, errorLog);
		glDeleteShader(m_vShader);
		glDeleteShader(m_fShader);
	}


	m_program = glCreateProgram();
	glAttachShader(m_program, m_vShader);
	glAttachShader(m_program, m_fShader);
	
	glLinkProgram(m_program);

	glDeleteShader(m_vShader);
	glDeleteShader(m_fShader);
	glGetProgramiv(m_program, GL_LINK_STATUS, &retCode);
	if (retCode == GL_FALSE)
	{
		glGetProgramInfoLog(m_program, sizeof(errorLog), NULL, errorLog);
	}

	m_pos = glGetAttribLocation(m_program, "vpos");
	m_color = glGetAttribLocation(m_program, "vcolor");

}

void Shader::setInt(int loc, int val)
{
	if (loc != -1)
	{
		glUniform1i(loc, val);
	}
}

void Shader::setFloat(int loc, float val)
{
	if (loc != -1)
	{
		glUniform1f(loc, val);
	}
}

void Shader::setVec3(int loc, const glm::vec3& vec)
{
	if (loc != -1)
	{
		glUniform3f(loc, vec.x, vec.y, vec.z);
	}
}

void Shader::setVec4(int loc, const glm::vec4& vec)
{
	if (loc != -1)
	{
		glUniform4f(loc, vec.x, vec.y, vec.z, vec.w);
	}
}

void Shader::setMatrix(int loc, const glm::mat4& matrix)
{
	if (loc != -1)
	{
		glUniformMatrix4fv(loc, 1, false, reinterpret_cast<const GLfloat *>(&matrix));
	}
}

uint32_t Shader::getId() const
{
	return m_program;
}

const char* Shader::getError() const
{
	return errorLog;
}

int Shader::getLocation(const char* name) const
{
	return glGetUniformLocation(m_program, name);
}

void Shader::use() const
{
	glUseProgram(m_program);
}

void Shader::setupAttribs() const
{
	glEnableVertexAttribArray(m_pos);
	glEnableVertexAttribArray(m_color);
	if (m_pos != -1)
	{
		glVertexAttribPointer(m_pos, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, x)));
	}
	if (m_color != -1)
	{
		glVertexAttribPointer(m_color, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, r)));
	}
	
}
