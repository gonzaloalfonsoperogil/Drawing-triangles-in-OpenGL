#include "World.h"



World::World()
{
}


World::~World()
{
}

void World::addEntity(const std::shared_ptr<Entity>& entity)
{
	m_entityList.push_back(entity);
	if (std::dynamic_pointer_cast<Camera>(entity))	m_cameraList.push_back(std::dynamic_pointer_cast<Camera>(entity));
}

void World::removeEntity(const std::shared_ptr<Entity>& entity)
{
	for (auto it = m_entityList.begin(); it != m_entityList.end(); ++it)
	{
		if (*it == entity)
		{
			m_entityList.erase(it);
		}
	}
	if (std::dynamic_pointer_cast<Camera>(entity))
	{
		for (auto it = m_cameraList.begin(); it != m_cameraList.end(); ++it)
		{
			if (*it == entity)
			{
				m_cameraList.erase(it);
			}
		}
	}
}

size_t World::getNumEntities() const
{
	return m_entityList.size();
}

const std::shared_ptr<Entity>& World::getEntity(size_t index) const
{
	return m_entityList[index];
}

std::shared_ptr<Entity>& World::getEntity(size_t index)
{
	return m_entityList[index];
}

void World::update(float deltaTime)
{
	for (auto it = m_entityList.begin(); it != m_entityList.end(); ++it)
	{
		(*it)->update(deltaTime);
	}
}

void World::draw()
{
	for (auto it = m_cameraList.begin(); it != m_cameraList.end(); ++it)
	{
		(*it)->prepare();
		for (auto it = m_entityList.begin(); it != m_entityList.end(); ++it)
		{
			(*it)->draw();
		}
	}
	
}