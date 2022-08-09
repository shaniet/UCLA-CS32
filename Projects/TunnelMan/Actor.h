#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"
#include "GameConstants.h"

// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp

class StudentWorld;
class Actor: public GraphObject{
public:
    Actor(StudentWorld* world,  int col, int row, int imgId, Direction startDirection, float size, unsigned int depth);
    virtual ~Actor(){}
    virtual void doSomething() = 0;
    virtual void Annoy() = 0;
    StudentWorld* getWorld() const{
        return m_world;
        
    }
public:
    StudentWorld* m_world;
};


class Earth: public Actor{
public:

//    Earth(StudentWorld* world, int startX, int startY, int imageID = TID_EARTH, Direction startDirection = right, float size = .25, unsigned int depth = 3)
//            : Actor(world, imageID, startX, startY, startDirection, size, depth) {setVisible(true);}
     Earth(StudentWorld* world, int col, int row, int imgID = TID_EARTH, Direction startDirection = right, float size = .25, unsigned int depth = 3):Actor(world, imgID, col, row, startDirection, size, depth){setVisible(true);}
    virtual ~Earth(){}
    virtual void doSomething(); //TODO: implement this function
    virtual void Annoy();
};

class TunnelMan: public Actor{
private:
    bool isAlive;
    int setHitPoints, setWater, setSonar, setNuggets;
public:
// todo: declare the tunnelman's setter functions
    TunnelMan(StudentWorld* world, int imgID = TID_PLAYER,int col=30, int row = 60,unsigned int depth = 0, float size = 1,  Direction startDirection = right):Actor(world, imgID, col, row, startDirection, size, depth), isAlive(true),  setHitPoints(10), setWater(5), setSonar(1), setNuggets(0){setVisible(true);}

    virtual void doSomething(); //TODO: implement this function
    virtual void Annoy();
    void canMove(int ch, int dest_x, int dest_y);
    void dec_hit_pts(int dec) {
        setHitPoints -= dec;
        }


        void die() {
            isAlive = false;
        }

        void live() {
            isAlive = true;
        }

        bool getIsAlive() const {
            return isAlive;
        }
    virtual ~TunnelMan(){}
    };




#endif // ACTOR_H_
