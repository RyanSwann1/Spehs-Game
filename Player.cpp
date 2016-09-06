#include "Player.h"
#include "EntityManager.h"
#include "TextureManager.h"
#include "Direction.h"
#include "PlayerLaser.h"
#include <assert.h>


Player::Player(EntityManager* entityManager)
	: Character(entityManager),
	m_timeBetweenFire(1)
{
	m_size = sf::Vector2f(.5f, .5f);
	m_position = sf::Vector2f(4, 2);
	m_name = "Player";
	m_entityType = EntityType::Player;
	m_speed = sf::Vector2f(5, 5);
	Entity::applyTexture(); //Initialize the texture for the entity
	m_direction = Direction::None;
	//Cannot allow more than one callback at teh same time
	EventSystem* eventSystem = m_entityManager->getSharedContext()->m_eventSystem;
	assert(eventSystem->addCallback<Player>(StateType::Game, "Move_Left", &Player::reactToInput, this) == true);
	assert(eventSystem->addCallback<Player>(StateType::Game, "Move_Right", &Player::reactToInput, this) == true);
	assert(eventSystem->addCallback<Player>(StateType::Game, "Move_Up", &Player::reactToInput, this) == true);
	assert(eventSystem->addCallback<Player>(StateType::Game, "Move_Down", &Player::reactToInput, this) == true);
	assert(eventSystem->addCallback<Player>(StateType::Game, "Fire_Laser", &Player::reactToInput, this) == true);
}

Player::~Player()
{
	EventSystem* eventSystem = m_entityManager->getSharedContext()->m_eventSystem;
	eventSystem->removeCallback(StateType::Game, "Move_Left");
	eventSystem->removeCallback(StateType::Game, "Move_Right");
	eventSystem->removeCallback(StateType::Game, "Move_Up");
	eventSystem->removeCallback(StateType::Game, "Move_Down");
	eventSystem->removeCallback(StateType::Game, "Fire_Laser");
}

void Player::onEntityCollision(Entity * collider)
{
	if (collider->getType() == EntityType::Enemy) 
	{
		reduceLivesAmount(collider->getDamage()); //Inflict damage onto this entity
		m_entityManager->removeEntity(collider->getID()); //Remove entity from game
	}
}

void Player::update(const float deltaTime)
{
	m_timeElasped += deltaTime;
	Entity::move(m_velocity.x, m_velocity.y);
	//m_velocity = sf::Vector2f(0, 0);

	//Check boundary
	sf::Vector2u mapBoundary = m_entityManager->getSharedContext()->m_window->getSize();
	if(m_position.x < 0) {
		m_position.x = 0;
	}
	else if ((m_position.x + m_size.x) >= mapBoundary.x) {
		m_position.x = mapBoundary.x;
	}
	
	else if (m_position.y > mapBoundary.y / 2.0f) {
		m_position.y = mapBoundary.y / 2.0f;
	}

	else if (m_position.y < 0) {
		m_position.y = 0;
	}
	Entity::update(deltaTime);
}

void Player::reactToInput(EventDetails* eventDetails)
{
	if (eventDetails->m_name == "Move_Left") {
		move(Direction::Left);
	}
	else if (eventDetails->m_name == "Move_Right") {
		move(Direction::Right);
	}
	else if (eventDetails->m_name == "Move_Up") {
		move(Direction::Up);
	}
	else if (eventDetails->m_name == "Move_Down") {
		move(Direction::Down);
	}
	else if (eventDetails->m_name == "Fire_Laser") {
		fireLaser();
	}
}

void Player::fireLaser()
{
	if (m_timeElasped >= m_nextFireTime)
	{
		Entity* laser = new PlayerLaser(m_entityManager);
		laser->setStartPos(getFirePos());
		m_entityManager->addEntity(EntityType::Projectile, laser);
	
		m_nextFireTime += m_timeBetweenFire;
	}
}

sf::Vector2f Player::getFirePos() const
{
	return sf::Vector2f(m_position.x + m_size.x, m_position.y + m_size.y);
}


