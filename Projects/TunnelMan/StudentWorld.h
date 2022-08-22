#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "GameWorld.h"
#include "GameConstants.h"
#include "Actor.h"
#include <string>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <sstream>
#include <iomanip>
// Students:  Add code to this file, StudentWorld.cpp, Actor.h, and Actor.cpp

class StudentWorld : public GameWorld
{
public:
    StudentWorld(std::string assetDir):GameWorld(assetDir){}
//TODO: set players to dead on grid
    virtual int init();
    virtual int move();
    virtual void cleanUp();
    void updateDisplayText();
    void removeEarth(int x, int y);
    void validCoordinate(int startx, int endx, int starty, int endy, int *x, int *y);
    void emptyEarth(int startx, int endx, int starty, int endy, int &x, int &y);
    bool checkBoulder(int x, int y) const;
    void addActor(Actor* a);
    bool checkField(int x, int y, int state);
    bool getTo(int x, int y, int state);
    void setGrid(int x, int y, int val){
        grid[x][y] = val;
    }
    void setNumProt(int num){
        numProt = num;
    }
    int getNumProt(){
        return numProt;
    }
    int getGrid(int x, int y){
        return grid[x][y];
    }
    void simulateProtestor();
    TunnelMan *getTunnelMan() const{
        return m_tunnelMan;
    }

    virtual ~StudentWorld();
private:
    TunnelMan* m_tunnelMan; // pointer to the player
    std::vector<Actor*> m_actors; // vector of pointers to all the actors in the game
    Earth * m_earth[64][64] = {nullptr}; // 2D array of pointers to the earth objects
     int grid[64][64]; // 2D array of integers to store the contents of the grid
    int numTicks; // number of ticks since the game started
    int numBarrelsLeft; // number of barrels left to be collected
    int numProt;
};

#endif // STUDENTWORLD_H_

