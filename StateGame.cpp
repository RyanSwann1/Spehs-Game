#include "StateGame.h"
#include "StateManager.h"
#include "TextureManager.h"
#include "EntityManager.h"
#include "Window.h"
#include "Enemy.h"
#include "RandomNumberGenerator.h"
#include <iostream>
#include <assert.h>

StateGame::StateGame(StateManager* stateManager)
	: StateBase(stateManager),
	m_timeBetweenEnemySpawn(3),
	m_nextEnemySpawnTime(4),
	m_minEnemySpawnPos(25),
	m_maxEnemySpawnPos(450)
{
	//m_stateManager->getSharedContext()->m_eventSystem->addCallback<StateGame>(StateType::Game, "Next_Level", &StateGame::nextLevel, this);
	m_stateManager->getSharedContext()->m_entityManager->addEntity(EntityType::Player);
}


StateGame::~StateGame()
{
	m_stateManager->getSharedContext()->m_eventSystem->removeCallback(StateType::Game, "Next_Level");
}

void StateGame::onCreate()
{
	std::cout << "StateGame Created." << "\n";
	//Window* window = m_stateManager->getSharedContext()->m_window;
	//window->toggleFullScreen(fullSCreen);
	//m_stateManager->getSharedContext()->m_entityManager->
	//registerEntity("Player", new Player(this, "Player", 3), 3);

}

void StateGame::onEnter()
{
	std::cout << "StateGame ENtered." << "\n";
}

void StateGame::update(const float deltaTime)
{
	m_timeElasped += deltaTime;
	if (m_timeElasped >= m_nextEnemySpawnTime)
	{
		m_nextEnemySpawnTime += m_timeBetweenEnemySpawn;
		spawnEnemy();
	}

	m_stateManager->getSharedContext()->m_entityManager->update(deltaTime);
}

void StateGame::draw(sf::RenderWindow & window)
{
	m_stateManager->getSharedContext()->m_entityManager->draw(window);
}

void StateGame::nextLevel()
{
	m_stateManager->switchTo(StateType::MainMenu);
	m_stateManager->remove(StateType::Game);
	std::cout << "State Size:" << m_stateManager->getStateSize() << "\n";
}

void StateGame::spawnEnemy()
{
	EntityManager* entityManager = m_stateManager->getSharedContext()->m_entityManager;
	Entity* enemy = new Enemy(entityManager);
	entityManager->addEntity(EntityType::Enemy, enemy);
	enemy->setStartPos(sf::Vector2f(RandomNumberGenerator::getRandomNumber(0, m_maxEnemySpawnPos), 650));
}

