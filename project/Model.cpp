#include "Model.h"
#include "State.h"
#include "../glm/gtx/quaternion.hpp"



Model::Model(const std::shared_ptr<Mesh>& mesh)
{
	m_mesh = mesh;
	degrees = 0;
}

void Model::draw()
{
	glm::mat4 TranslateMatrix = glm::translate(glm::mat4(), m_position);
	glm::mat4 RotateMatrix = glm::rotate(TranslateMatrix, glm::angle(m_rotation), glm::axis(m_rotation));
	State::modelMatrix = glm::scale(RotateMatrix, m_scale);
	m_mesh->draw();
}

void Model::update(float deltaTime)
{
	setRotation(glm::angleAxis(glm::radians(degrees), glm::vec3(0,1,0)));
	degrees += 32 * deltaTime;
}