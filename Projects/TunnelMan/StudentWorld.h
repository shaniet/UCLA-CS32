#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "GameWorld.h"
#include "GameConstants.h"
#include "Actor.h"
#include <string>
#include <vector>

// Students:  Add code to this file, StudentWorld.cpp, Actor.h, and Actor.cpp

class StudentWorld : public GameWorld
{
public:
    StudentWorld(std::string assetDir);

    virtual int init();
    virtual int move();

    virtual void cleanUp();
    virtual ~StudentWorld();
private:
    TunnelMan* m_tunnelMan;
	std::vector<Actor*> m_actors;
	std:: vector<Earth*> m_earth;
};

#endif // STUDENTWORLD_H_
