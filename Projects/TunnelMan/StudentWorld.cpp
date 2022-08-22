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

    //Initialize Grid to hold objects
    for (int i = 0; i<64; i++)
        {
            for (int j = 0; j<64; j++)
            {
                grid[i][j] = 10;
            }
        }
    
    //Initializing Earth
    
        for (int i = 0; i < 60; i++)
        {
            for (int j = 0; j < 60; j++)
            {
                if (((i >= 30 && i <= 33) && (j >= 4 && j <= 59)))
                {
                 
                }
                
                else {
                    m_earth[i][j] = new Earth(i, j,this);
                     grid[i][j] = TID_EARTH;
                    grid[60][59]=2;
                
                }
            }
        }

    
       

    
    //init boulders
    int B = min(int(getLevel()/2 +2), 9);

    for(int i = 0; i< B; i++){
        int x, y;
        validCoordinate(1, 55, 20, 52, &x,&y); // set to 55 so that it is one before the right column of grid
        for(int j = x; j< x+ 4; j++){
            for(int k = y; k< y+4; k++){
                 if(m_earth[j][k] != nullptr){
                     removeEarth(j, k);
                     m_earth[j][k] = nullptr;
                     grid[j][k] = TID_BOULDER;
                 }
            }
        }
       
        Boulder* boulder = new Boulder(x, y, this);
        m_actors.push_back(boulder);

    }
    
    
    // init gold nuggest
    int G = max(5-int(getLevel() / 2), 2);

    for(int i = 0; i< G; i++){
        int x, y;
        validCoordinate(1, 55, 0, 52, &x, &y);
        grid[x][y]=TID_GOLD;
        Gold* gold = new Gold(x, y, this, false, true, true);
        m_actors.push_back(gold);
    }
    
    //init barrels of oil
    int L = min(int(2 + getLevel()), 21);
    for(int i= 0; i< L; i++){
        int x, y;
        validCoordinate(1, 55, 0, 52, &x, &y); //was 56
        grid[x][y] = TID_BARREL;
        Barrel* barrel = new Barrel(x, y, this);
        getTunnelMan()-> setBarrels(L);
        m_actors.push_back(barrel);
    }
    simulateProtestor();
    return GWSTATUS_CONTINUE_GAME;
}

int StudentWorld::move(){

    numTicks++; // increment the number of ticks
    updateDisplayText();
    m_tunnelMan->doSomething(); // do something for the tunnelman
    
    
    //init regular/hardcore protester
    int T = max(25, int(200 -getLevel()));
  
    int P = min(15, int(2 + getLevel() * 1.5));
    if(numTicks % T == 0&& getNumProt() <= P){ // if the number of ticks simulated is a multiple of the number of protestors
        simulateProtestor();
    }
    
    
    //init water/ sonar
    int G = (getLevel() * 25 + 300);
       bool makeGoodie = (rand()%100)<(1.0/G)*100;
    if(makeGoodie){
        bool probSonar =(rand()%100)<20;
        if(probSonar){
            int T = max(100, int(300 - 10 * getLevel()));
            grid[0][60] = TID_SONAR;
            Sonar* sonar = new Sonar(0, 60, this, T);
            m_actors.push_back(sonar);
        }
        else{
            int W = max(100, int(300 -10* getLevel()));
            int x, y;
            emptyEarth(1, 55, 0, 52, x, y);
            grid[x][y] = TID_WATER_POOL;
            Water* water = new Water(x, y, this, W);
            m_actors.push_back(water);
        }
    }
    
    
       
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
           setNumProt(0);
           
           return GWSTATUS_PLAYER_DIED;//return player died
       }
    if(m_tunnelMan-> getBarrels() == 0){
        m_tunnelMan-> changeScore(1000);
        playSound(SOUND_FINISHED_LEVEL); //play the finished level sound
        setNumProt(0);
         advanceToNextLevel();
        return GWSTATUS_FINISHED_LEVEL;
    }
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
    {        for (int k = 0; k<64; k++)//for each column in the grid
        {
            delete m_earth[j][k]; //delete the earth object
        }
    }
    
    delete m_tunnelMan; //delete the tunnelman
}

void StudentWorld:: emptyEarth(int startx, int endx, int starty, int endy, int &x, int &y){
    
    bool valid = false;
    
    int i, j;

    // randomly place the object within the 60x60 grid
    while(!valid){
        bool earth = true;
        x = startx + ( std::rand() % ( endx - startx + 1) ); // check this numbering(and exclude shaft)
        y = starty + ( std::rand() % ( endy - starty + 1) );
        for(i = 0; i< 4; i++){
            for(j = 0; j< 4; j++){
                if(grid[x+i][y+j] == TID_EARTH){
                    valid = false;
                    earth = false;
                    break;
                    
                }
            }
            if(!earth){
                break;
            }
        
        }
        if (i == 4 && j == 4){
                valid = true;
                break;
        }
            
            
    }
        
        
            
}
    
            
    
        

    
void StudentWorld :: updateDisplayText(){
    int level = getLevel();
    int lives = getLives();
    int health = (m_tunnelMan->getHitPoints()/10.0) * 100;

    int squirts = m_tunnelMan->getWater();
    int gold = m_tunnelMan->getNugget();
    int barrels = m_tunnelMan->getBarrels();
    int sonar = m_tunnelMan->getSonar();
    int score = m_tunnelMan-> getScore();

    ostringstream oss;
        oss.setf(ios::fixed);
    oss << "Lvl: " << setw(2)<< setfill(' ') << level << " Lives: " << lives<< " Hlth: "  << setw(3) << setfill(' ')<< health << "% Wtr: " << setw(2) << setfill(' ') << squirts << " Gld: " << setw(2) << setfill(' ') << gold << " Oil: " << setw(2) << setfill(' ') << barrels << " Sonar: " << setw(2) << setfill(' ') << sonar << " Scr: " << setw(8) << setfill('0') << score;
    string s;
    s = oss.str();
    setGameStatText(s);
    
}
void StudentWorld::removeEarth(int x, int y)
{
    bool flag = false;
    
    for (int i = x; i<x + 4; i++) // for each row in the grid
    {
        for (int j = y; j<y + 4; j++) // for each column in the grid
        {
            if (m_earth[i][j] != nullptr) // if the earth object is not null
            {
                delete m_earth[i][j];
//               m_earth[i][j]->setVisible(false); // set the visibility to false
                m_earth[i][j] = nullptr; // set the earth object to null
                 grid[i][j] = 10; // set the grid content to 10
                flag = true;
               
            }
        }
    }
    if(flag){
    playSound(SOUND_DIG); // play the dig sound
    }
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

void StudentWorld:: simulateProtestor(){
    int probabilityOfHardcore = min(90, int(getLevel() * 10.0 + 30));
    int ticksToWaitBetweenMoves = max(0, int(3 - (getLevel() / 4)));
    int numSquaresToMove = rand() % 53 +8;
    bool Hardcore = (rand()%100)<probabilityOfHardcore;
    if(!Hardcore){
        RegularProtester* regularProtester = new RegularProtester(56, 60, this, numSquaresToMove, ticksToWaitBetweenMoves);
       m_actors.push_back(regularProtester);
        numProt++;
    }
    else{
        int numSquaresToMove = rand() % 53 +8;
        int ticksToWaitBetweenMoves = max(0, int(3 - (getLevel() / 4))); //should be three
        HardcoreProtester* hardcoreProtester = new HardcoreProtester(56, 60, this, numSquaresToMove, ticksToWaitBetweenMoves);
       m_actors.push_back(hardcoreProtester);
        numProt++;
      
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
    // state 0 is for a boulder check if it needs to fall(no earth below
    // state 1 will never come up here( it is just for ticks to pass)
    // state 2 is for boulder to fall (earth,tunnelman, protestors or other boulders)
    // state 3 is for squirt to check for barrier( with earth, protestors, or boulder)
    // state 4 is for barrel/gold to check if it is near tunnelman to become visible
    // state 5 is to check if the tunnelman picked up the barrel/gold/sonar/water pool
   // state 6 is to check what actors are close enough to illuminate using sonar
    // state -1 is to check if protestor picked up gold nugget


   
   if(state == 0){ // check that the row right below boulder is not earth(it will then change to wait state)
       bool flag = true;
        for(int i = 0; i < 4; i++){
            if(m_earth[x+i][y-1] != nullptr){
                flag =  false;
                break;
            }
        }
       return flag;}
   else if (state == 2 || state == 3|| state == 6|| state == -1){
       if(y < 0){// check if we are out of bounds (for boulder falling)
           return true;}
       if (m_earth[x][y] != nullptr){       //check if there is earth below the boulder or if earth in squirt direction
           return true;}
        // check if tunnelMan below boulder
        if ((state ==2)&&(sqrt(pow(x - m_tunnelMan->getX(), 2) + pow(y - m_tunnelMan->getY(), 2)) <= 3)) //if the distance is less than 3
        {
            m_tunnelMan->Annoy(-100); //annoy the actor (should kill)
            return true;
        }
       else{
           for (vector<Actor*>::iterator i = m_actors.begin(); i != m_actors.end(); i++)
            { // 2 is boulder hits protestor, 3 is if squirt hits protestor, 5 is if protestor is near gold to pick it up
                if(state == 2 || state == 3 || state == -1){
                    if ((*i)-> getID() == TID_PROTESTER || (*i)-> getID() == TID_HARD_CORE_PROTESTER){
                            if (sqrt(pow(x - ((*i)->getX()), 2) + pow(y - ((*i)->getY()), 2)) <= 3) //if the distance is less than 3
                                
                            {
                                if(state == 2){ (*i)-> Annoy(-100); m_tunnelMan-> changeScore(500); return true;}
                                //check if protestor below boulder (kill protestor) & return true
                                if(state == 3){
                                    (*i)-> Annoy(-2);
                                    if((*i)-> getID() == TID_PROTESTER && (!(*i)-> isAlive())){
                                        m_tunnelMan-> changeScore(100);
                                    } // if squirt killed regular protestor
                                    else if((*i)-> getID() == TID_HARD_CORE_PROTESTER && (!(*i)-> isAlive())){
                                        m_tunnelMan-> changeScore(250);
                                    }
                                    return true;
                                    
                                }
                                // check if protestor in squirt range (squirt protestor) & return true
                                if(state == -1){
                                    if((*i)-> getID() ==TID_PROTESTER||(*i)-> getID() ==TID_HARD_CORE_PROTESTER ){
                                        (*i)-> Annoy(-45000000); //special case for gold
                                    
                                    return true;
                                    }
                                }
                              
                            }
                    }
                }
                if((*i)-> getID() == TID_BOULDER){

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
      
    else if(state == 4){ // case to show goodies or to check if tunnelman is near protestor
        if (sqrt(pow(x - m_tunnelMan->getX(), 2) + pow(y - m_tunnelMan->getY(), 2)) <= 4) //if the distance is less than 4
            {

                return true;
            
            }
        
    }
    else if (state == 5){ // case to pick up goodies
        if (sqrt(pow(x - m_tunnelMan->getX(), 2) + pow(y - m_tunnelMan->getY(), 2)) <= 3) //if the distance is less than 3
            {
                return true;
            
            }
        
    }
    return false;
}




bool StudentWorld:: getTo(int x, int y, int state){
    // state == 1 is value of up
    // state == 2 is value of down
    // state == 3 is value of left
    // state == 4 is value of right
    // state == 5 is tunnelman
   

    if(state >0 && state <6){
    for(int j = 0; j< 4; j++){ // to check all 4 pixels around
        if(state == 1){ // up
        
            if((y+1 > 60)||(grid[x+j][y+4] == TID_EARTH)|| (grid[x+j][y+4] == TID_BOULDER)){ // if can move up
                return false;
            }

        }
        else if(state == 2){// down
            if((y-1 < 0)||(grid[x+j][y-1] == TID_EARTH)|| (grid[x+j][y-1] == TID_BOULDER)){ // if can move down
                return false;
            }

        }
        else if(state == 3){ //left
            if((x-1 < 0)||(grid[x-1][y+j] == TID_EARTH )|| (grid[x-1][y+j] == TID_BOULDER)){ // if can move left
                return false;
            }

        }
        else if(state == 4){ //right
            if((x+1 > 56)||(grid[x+4][y+j]== TID_EARTH )|| (grid[x+4][y+j]== TID_BOULDER)){ // if can move right
                return false;
            }

        }
      
    
 
   
        else if(state == 5){
            int tmanX =m_tunnelMan->getX();
            int tmanY =m_tunnelMan->getY();
        //if boulder or earth in line of sight return false
      
            if(x== tmanX){
                if(tmanY>y){
                    for(int i = y; i< tmanY; i++){
                        if(grid[x+j][i]== TID_EARTH||grid[x][i]==TID_BOULDER){
                          
                            return false;
                        }
                    }
                  
                }
                else{
                    for(int i = tmanY; i< y; i++){
                        if(grid[x+j][i]== TID_EARTH||grid[x][i]==TID_BOULDER){
                           
                            return false;
                        }
                    }
                }
            }
        
            else{
                if(tmanX>x){
                    for(int i = x; i< tmanX; i++){
                        if(grid[i][y+j]== TID_EARTH||grid[i][y]==TID_BOULDER){

                            return false;
                        }
                    }
                
                }
                else{
                    for(int i = tmanX; i< x; i++){
                        if(grid[i][y+j]== TID_EARTH||grid[i][y]==TID_BOULDER){
                     

                            return false;
                        }
                    }

                }
            }
        }


    }

    }
    return true;

}



