#pragma once
#include "Entity.h"
#include "Mesh.h"

class Model : public Entity
{
public:
	Model(const std::shared_ptr<Mesh>& mesh);
	virtual void draw() override;
	void update(float deltaTime);


private:
	std::shared_ptr<Mesh> m_mesh;
	float degrees;
};

