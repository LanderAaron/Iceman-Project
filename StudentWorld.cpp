#include "StudentWorld.h"
#include <string>
#include "GameConstants.h"
#include "Actor.h"
#include <algorithm>
#include <sstream>
#include <iostream>
#include <iomanip>

using namespace std;

GameWorld* createStudentWorld(string assetDir)
{
	return new StudentWorld(assetDir);
	
}

// Constructor
StudentWorld::StudentWorld(std::string assetDir) :
	GameWorld(assetDir), m_player(nullptr) {}

// Destructor
StudentWorld::~StudentWorld() {
	cleanUp();
}

//Initialize game world
int StudentWorld::init() {
	// Initializes Ice Field
	for (int x = 0; x < VIEW_WIDTH; x++) 
	{
		for (int y = 0; y < VIEW_HEIGHT; y++) 
		{
			if (y < 56)
				m_iceField[x][y] = new Ice(this, x, y);
			else
				m_iceField[x][y] = nullptr;
		}
	}

	// Creates pre-made tunnel
	//clearIce(28, 53);

	/*int tunnelStartX = 30;
    int tunnelStartY = 63;
    for (int x = tunnelStartX; x < tunnelStartX + 4; ++x)
    {
        for (int y = tunnelStartY - 4; y < tunnelStartY; ++y)
        {
            if (x >= 0 && x < VIEW_WIDTH && y >= 0 && y < VIEW_HEIGHT && m_iceField[x][y] != nullptr)
            {
                delete m_iceField[x][y];
                m_iceField[x][y] = nullptr;
            }
        }
    }*/
	

	m_player = new Player(this, 31, 59);
	m_player->setVisible(true);
	
	return GWSTATUS_CONTINUE_GAME;
}

int StudentWorld::move() {
	m_player->doSomething();
	updateGameStatusText();
	return GWSTATUS_CONTINUE_GAME;
}

void StudentWorld::cleanUp() {
	delete m_player;
	m_player = nullptr;

	for (int x = 0; x < VIEW_WIDTH; x++) 
	{
		for (int y = 0; y < VIEW_HEIGHT; y++) 
		{
			delete m_iceField[x][y];
			m_iceField[x][y] = nullptr;
		}
	}
}

void StudentWorld::removeIceAt(int x, int y) {
	//if (x >= 0 && x < VIEW_WIDTH && y >= 0 && y < VIEW_HEIGHT)
	//{
	//	// Loop over the 4x4 area starting from (x, y)
	//	for (int i = 0; i < 4; i++)
	//	{
	//		
	//		for (int j = 0; j < 4; j++)
	//		{
	//			
	//			int targetX = x + i;
	//			int targetY = y + j;
	//			if (targetX >= 0 && targetX < VIEW_WIDTH && targetY >= 0 && targetY < VIEW_HEIGHT
	//				&& m_iceField[targetX][targetY] != nullptr)
	//			{
	//				delete m_iceField[targetX][targetY];
	//				m_iceField[targetX][targetY] = nullptr;
	//			}
	//		}
	//	}
	//}
}

void StudentWorld::clearIce(int x, int y)
{
	//if ((x >= 0 && x < VIEW_WIDTH) && (y >= 0 && y < VIEW_HEIGHT))
	//{
		// Loop over the 4x4 area starting from (x, y) (may be causing edge case)
		for (int i = 0; i < 4; ++i)
		{
			for (int j = 0; j < 4; ++j)
			{
				int targetX = x + i;
				int targetY = y + j;
				
				//if (targetX >= 0 && targetX < VIEW_WIDTH && targetY >= 0 && targetY < VIEW_HEIGHT
					//&& m_iceField[targetX][targetY] != nullptr)
				if (targetX >= 0 && targetX < VIEW_WIDTH && targetY >= 0 && targetY < VIEW_HEIGHT
					&& m_iceField[targetX][targetY] != nullptr)
					{
						delete m_iceField[targetX][targetY];
						m_iceField[targetX][targetY] = nullptr;
					}
			}
		}

	//}
}

void StudentWorld::removeIceAround(int x, int y, GraphObject::Direction dir) {
	int startX = x;
	int startY = y;

	switch (dir) {
	case GraphObject::left:
		startX = x ;
		startY = y ;
		//
		break;
	case GraphObject::right:
		startX = x ;
		startY = y ;
		//std::cout << "Direction: right, startX: " << startX << ", startY: " << startY << "\n";
		break;
	case GraphObject::up:
		startX = x ;
		startY = y ;
		//std::cout << "Direction: up, startX: " << startX << ", startY: " << startY << "\n";
		break;
	case GraphObject::down:
		startX = x ;
		startY = y ;
		//std::cout << "Direction: down, startX: " << startX << ", startY: " << startY << "\n";
		break;
	default:
		break;
	}

	// Ensure start positions do not go out of bounds (not causing edge case)
	startX = max(-3, startX - 3);
	cout << "X Position: " << startX << endl;
	startY = max(-3, startY - 3);
	cout << "Y Position: " << startY << endl;

	// Calculate the end positions, ensuring they do not go out of bounds (not causing edge case)
	int endX = min(VIEW_WIDTH , startX + 3);
	int endY = min(VIEW_HEIGHT , startY + 3);

	cout << "Direction: " << dir << ", startX: " << startX << ", startY: " << startY << std::endl;
	cout << "End positions: endX: " << endX << ", endY: " << endY << std::endl;

	

	for (int i = startX; i <= endX; ++i) {
		for (int j = startY; j <= endY; ++j) {
			clearIce(i, j);
			// Ensure the coordinates are within valid bounds before attempting to remove ice
			//if (i >= 0 && i < VIEW_WIDTH && j >= 0 && j < VIEW_HEIGHT) {
				
			//}
		}
	}
}

void StudentWorld::updateGameStatusText()
{
	int level = getLevel();
	int lives = getLives();
	int health = m_player->getHealth();
	int water = 5;  
	int gold = 2;   
	int oilLeft = 2; 
	int sonar = 1;  
	int score = getScore();

	ostringstream oss;
	oss << "Lvl: " << level
		<< "  Lives: " << lives
		<< "  Hlth: " << health << "%"
		<< "  Wtr: " << water
		<< "  Gld: " << gold
		<< "  Oil Left: " << oilLeft
		<< "  Sonar: " << sonar
		<< "  Scr: " << setw(6) << setfill('0') << score;

	setGameStatText(oss.str());
}

