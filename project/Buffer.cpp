#include "Buffer.h"
#include "../src/common.h"



Buffer::Buffer(std::vector<Vertex> vertices, std::vector<uint16_t> indices)
{
	m_vertices = vertices;
	m_indices = indices;
	glGenBuffers(1, &v);
	glBindBuffer(GL_ARRAY_BUFFER, v);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * m_vertices.size(), m_vertices.data(), GL_STATIC_DRAW);

	glGenBuffers(1, &i);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, i);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint16_t) * m_indices.size(), m_indices.data(), GL_STATIC_DRAW);

}


Buffer::~Buffer()
{
}

void Buffer::draw(const Shader& shader) const
{
	glBindBuffer(GL_ARRAY_BUFFER, v);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, i);
	shader.setupAttribs();
	glDrawElements(GL_TRIANGLES, m_indices.size(), GL_UNSIGNED_SHORT, nullptr);

}
