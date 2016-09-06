#include "EnemyLaser.h"
#include "EntityManager.h"


EnemyLaser::EnemyLaser(EntityManager* entityManager)
	: Projectile(entityManager)

{
	m_direction = Direction::Up;
	m_size = sf::Vector2f(.75f, .75f);
	m_name = "Enemy_Laser";
	m_speed = sf::Vector2f(0, .1f);
	m_damage = 1;
	Entity::applyTexture();
}


EnemyLaser::~EnemyLaser()
{
}

void EnemyLaser::onEntityCollision(Entity * collider)
{

}

void EnemyLaser::update(const float deltaTime)
{
	move(m_direction);
	Entity::update(deltaTime);

	sf::Vector2u mapSize = m_entityManager->getSharedContext()->m_window->getSize();
	if (m_position.y <= 0)
	{
		m_entityManager->removeEntity(m_ID);
	}
}

