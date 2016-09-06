#ifndef CHARACTER_H
#define CHARACTER_H


#include "Entity.h"
class Character :
	public Entity
{
public:
	Character(EntityManager* entityManager);
	virtual ~Character();

	void move(const Direction dir);
	void reduceLivesAmount(const unsigned int i);
	inline void addLivesAmount(const unsigned int i);

	virtual void update(const float deltaTime) {}

protected:
	virtual void onEntityCollision(Entity* collider) = 0;
	unsigned int m_lives;
	unsigned int m_maxLives;

};
#endif // !CHARACTER_H
