#include "Actor.h"
#include "StudentWorld.h"
#include "GameConstants.h"

void Player::doSomething() {
	int ch;
	if (getWorld()->getKey(ch))
	{
		int newX = getX();
		int newY = getY();
		GraphObject::Direction dir = getDirection();

		switch (ch) {
		case KEY_PRESS_LEFT:
			dir = left;
			if (newX > 0) newX--;
			break;
		case KEY_PRESS_RIGHT:
			dir = right;
			if (newX < VIEW_WIDTH - 1) newX++;
			break;
		case KEY_PRESS_UP:
			dir = up;
			if (newY < VIEW_HEIGHT - 1) newY++;
			break;
		case KEY_PRESS_DOWN:
			dir = down;
			if (newY > 0) newY--;
			break;
		}
		getWorld()->removeIceAround(newX, newY, dir);
		setDirection(dir);


		moveTo(newX, newY);
	}
}

int Player::getHealth() const {
	return m_health;
}

