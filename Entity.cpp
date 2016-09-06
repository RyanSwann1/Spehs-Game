#include "Entity.h"
#include "EntityManager.h"
#include <cmath>


Entity::Entity(EntityManager* entityManager)
	: m_entityManager(entityManager)
{}

Entity::~Entity()
{}

void Entity::draw(sf::RenderWindow & window)
{
	m_sprite.setPosition(m_position.x, m_position.y);
	m_sprite.setScale(m_size.x, m_size.y);
	window.draw(m_sprite);
	//drawAABB(window);
}

void Entity::update(const float deltaTime)
{
	checkCollisions();
}


void Entity::move(const float x, const float y)
{
	m_oldPosition = m_position; //Assign the old position
	m_position += sf::Vector2f(x, y); //Move to new position
	
	updateAABB(); //Update the bounding box
}

void Entity::updateAABB()
{
	m_AABB = sf::FloatRect(m_position.x - (m_texture->getSize().x / 3.0f), m_position.y - (m_texture->getSize().y / 3.0f), m_texture->getSize().x / 2.0f, m_texture->getSize().y / 2.0f);
}

void Entity::checkCollisions()
{
	for(auto &i : m_entityManager->getEntities())
	{ 
		if (m_AABB.intersects(i.first->getAABB()))
		{
			onEntityCollision(i.first);
		}
	}
}

void Entity::resolveCollisions()
{
	if (m_collisions.empty()) {
		return;
	}
	//Sort the collisions so that one with teh biggest area is first
	std::sort(m_collisions.begin(), m_collisions.end(), [](const CollisionElement& col1, const CollisionElement& col2) { return col1.m_area < col2.m_area; });

	while (m_collisions.begin() != m_collisions.end())
	{
		m_collisions.pop_back();
	}
}

void Entity::applyTexture()
{
	TextureManager* textureManager = m_entityManager->getSharedContext()->m_textureManager;
	std::cout << "Requested texture." << "\n";
	if (textureManager->requireResource(m_name))
	{
		m_texture = textureManager->getResource(m_name);
		m_sprite.setTexture(*m_texture);
		m_sprite.setOrigin(m_texture->getSize().x / 2.0f, m_texture->getSize().y / 2.0f);
		std::cout << "Texture added." << "\n";
	}
}

void Entity::drawAABB(sf::RenderWindow& window)
{
	sf::RectangleShape rect;
	rect.setPosition(sf::Vector2f(m_AABB.left, m_AABB.top));
	rect.setSize(sf::Vector2f(m_AABB.width, m_AABB.height));
	rect.setFillColor(sf::Color::Green);
	window.draw(rect);
}