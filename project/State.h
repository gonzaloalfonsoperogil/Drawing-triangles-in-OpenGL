#pragma once
#include "../src/common.h"
#include "Shader.h"

class State{

public:
	State();
	~State();

	static std::shared_ptr<Shader>	defaultShader;
	static glm::mat4 				projectionMatrix;
	static glm::mat4 				viewMatrix;
	static glm::mat4 				modelMatrix;
	

};

