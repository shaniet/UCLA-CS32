#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "GameWorld.h"
#include "GameConstants.h"
#include "Actor.h"
#include <string>
#include <vector>
#include <cmath>
#include <sstream>
#include <iomanip>
// Students:  Add code to this file, StudentWorld.cpp, Actor.h, and Actor.cpp

class StudentWorld : public GameWorld
{
public:
    StudentWorld(std::string assetDir):GameWorld(assetDir){}

    virtual int init();
    virtual int move();
    virtual void cleanUp();
    void removeEarth(int x, int y);
    void setGridContent(int x, int y, int ID);
    TunnelMan* gettunnelMan() const;
    virtual ~StudentWorld();
private:
    TunnelMan* m_tunnelMan; // pointer to the player
	std::vector<Actor*> m_actors; // vector of pointers to all the actors in the game
    Earth * m_earth[64][64] = {nullptr}; // 2D array of pointers to the earth objects
    int grid[64][64]; // 2D array of integers to store the contents of the grid
    int numTicks; // number of ticks since the game started
};

#endif // STUDENTWORLD_H_

