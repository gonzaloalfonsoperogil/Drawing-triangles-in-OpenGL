#pragma once
#include <stdint.h>
#include <memory>
#include <string>
#include "../lib/glm/glm.hpp"
#include "GL\glew.h"

class Shader
{
public:
	~Shader();
	

	static std::shared_ptr<Shader> create(const std::string& vertexCode, const std::string& fragmentCode);
	

	// Devuelve el identificador de OpenGL del programa
	uint32_t	getId() const;

	// Obtiene el mensaje de error generado al compilar o enlazar
	const char*	getError() const;

	// Activa el uso de este programa
	void		use() const;

	// Activa la escritura de las variables attribute,
	// y especifica su formato
	void		setupAttribs() const;

	// Obtiene la localización de una variable uniform
	int		getLocation(const char* name) const;


	// Da valor a una variable uniform
	void		setInt(int loc, int val);
	void		setFloat(int loc, float val);
	void		setVec3(int loc, const glm::vec3& vec);
	void		setVec4(int loc, const glm::vec4& vec);
	void		setMatrix(int loc, const glm::mat4& matrix);

private:
	Shader(const std::string& vertexCode, const std::string& fragmentCode);

	char * m_errorCode;
	uint32_t m_vShader, m_fShader, m_program;
	GLint retCode;
	char errorLog[1024];

	int m_pos, m_color;
};

