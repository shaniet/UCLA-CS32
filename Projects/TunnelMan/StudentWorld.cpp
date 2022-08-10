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



StudentWorld::~StudentWorld()
{}

int StudentWorld:: init(){
    
    numTicks = 0;
       for (int i = 0; i<64; i++)
       {
           for (int j = 0; j<61; j++)
           {
               grid[i][j] = 10;
           }
       }
    m_tunnelMan = new TunnelMan(this);
        //Initializing Earth
        for (int i = 0; i < 64; i++)
        {
            for (int j = 0; j < 60; j++)
            {
                //Shaft
                if ((i >= 30 && i <= 33) && (j >= 4 && j <= 59))
                {
                    
                }
                else {
                    m_earth[i][j] = new Earth(i, j,this);
                    grid[i][j] = TID_EARTH;
                }
            }
        }
    return GWSTATUS_CONTINUE_GAME;
}


int StudentWorld::move(){
    numTicks++;
       
    m_tunnelMan->doSomething();
       
       if (!m_actors.empty())
       {
           vector<Actor*>::iterator i;
           
           
           for (i = m_actors.begin(); i != m_actors.end(); i++)
           {
               if ((*i)->isAlive())
               {
                   (*i)->doSomething();
                   //If tunnelman dies
               }
           }
           
           //Remove dead objects
           for (i = m_actors.begin(); i != m_actors.end();)
           {
               if (!(*i)->isAlive())
               {
                   delete *i;
                   i = m_actors.erase(i);
               }
               else i++;
           }
       }
       
    if (!m_tunnelMan->isAlive())
       {
           playSound(SOUND_PLAYER_GIVE_UP);
           decLives();
           return GWSTATUS_PLAYER_DIED;
       }
       return GWSTATUS_CONTINUE_GAME;
   }


void StudentWorld::cleanUp() {
    vector<Actor*>::iterator i;
    for (i = m_actors.begin(); i != m_actors.end();)
    {
        delete *i;
        i = m_actors.erase(i);
    }
    for (int k = 0; k<64; k++)
    {
        for (int l = 0; l<60; l++)
        {
            delete m_earth[k][l];
        }
    }
    
    delete m_tunnelMan;
}
void StudentWorld::setGridContent(int x, int y, int ID)
{
    grid[x][y] = ID;
}
void StudentWorld::removeEarth(int x, int y)
{
    
    for (int i = x; i<x + 4; i++)
    {
        for (int j = y; j<y + 4; j++)
        {
            if (m_earth[i][j] != nullptr)
            {
                delete m_earth[i][j];
                m_earth[i][j] = nullptr;
                grid[i][j] = 10;
                playSound(SOUND_DIG);
            }
        }
    }
}
