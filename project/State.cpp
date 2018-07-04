#include "State.h"

State::State()
{

}
State::~State()
{

}

std::shared_ptr<Shader>	State::defaultShader;
glm::mat4 				State::projectionMatrix;
glm::mat4 				State::viewMatrix;
glm::mat4 				State::modelMatrix;
