#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"
#include "GameConstants.h"


// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp

// QUESTION: is it okay if i implememnt some functions in the .h file and the cpp file

class StudentWorld;

class Actor: public GraphObject
{
private:
    bool m_life;
    StudentWorld* m_world;
public:
    Actor(int imageID, int startX, int startY, StudentWorld* world, Direction dir = right, double size = 1.0, unsigned int depth = 0): GraphObject(imageID,startX,startY,dir,size,depth),m_life(true),m_world(world){setVisible(true);}
    virtual ~Actor() {}
    void virtual doSomething() = 0;
    bool isAlive()const { return m_life; }
    void die() { m_life = false; }
    StudentWorld* getWorld() { return m_world; }
};

class Earth: public Actor
{
public:
    Earth(int startX, int startY, StudentWorld* world): Actor(TID_EARTH,startX,startY,world,right,.25,3){}
    virtual void doSomething(){}
    virtual ~Earth() {}
};



class TunnelMan: public Actor{
private:
    int hitPoints, water, sonar, nugget;
public:
// todo: declare the tunnelman's setter functions
    TunnelMan(StudentWorld* world):Actor(TID_PLAYER,30,60,world),hitPoints(10),water(5),sonar(1),nugget(0){}
    virtual void doSomething();
//    virtual void Annoy();
    void sethitPoints(int points){
        hitPoints = points;
    }
    void decWater(){
        if(water > 0)
        water--;
    }
    void incWater(){
        water+=5;
    }
    void incSonar(){
        sonar++;
    }
    int getHitPoints() const{
        return hitPoints;
    }
    int getWater() const{
        return water;
    }
    int getSonar() const{
        return sonar;
    }
    int getNugget() const{
        return nugget;
    }
    virtual ~TunnelMan(){}
};




#endif // ACTOR_H_
