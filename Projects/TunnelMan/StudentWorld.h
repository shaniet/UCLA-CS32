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
    TunnelMan* m_tunnelMan;
	std::vector<Actor*> m_actors;
    Earth * m_earth[64][64];
    int grid[64][64];
    int numTicks;
};

#endif // STUDENTWORLD_H_

