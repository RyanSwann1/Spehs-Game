#ifndef STATE_GAME_H
#define STATE_GAME_H

#include "Player.h"
#include "StateBase.h"


class StateGame :
	public StateBase
{
public:
	StateGame(StateManager* stateManager);
	~StateGame();

	void onCreate() override;


	void onEnter() override;

	void update(const float deltaTime) override;
	void draw(sf::RenderWindow& window) override;
	
private:
	void nextLevel();
	void spawnEnemy();

	float m_timeElasped;
	float m_nextEnemySpawnTime;
	float m_timeBetweenEnemySpawn;
	unsigned int m_minEnemySpawnPos;
	unsigned int m_maxEnemySpawnPos;

};
#endif // !STATE_GAME_H
