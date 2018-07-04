#include "Camera.h"
#include "State.h"
#include "../src/common.h"


Camera::Camera()
{
	m_projection = glm::mat4(1.0f);
	m_clearColor = glm::vec3(0, 0, 0);
	m_viewport = glm::ivec4(0, 0, 0, 0);
}


Camera::~Camera()
{
}

const glm::mat4& Camera::getProjection() const
{
	return m_projection;
}
void Camera::setProjection(const glm::mat4& proj)
{
	m_projection = proj;
}

const glm::ivec4& Camera::getViewport() const
{
	return m_viewport;
}
void Camera::setViewport(const glm::ivec4& vp)
{
	m_viewport = vp;
}

const glm::vec3& Camera::getClearColor() const
{
	return m_clearColor;
}

void Camera::setClearColor(const glm::vec3& color)
{
	m_clearColor = color;
}

void Camera::update(float deltaTime)
{

}

void Camera::prepare()
{
	State::projectionMatrix = getProjection();
	/*glm::mat4 rotationMatrix(-glm::angleAxis(glm::angle(getRotation()), glm::axis(getRotation())));
	State::viewMatrix = glm::translate(rotationMatrix, -getPosition());*/
	glm::mat4 view = glm::mat4();
	view = glm::rotate(view, glm::angle(m_rotation)*-1.0f, glm::axis(m_rotation));
	view = glm::translate(view, getPosition()*-1.0f);
	State::viewMatrix = view;
	
	glViewport(getViewport().x, getViewport().y, getViewport().z, getViewport().w);
	glScissor(getViewport().x, getViewport().y, getViewport().z, getViewport().w);
	glClearColor(getClearColor().r, getClearColor().g, getClearColor().b, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}