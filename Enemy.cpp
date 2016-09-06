#include "Enemy.h"
#include "EntityManager.h"
#include "EnemyLaser.h"

Enemy::Enemy(EntityManager* entityManager)
	: Character(entityManager),
	m_nextFireTime(.75f),
	m_timeBetweenFire(1.5f),
	m_timeElasped(0)
{
	m_name = "Enemy";
	m_speed = sf::Vector2f(.025f, .025f);
	m_direction = Direction::Up;
	m_entityType = EntityType::Enemy;
	m_size = sf::Vector2f(.5f, .5f);
	m_lives = 1;
	Entity::applyTexture();
}

Enemy::~Enemy()
{
		
}

void Enemy::onEntityCollision(Entity * collision)
{
		 
}

void Enemy::update(const float deltaTime)
{
	m_timeElasped += deltaTime;
	move(m_direction);

	sf::Vector2u mapSize = m_entityManager->getSharedContext()->m_window->getSize();
	if (m_position.y < 0)
	{
		m_entityManager->removeEntity(m_ID);
	}
	Entity::update(deltaTime);

	if (m_timeElasped >= m_nextFireTime)
	{
		//fireProjectile();
		m_nextFireTime += m_timeBetweenFire;
	}
}

void Enemy::fireProjectile()
{
	Entity* projectile = new EnemyLaser(m_entityManager);
	projectile->setStartPos(getFirePos());
	m_entityManager->addEntity(EntityType::Projectile, projectile);

	//if (m_timeElasped >= m_nextFireTime)
	//{
	//	Entity* laser = new PlayerLaser(m_entityManager);
	//	laser->setStartPos(getFirePos());
	//	m_entityManager->addEntity(EntityType::Projectile, laser);

	//	m_nextFireTime += m_timeBetweenFire;
	//}
}

sf::Vector2f Enemy::getFirePos() const
{
	return sf::Vector2f(m_position.x, m_position.y);
}
