#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "GameWorld.h"
#include "GameConstants.h"
#include <string>
#include <vector>
#include "Actor.h"

class StudentWorld : public GameWorld
{
public:
	/*StudentWorld(std::string assetDir)
		: GameWorld(assetDir){
	}*/
	StudentWorld(std::string assetDir);
	virtual int init();
	virtual int move();
	virtual void cleanUp();
	virtual ~StudentWorld();

	void removeIceAt(int x, int y);
	void removeIceAround(int x, int y,
		GraphObject::Direction dir);
		

	void clearIce(int x, int y);

	Ice* getIceAt(int x, int y) const {
		if (x >= 0 && x < VIEW_WIDTH && y >= 0 && y < VIEW_HEIGHT)
			return m_iceField[x][y];
		return nullptr;
	}

private:
	Player* m_player;
	Ice* m_iceField[VIEW_WIDTH][VIEW_HEIGHT];
	void updateGameStatusText();
};

#endif STUDENTWORLD_H_
