#include "StudentWorld.h"
#include <string>
using namespace std;


//Notes:
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


// student world destructor
StudentWorld::~StudentWorld()
{}

int StudentWorld:: init(){
    numTicks = 0; // set the number of ticks to 0
    
    
    //initialize tunnelMan
    m_tunnelMan = new TunnelMan(this);
    
    //initialize grid 
    //Initializing Earth
        for (int i = 0; i < 64; i++)
        {
            for (int j = 0; j < 60; j++)
            {
                if ((i >= 30 && i <= 33) && (j >= 4 && j <= 59))
                {
                    
                }
                else {
                    m_earth[i][j] = new Earth(i, j,this);
                    grid[i][j] = TID_EARTH;
                }
            }
        }
    
    
    //init boulders
    int B = min(int(getLevel()/2 +2), 9);
    
    // init gold nuggest
    int G = max(int(5-getLevel() / 2), 2);
    
    //init barrels of gold
    int L = min(int(2 + getLevel()), 21);
    
    
    return GWSTATUS_CONTINUE_GAME;
}


int StudentWorld::move(){

    numTicks++; // increment the number of ticks
        
    m_tunnelMan->doSomething(); // do something for the tunnelman
       
       if (!m_actors.empty()) //if the actors vector is not empty
       {
           vector<Actor*>::iterator i; // iterator for the actors vector
           
           
           for (i = m_actors.begin(); i != m_actors.end(); i++) //for each actor in the vector
           {
               if ((*i)->isAlive()) //if the actor is alive
               {
                   (*i)->doSomething(); //do something for the actor
               
               }
           }
           
           //Remove dead objects
           for (i = m_actors.begin(); i != m_actors.end();) // for each actor in the vector
           {
               if (!(*i)->isAlive()) //if the actor is not alive
               {
                   delete *i; //delete the actor
                   i = m_actors.erase(i); //erase the actor from the vector
               }
               else i++; //else move on to the next actor
           }
       }
       
    if (!m_tunnelMan->isAlive())
       {
           playSound(SOUND_PLAYER_GIVE_UP); //play the player give up sound
           decLives(); //decrement the number of lives
           return GWSTATUS_PLAYER_DIED;//return player died
       }
       return GWSTATUS_CONTINUE_GAME;//return continue game
   }


void StudentWorld::cleanUp() {
    vector<Actor*>::iterator i;//iterator for the actors vector
    for (i = m_actors.begin(); i != m_actors.end();)//for each actor in the vector
    {
        delete *i; // delete the actor
        i = m_actors.erase(i);//erase the actor from the vector
    }
    for (int k = 0; k<64; k++)//for each row in the grid
    {
        for (int l = 0; l<60; l++)//for each column in the grid
        {
            delete m_earth[k][l]; //delete the earth object
        }
    }
    
    delete m_tunnelMan; //delete the tunnelman
}
void StudentWorld::setGridContent(int x, int y, int ID)
{
    grid[x][y] = ID; //set the grid content to the ID
}
void StudentWorld::removeEarth(int x, int y)
{
    
    for (int i = x; i<x + 4; i++) // for each row in the grid
    {
        for (int j = y; j<y + 4; j++) // for each column in the grid
        {
            if (m_earth[i][j] != nullptr) // if the earth object is not null
            {
                delete m_earth[i][j]; //delete the earth object
                m_earth[i][j] = nullptr; // set the earth object to null
                grid[i][j] = 10; // set the grid content to 10
               
            }
        }
    }
    playSound(SOUND_DIG); // play the dig sound
}
