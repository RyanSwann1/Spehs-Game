#include "EntityManager.h"
#include "SharedContext.h"
#include "Player.h"
#include "PlayerLaser.h"
#include "Enemy.h"
#include "EnemyLaser.h"

EntityManager::EntityManager(SharedContext* sharedContext)
	: m_sharedContext(sharedContext),
	m_entityCount(0)
{
	registerEntity<Player>(EntityType::Player);
	registerEntity<PlayerLaser>(EntityType::Projectile);
	registerEntity<Enemy>(EntityType::Enemy);
	registerEntity<EnemyLaser>(EntityType::Projectile);
}


EntityManager::~EntityManager()
{
	destroyEntities();
	destroyFactory();
	m_entitiesToRemove.clear(); //If any left 
}

void EntityManager::addEntity(const EntityType type)
{
	auto iter = m_entityFactory.find(type);
	if (iter != m_entityFactory.cend())
	{
		m_entityCount++; //Increase entity count for each entity added
		m_entities.emplace_back(iter->second(), m_entityCount);
		m_entities.back().first->setID(m_entityCount); //Set ID for the entity
	}
	else {
		std::cerr << "Couldn't find Entity " << "\n";
	}
}

void EntityManager::addEntity(const EntityType type, Entity * entity)
{
	if (m_entityFactory.find(type) != m_entityFactory.cend())
	{
		m_entityCount++;
		m_entities.emplace_back(entity, m_entityCount);
		m_entities.back().first->setID(m_entityCount);
	}
}

void EntityManager::processRemovals()
{
	while (m_entitiesToRemove.begin() != m_entitiesToRemove.end())
	{
		if (removeActiveEntity(m_entitiesToRemove.back()))
		{
			m_entitiesToRemove.pop_back();
			m_entityCount--;
		}
		else {
			std::cout << "Entity not removed." << "\n";
		}
	}
}

void EntityManager::update(const float deltaTime)
{
	for (auto &i : m_entities)
	{
		i.first->update(deltaTime);
	}
	processRemovals();
}

void EntityManager::draw(sf::RenderWindow & window)
{
	for (auto &i : m_entities)
	{
		i.first->draw(window);
	}
}

bool EntityManager::removeActiveEntity(unsigned int id)
{
	for (auto iter = m_entities.begin(); iter != m_entities.end(); iter++)
	{
		if (iter->first->getID() == id)
		{
			delete iter->first;
			iter->first = nullptr;
			m_entities.erase(iter);
			std::cout << "Entity Removed." << "\n";
			return true;
		}
	}
	return false;
}

void EntityManager::destroyFactory()
{
	for (auto &i : m_entityFactory)
	{
		delete i.second();
		i.second = nullptr;
	}
	m_entityFactory.clear();
}

void EntityManager::destroyEntities()
{
	for (auto &i : m_entities)
	{
		delete i.first;
		i.first = nullptr;
	}
	m_entities.clear();
}
