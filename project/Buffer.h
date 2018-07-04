#pragma once
#include "Vertex.h"
#include <vector>
#include "Shader.h"




class Buffer
{
public:
	Buffer(std::vector<Vertex> vertices, std::vector<uint16_t> indices);
	~Buffer();
	void draw(const Shader& shader) const;

	uint32_t v, i;

	std::vector<Vertex> m_vertices;
	std::vector<uint16_t> m_indices;

};

