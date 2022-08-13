#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"
#include "GameConstants.h"
#include <algorithm>
// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp

// Base class for Game's objects

class StudentWorld;

class Actor: public GraphObject
{
private:
    bool m_life;
    StudentWorld* m_world;
public:
    //Base class constructor
    Actor(int imageID, int startX, int startY, StudentWorld* world, Direction dir = right, double size = 1.0, unsigned int depth = 0): GraphObject(imageID,startX,startY,dir,size,depth),m_life(true),m_world(world){setVisible(true);}
    //base class destructor
    virtual ~Actor() {}
    //pure virtual function to be overridden by derived classes
    void virtual doSomething() = 0;
    // check if the actor is alive
    bool isAlive()const { return m_life; }
    // set the actor's life to false
    void die() { m_life = false; }
    // get the student world pointer
    StudentWorld* getWorld() { return m_world; }
};

class Earth: public Actor
{
public:
    //Earth constructor
    Earth(int startX, int startY, StudentWorld* world): Actor(TID_EARTH,startX,startY,world,right,.25,3){}
   // earth's do something function(doesnt do anything)
    virtual void doSomething(){}
     //Earth destructor
    virtual ~Earth() {}
};



class TunnelMan: public Actor{
private:
    int hitPoints, water, sonar, nugget;
public:
    //TunnelMan constructor
    TunnelMan(StudentWorld* world):Actor(TID_PLAYER,30,60,world),hitPoints(10),water(5),sonar(1),nugget(0){}
    //TunnelMan doSomething function
    virtual void doSomething();
//    virtual void Annoy();
// public helper functions
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
    //public getter functions: get hit points, get water, get sonar, get nugget

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
    //TunnelMan destructor
    virtual ~TunnelMan(){}
};




#endif // ACTOR_H_
