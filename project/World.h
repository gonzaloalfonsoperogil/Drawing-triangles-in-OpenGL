#pragma once
#include <memory>
#include <vector>
#include "Entity.h"
#include "Camera.h"

class World
{
public:
	World();
	~World();

	void addEntity(const std::shared_ptr<Entity>& entity);
	void removeEntity(const std::shared_ptr<Entity>& entity);
	size_t getNumEntities() const;
	const std::shared_ptr<Entity>& getEntity(size_t index) const;
	std::shared_ptr<Entity>& getEntity(size_t index);
	void update(float deltaTime);
	void draw();

private:
	std::vector<std::shared_ptr<Entity>> m_entityList;
	std::vector<std::shared_ptr<Camera>> m_cameraList;
};

