#include "StudentWorld.h"
#include <string>
using namespace std;

//TODO: remove grid array (not necessary)
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
    // for (int i = 0; i < 64; i++){   
    //     for (int j = 0; j < 64; j++)
    //         grid[i][j] = 10;
    // }
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
                    // grid[i][j] = TID_EARTH;
                
                }
            }
        }

    
    //init boulders
    int B = min(int(getLevel()/2 +2), 9);

    for(int i = 0; i< B; i++){
        int x, y;
        validCoordinate(1, 59, 20, 52, &x,&y);
        for(int j = x; j< x+ 4; j++){
            for(int k = y; k< y+4; k++){
                 if(m_earth[j][k] != nullptr){
                     removeEarth(j, k);
                     m_earth[j][k] = nullptr;
                 }
            }
        }
        Boulder* boulder = new Boulder(x, y, this);
        m_actors.push_back(boulder);

    }
    
    // init gold nuggest
    int G = max(int(5-getLevel() / 2), 2);

    for(int i = 0; i< G+10; i++){
        int x, y;
        validCoordinate(1, 59, 0, 52, &x, &y);
        // TODO: push back the gold nuggets
        Gold* gold = new Gold(x, y, this, false, true, true);
        m_actors.push_back(gold);
    }
    
    //init barrels of oil
    int L = min(int(2 + getLevel()), 21);
    for(int i= 0; i< L+10; i++){
        int x, y;
        validCoordinate(1, 59, 0, 52, &x, &y); //was 56
        Barrel* barrel = new Barrel(x, y, this);
        m_actors.push_back(barrel);
    }
    // init sonar kit
    int T = max(100, int(300 - 10 * getLevel()));
    Sonar* sonar = new Sonar(0, 60, this, T);
    m_actors.push_back(sonar);

    // init water pool 
    int W = max(100, int(300 -10* getLevel()));
    Water* water = new Water(56, 60, this, W); //TODO: figure out where this goes in earth

    //TODO: initialize protester (regular and hardcore)
    
    return GWSTATUS_CONTINUE_GAME;
}

int StudentWorld::move(){

    numTicks++; // increment the number of ticks
    //TODO: update the display text 
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
//    if(numBarrelsLeft == 0){
//        playSound(SOUND_FINISHED_LEVEL); //play the finished level sound
//         advanceToNextLevel();
//        return GWSTATUS_FINISHED_LEVEL;
//    }
       return GWSTATUS_CONTINUE_GAME;//return continue game
   
}

void StudentWorld::cleanUp() {
    vector<Actor*>::iterator it;//iterator for the actors vector
    for (it = m_actors.begin(); it != m_actors.end();)//for each actor in the vector
    {
        delete *it; // delete the actor
        it = m_actors.erase(it);//erase the actor from the vector
    }
    for (int j = 0; j<64; j++)//for each row in the grid
    {
        for (int k = 0; k<60; k++)//for each column in the grid
        {
            delete m_earth[j][k]; //delete the earth object
        }
    }
    
    delete m_tunnelMan; //delete the tunnelman
}

void StudentWorld::removeEarth(int x, int y)
{
    
    for (int i = x; i<x + 4; i++) // for each row in the grid
    {
        for (int j = y; j<y + 4; j++) // for each column in the grid
        {
            if (m_earth[i][j] != nullptr) // if the earth object is not null
            {
                delete m_earth[i][j];
//               m_earth[i][j]->setVisible(false); // set the visibility to false
                m_earth[i][j] = nullptr; // set the earth object to null
                // grid[i][j] = 10; // set the grid content to 10
               
            }
        }
    }
    playSound(SOUND_DIG); // play the dig sound
}

void StudentWorld:: validCoordinate(int startx, int endx, int starty, int endy, int *x, int *y){
//used the pathagream theorem to calculate the distance between any two actors in the actor vector
    bool valid = false;
    //distance formula = sqrt( (x2 - x1)^2 + (y2 - y1)^2 )
    // randomly place the object within the 60x60 grid
    while(!valid){
        
        *x = startx + ( std::rand() % ( endx - startx + 1) ); // check this numbering(and exclude shaft)
        *y = starty + ( std::rand() % ( endy - starty + 1) ); // check this numbering and exclude shaft)

        // if actors array is empty, break out of the loop and the object can be placed
        if((*x >= 25 && *x <= 35)){ //&& (*y >= 0 && *y <= 59))
      
            valid = false;
        }
         else if (m_actors.empty()){

            valid = true;
        }
      
        else{
            vector<Actor*>::iterator i; // iterator for the actors vector
            for (i = m_actors.begin(); i != m_actors.end(); i++) //for each actor in the vector
            {
                if (sqrt(pow(*x - ((*i)->getX()), 2) + pow(*y - ((*i)->getY()), 2)) <= 6) //if the distance is less than 6
                {
                    valid = false; //set the valid to false
                    break; //break out of the loop
                }
                
                else valid = true; //else set the valid to true
            }
        }
    }
}

bool StudentWorld:: checkBoulder(int x, int y)const {
  //iterate actors vector
    vector<Actor*>::const_iterator i; // iterator for the actors vector
    for (i = m_actors.begin(); i != m_actors.end(); i++) //for each actor in the vector
    {
        if ((*i)->getID() == TID_BOULDER) //if the actor is a boulder
        {
            if (sqrt(pow(x - ((*i)->getX()), 2) + pow(y - ((*i)->getY()), 2)) <= 3) //if the distance is less than 3
            {
                return false; //return false (meaning there is a boulder and tunnelman cant move there)
            }
        }
    }
    return true; //return true (meaning there is no boulder and tunnelman can move there)

}
   
void StudentWorld:: addActor(Actor* a) {
    m_actors.push_back(a); //add the actor to the actors vector
}

bool StudentWorld:: checkField(int x, int y, int state) {
    // state 0 is for a boulder check for earth below
    // state 2 is for boulder to fall
    // state 3 is for squirt to check for barrier
    // state 4 is for barrel/gold to check if it is near tunnelman to become visible
    // state 5 is to check if the tunnelman picked up the barrel/gold/sonar/water pool 
   // state 6 is to check what actors are close enough to illuminate using sonar


    // check that the row right below boulder is not earth(it will then change to wait state)
   if(state == 0){
       bool flag = true;
        for(int i = 0; i < 4; i++){
            if(m_earth[x+i][y-1] != nullptr){
                flag =  false;
                break;
            }
        }
       return flag;}
   else if (state == 2 || state == 3|| state == 6){
       if(y < 0){// check if we are out of bounds (for boulder falling)
           return true;}
   
       //check if there is earth below the boulder or if earth in squirt direction
       if (m_earth[x][y] != nullptr){
           cout<< "i am at earth not null";
           return true;}
        // check if tunnelMan below boulder
        if(state ==2){
            if (sqrt(pow(x - m_tunnelMan->getX(), 2) + pow(y - m_tunnelMan->getY(), 2)) <= 3) //if the distance is less than 3
            {
                m_tunnelMan->Annoy(-100); //annoy the actor (should kill)//TODO: MAKE SURE THIS KILLS
                return true;}
        }
       else{
           for (vector<Actor*>::iterator i = m_actors.begin(); i != m_actors.end(); i++)
            {
                if ((*i)-> getID() == TID_PROTESTER){
                        if (sqrt(pow(x - ((*i)->getX()), 2) + pow(y - ((*i)->getY()), 2)) <= 3) //if the distance is less than 3
                        {
                            if(state == 2){ (*i)-> Annoy(-100);} //check if protestor below boulder
                            if(state == 3){// check if protestor in squirt range

                                (*i)-> Annoy(-2);
                                std:: cout<<"hello regular";
                                 return true;
                            }
                            if(state == 5){
                                return true;
                            }
                        }
                }
                if((*i)-> getID() == TID_HARD_CORE_PROTESTER){
                    //check if protestor below boulder
                        if (sqrt(pow(x - ((*i)->getX()), 2) + pow(y - ((*i)->getY()), 2)) <= 3) //if the distance is less than 3
                        {
                            //check if hardcore protestor below boulder
                            if(state == 2){ (*i)-> Annoy(-100);}
                            // check if hardcore protestor in squirt range(return true if it is)
                            if(state == 3){ 
                                (*i)-> Annoy(-2);
                                std:: cout<<"hello hardcore";
                                return true;
                            }
                            if(state == 5){
                                return true;
                            }
                        }
                }
                if((*i)-> getID() == TID_BOULDER){
                    std:: cout<<"hello boulder CHECK";
                 
                    //distance is less than 3
                    if (sqrt(pow(x - ((*i)->getX()), 2) + pow(y - ((*i)->getY()), 2)) <= 3){ //if the
                        //check if is below DIFFERENT boulder
                        if(state == 2){
                            if(x != (*i)->getX() && y !=(*i)->getY()){
                                return true;
                                }
                        }
                        // check if squirt is facing boulder
                        if(state == 3){
                            std:: cout<<"hello boulder";
                            return true;
                        }
                    }
                }
                if(state == 6){ // case to illuminate goodies
                    if((*i)-> getID() == TID_BARREL || (*i)-> getID() == TID_GOLD){
                        if (sqrt(pow(x - ((*i)->getX()), 2) + pow(y - ((*i)->getY()), 2)) <= 12) //if the distance is less than 12
                        {
                            (*i)-> setOwnVisible(true);
                             
                        }
                    }
                }
            }
       }
   }
      
    else if(state == 4){ // case to show goodies
        if (sqrt(pow(x - m_tunnelMan->getX(), 2) + pow(y - m_tunnelMan->getY(), 2)) <= 4) //if the distance is less than 3
            {

                return true;
            
            }
        
    }
    else if (state == 5){ // case to pick up goodies
        std::cout<<"made it";
        if (sqrt(pow(x - m_tunnelMan->getX(), 2) + pow(y - m_tunnelMan->getY(), 2)) <= 3) //if the distance is less than 4
            {
                std:: cout<< "found it!";
                return true;
            
            }
        
    }
    return false;
}



