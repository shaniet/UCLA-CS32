#include "StudentWorld.h"
#include <string>
using namespace std;



// coordinate: 00 bottom left 4,4 top right
//bottom right pixal should be 3,0
// distance is center to ceneter
//set earth to invisible when deleting it
//0,0 1,0 2,0 3, 0
GameWorld* createStudentWorld(string assetDir)
{
    return new StudentWorld(assetDir);
}

// Students:  Add code to this file (if you wish), StudentWorld.h, Actor.h and Actor.cpp

StudentWorld:: StudentWorld(string assetDir)
    : GameWorld(assetDir)
{
    // m_tunnelMan = nullptr; not alive yet
}

StudentWorld::~StudentWorld()
{}

//clear earth function
//64x64 that way the player can go up to the 4 black spaces on the very noth

int StudentWorld:: init(){
    m_tunnelMan = new TunnelMan(this);
 
    for(int i = 0; i < 64; i++){
        for(int j = 0;j< 64; j++){
            if(i >= 30 && i <= 33 && j >= 4 && j <= 59){
                continue;
            }
//            else{
////                m_earth.push_back(new Earth(i,j,this));
//            }
        }
    }
    return GWSTATUS_CONTINUE_GAME;
}

int StudentWorld:: move(){
    m_tunnelMan->doSomething();
    decLives();
        return GWSTATUS_PLAYER_DIED;

}
void StudentWorld:: cleanUp(){
    delete m_tunnelMan;
    for (int i = 0; i < m_actors.size(); i++)
    {
        delete m_actors[i];
    }
}
