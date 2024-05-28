#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"

class StudentWorld;

class Actor : public GraphObject {
public:
	Actor(int imageID, int startX, int startY,
		StudentWorld* world) : GraphObject(imageID, startX, startY),
		m_world(world) {}

	virtual void doSomething() = 0;

protected:
	StudentWorld* getWorld() const { return m_world; }

private:
	StudentWorld* m_world;
};

class Player : public Actor {
public:
	Player(StudentWorld* world, int startX, int startY) :
		Actor(IID_PLAYER, startX, startY, world), m_health(100) {
		setVisible(true);
	}

	virtual void doSomething();

	int getHealth() const;

private:
	int m_health;
};

class Ice : public Actor {
public:
	Ice(StudentWorld* world, int startX, int startY) :
		Actor(IID_ICE, startX, startY, world) {
		setVisible(true);
	}

	virtual void doSomething() {}
};
#endif // ACTOR_H_
