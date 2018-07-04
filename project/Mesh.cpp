#include "Mesh.h"
#include "State.h"

Mesh::Mesh()
{
}


Mesh::~Mesh()
{
}

void Mesh::addBuffer(const std::shared_ptr<Buffer>& buffer, const std::shared_ptr<Shader>& shader)
{
	std::pair<std::shared_ptr<Buffer>, std::shared_ptr<Shader>> myPair;
	myPair.first = buffer;

	if (shader)		myPair.second = shader;
	else			myPair.second = State::defaultShader;
	
	m_buffers.push_back(myPair);
}

size_t Mesh::getNumBuffers() const
{
	return m_buffers.size();
}

const std::shared_ptr<Buffer>& Mesh::getBuffer(size_t index) const
{
	return m_buffers[index].first;
}

std::shared_ptr<Buffer>& Mesh::getBuffer(size_t index)
{
	return m_buffers[index].first;
}

void Mesh::draw()
{
	for (auto it = m_buffers.begin(); it != m_buffers.end(); ++it)
	{
		(*it).second->use();
		glm::mat4 mvp = State::projectionMatrix * State::viewMatrix * State::modelMatrix;
		GLint uniMvp = (*it).second->getLocation("MVP");
		(*it).second->setMatrix(uniMvp, mvp);
		(*it).first->draw(*(*it).second);
	}
}
