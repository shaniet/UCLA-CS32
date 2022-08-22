#include "Actor.h"
#include "StudentWorld.h"
#include <algorithm>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <set>
using namespace std;

// Students:  Add code to this file (if you wish), Actor.h, StudentWorld.h, and StudentWorld.cpp


//NOTES;
//allowed to use isvisible and getid
//waterpool(same bounds as boulder but can span in the middle shaft(0-60,0-56)
//gold((0-60,0-56)except shaft)<- same for barrel have the same bounds
//sonar can spawn upper left

// protestors ticks to wait and num squares between (calculate every single time) in the do something()
//check if non resting tiks are not greater than 15
//bfs/dfs advice: midterm had outline for searching algorithm (when you find the path you can create a 2d array of discover points and as you figure out a solution you can mark off the coordinates accordingly
    //bool/char array of earth and check if visible for earth its essentially a wall
    //start them at false / dequeing
//protestor requirment wording pg41 point 5: verticle line of sight, no earth (loop through earth objects)
//differentia different actors in a vector-> get the id for any actor

void TunnelMan::doSomething(){
    //if dead, exit function
    if(!isAlive()){
        return;
        
    }
 
    //create a switch statment to check for user input
    int ch;


    if(getWorld()-> getKey(ch)){
        switch(ch)
     

        {
            case KEY_PRESS_RIGHT:

                // check if the tunnelman is within the bounds of the screen
                if((getX() <56 && getDirection() == right)&& (getWorld ()->checkBoulder(getX()+1,getY()))){
                    // if so move the tunnelman right
                    moveTo(getX() +1, getY());
                    //remove earth from the screen
                    getWorld()->removeEarth(getX(), getY());

                }
                // set the direction to right
                    setDirection(right);
         
                break;
            case KEY_PRESS_LEFT:
          
                // check if the tunnelman is within the bounds of the screen
                if((getX() >0 && getDirection() == left)&&(getWorld()->checkBoulder(getX()-1,getY()))){
                    // if so move the tunnelman left
                    moveTo(getX() -1, getY());
                    //remove earth from the screen
                    getWorld()->removeEarth(getX(), getY());
                }
                // set the direction to left
                    setDirection(left);
                break;
            case KEY_PRESS_UP:
          
                if((getY() <60 && getDirection() == up)&&(getWorld()->checkBoulder(getX(),getY()+1))){
                    // if so move the tunnelman up
                    moveTo(getX(), getY()+1);
                    //remove earth from the screen
                    getWorld()->removeEarth(getX(), getY());
                }
                // set the direction to up
                    setDirection(up);
                break;
            case KEY_PRESS_DOWN:
           
                if((getY() >0 && getDirection() == down)&&(getWorld()->checkBoulder(getX(),getY()-1))){
                    // if so move the tunnelman down
                    moveTo(getX() , getY()-1);
                    //remove earth from the screen
                    getWorld()->removeEarth(getX(), getY());

                }
                // set the direction to down
                    setDirection(down);
               
                break;
            case KEY_PRESS_ESCAPE:
                die();
           
//                kill player
                break;
            case KEY_PRESS_SPACE:
                {
                     if(getWater() > 0){

                         changeWater(-1);//decrement water

                        Squirt *s = new Squirt(getX(), getY(), getWorld(), getDirection()); //create a new squirt
                        getWorld()->addActor(s); //add the squirt to the actor vector

                     }
               
                    break;
                }
            case 'Z':
            case 'z':

                if(getSonar() > 0){ //if there is a sonar
                    getWorld()-> checkField(getX(), getY(),6); // illuminate the field within radius
                    getWorld()-> playSound(SOUND_SONAR);
                    changeSonar(-1); // decrement sonar
                }
                    break;
            case KEY_PRESS_TAB:
                {
                    if (getNugget() > 0){ // if there is a nugget

                        Gold *gold = new Gold(getX(), getY(), getWorld(), true, false, false); // create a new gold
                        getWorld()->addActor(gold); // add the gold to the actor vector
                        getWorld()->setGrid(getX(),getY(), TID_GOLD);
                        changeNugget(-1); // decrement nugget
                    }

                    break;
                    
                }
        }
    }
}

void TunnelMan::Annoy(int amt){
    changeHitPoints(amt);
}

void Boulder::doSomething(){
    if(!isAlive()){
        return;
    }
    else if(getState() == 0){ // boulder is stable
        if(getWorld()-> checkField(getX(), getY(), 0)){ // check if there is earth below
            setState(1); // set the state to falling if there is no earth below
            setWaitTicks(30); // set the wait ticks to 30
        }
    }
    else if(getState () == 1){ //if waiting
        if(getTicks() <1){ // check if wait is done
            getWorld()->setGrid(getX(), getY(), 10);
            setState(2); // set the state to falling
        }
        else{
            decTicks(); // if not decrement the wait ticks
            
        }
    }
    else if(getState() == 2){ // if falling

        if(!(getWorld()-> checkField(getX(), getY(), 2))){ // check appropriate objects below boulder
       
            moveTo(getX(), getY()-1); // move the boulder down
        }
        else{
        setState(-1); // set the state to dead
        }
    }
    else{
        die(); // if dead, kill the boulder
    }
    
}

void Squirt::doSomething(){
   if(!isAlive()){
       return;
   }
    else{
        if(getTravel () >0){ // if there is travel left
            if(getDirection() == up && getY()<60){ // if traveling up and not at the top of the screen
                if(!(getWorld()-> checkField(getX(), getY()+1, 3))){ // check for the appropriate objects above the squirt
                    moveTo(getX(), getY()+1); // move the squirt up
                    decTravel(); // decrement travel
                }
                else{
                    getWorld()->playSound(SOUND_PLAYER_SQUIRT);
                    die(); // if there is an object blocking the squirt, kill the squirt
                    return;
                }
            }
            else if(getDirection() == down && getY()>0){ // if traveling down and not at the bottom of the screen
                if(!(getWorld()-> checkField(getX(), getY()-1, 3))){ // check for the appropriate objects below the squirt
                    moveTo(getX(), getY()-1); // move the squirt down
                    decTravel(); // decrement travel
                }
                else{
                    getWorld()->playSound(SOUND_PLAYER_SQUIRT);
                    die(); // if there is an object blocking the squirt, kill the squirt
                    return;
                }
            }
            else if(getDirection() == right&& getX()<56){ // if traveling right and not at the right of the screen
                if(!(getWorld()-> checkField(getX()+1, getY(), 3))){    // check for the appropriate objects to the right of the squirt
                    moveTo(getX()+1, getY()); // move the squirt right
                    decTravel(); // decrement travel
                }
                else{
                    getWorld()->playSound(SOUND_PLAYER_SQUIRT);
                    die(); // if there is an object blocking the squirt, kill the squirt
                    return;
                }
               
            }
            else if(getDirection() == left&& getX()>0){ // if traveling left and not at the left of the screen
                if(!(getWorld()-> checkField(getX()-1, getY(), 3))){ // check for the appropriate objects to the left of the squirt
                    moveTo(getX()-1, getY()); // move the squirt left
                    decTravel(); // decrement travel
                }
                else{
                    getWorld()->playSound(SOUND_PLAYER_SQUIRT);
                    die(); // if there is an object blocking the squirt, kill the squirt
                    return;
                }
            }
            
            else{
                decTravel(); // if the squirt is at the edge of the screen, decrement travel
            }
           
        }
        else{
            getWorld()->playSound(SOUND_PLAYER_SQUIRT);
            die();
        }
    }
}
        
void Barrel:: doSomething(){
    if(!isAlive()){
        return;
    }
    if((!getVisible()) && getWorld()->checkField(getX(), getY(), 4)){ // if the barrel is not visible and tunnelMan is within radius
        setOwnVisible(true); // set the barrel to visible
        return ;
    }
    if((getVisible()) && (getWorld()->checkField(getX(), getY(), 5))){ // if the barrel is visible and tunnelMan is within radius
        getWorld()->getTunnelMan()->changeScore(1000); // increase the score by 1000
        getWorld()->setGrid(getX(), getY(), 10);
        die(); // kill the barrel
        getWorld()-> playSound(SOUND_FOUND_OIL); // play the sound
        getWorld()-> getTunnelMan()->changeBarrels(-1); // increase the number of barrels by 1
        return;
        
    }
}

void Gold:: doSomething(){
    if(!isAlive()){
        return;
    }
    if((getState() && !getVisible()) && getWorld()->checkField(getX(), getY(), 4)){ // if the gold is not visible and tunnelMan is within radius
        setOwnVisible(true); // set the gold to visible
        return ;
    }
    if((getState() && getVisible()) && (getWorld()->checkField(getX(), getY(), 5))){ // if the gold is visible and tunnelMan is within radius
        if(getState() && getPickupT()){
             getWorld()->getTunnelMan()->changeScore(10);
            getWorld()->setGrid(getX(), getY(), 10);
            die();
            getWorld()-> playSound(SOUND_GOT_GOODIE);
            getWorld()->getTunnelMan()->changeNugget(1);
            return;
        }
    }
     if(getTicks()>0){ // if the tick time is still going
         if(!getState() && getWorld()->checkField(getX(), getY(), -1)){ // if the gold is in temp state and protestor is within radius
             getWorld()->setGrid(getX(), getY(), 10);
            die(); // kill the gold to pick it up
            getWorld() -> getTunnelMan()->changeScore(25); // increase the score by

            return;
        }
        else{
            decTicks(); // if not, decrement the tick time
        }

     }
     else if(!getState() &&getTicks() <= 0){ // if the tick time is done and the gold is in temp state
         getWorld()->setGrid(getX(), getY(), 10);
         die(); // kill the gold
        return;
     }
    

}

void Sonar:: doSomething(){
    if(!isAlive()){
        return;
    }
    if(getTicks()>0){ // if the tick time is still going
        if(getWorld()->checkField(getX(), getY(), 5)){ // if tunnelMan is within radius
            getWorld()->setGrid(getX(), getY(), 10);
            die(); // kill the sonar to pick it up
            getWorld()-> playSound(SOUND_GOT_GOODIE); // play the sound
            getWorld()->getTunnelMan()->changeSonar(1); // increase the number of sonars by 1
            getWorld()->getTunnelMan()->changeScore(75); // increase the score by 75
            return ;
        }
        else{
            decTicks(); // if not, decrement the tick time
        }
      
    }
    else if(getTicks() <= 0){ // if the tick time is done
        getWorld()->setGrid(getX(), getY(), 10);
        die();  // kill the sonar
    }
    
    
}

void Water:: doSomething(){
    if(!isAlive()){
        return;
    }
    if(getTicks()>0){ // if the tick time is still going
        if(getWorld()->checkField(getX(), getY(), 5)){ // if tunnelMan is within radius
            getWorld()->setGrid(getX(), getY(), 10);
            die(); // kill the water to pick it up
            getWorld()-> playSound(SOUND_GOT_GOODIE); // play the sound
            getWorld()->getTunnelMan()->changeWater(5); // increase the number of water by 5
            getWorld()->getTunnelMan()->changeScore(100); // increase the score by 100
            return ;
        }
        else{
            decTicks(); // if not, decrement the tick time
        }
      
    }
    else if(getTicks() <= 0){ // if the tick time is done
        getWorld()->setGrid(getX(), getY(), 10);
        die();
    }
    
    
}

void Protester:: doSomething(){
    if(!isAlive()){
        return;
    }
    
     if (getState() == 0){ // 1.

         if(getTicksProt() > 0){
               decTicksProt();
            return;
         }
         else{
             setState(1);
         }
     }
     if(getState() == 2){
         getWorld()-> getTunnelMan()-> changeScore(100);
         int track[64][64];
         BFS(track, getX(), getY());
         stack<Direction> loc = Moveit(track, getX(), getY());
         if(!loc.empty()){
            
             setDirection(loc.top());
             int addX = 0;
             int addY = 0;

             if(loc.top() == right){
                 addX = 1;
             }
             else if(loc.top() == left){
                 addX = -1;
             }
             else if(loc.top() == up){
                 addY = 1;
             }
             else{
                 addY = -1;
             }
             moveTo(getX()+addX, getY()+addY);
             loc.pop();
            }
       

        

       
         if(getX()>= 56 && getY() >= 60){
             die();
         }
        return;
     }
    
    //4.
     if(getState() == 1 && (checkProtestor(getX(), getY(), getDirection(), 1))){ // if the protestor is in the tunnelMan's radius and facing direction
         if(getTicksProt()>0){ // if the tick time is still going
            decTicksProt(); // decrement the tick time
            return;
        }
        else{
            getWorld()-> playSound(SOUND_PROTESTER_YELL); // play the sound
            getWorld() -> getTunnelMan()->Annoy(-2);
            setTicksProt(15);
            return;
        }

     }
    
    //5.
     if((getState() == 1) && checkProtestor(getX(), getY(), getDirection(), 2)){ // if the protestor is in horiontal and vertical line

        
             if(getY() == getWorld()->getTunnelMan()-> getY()){

                 setDirection(getDir(getX(), getY(), 1));
             }
             if(getX() == getWorld()->getTunnelMan()-> getX()){

                 setDirection(getDir(getX(), getY(), 2 ));
             }


                // set the direction to face tunnelman
                if (getDirection() == up){
                    moveTo(getX(), getY()+1);
                }
                else if (getDirection() == down){
                    moveTo(getX(), getY()-1);
                }
                else if (getDirection() == left){
                    moveTo(getX()-1, getY());
                }
                else{// (getDirection() == right){
                    moveTo(getX()+1, getY());
                }
             
                    
                    setNumSquaresToMoveInCurrentDirection(0);
         
             setTicksProt(getOriginalTicks());
             setState(0);


         return;
     }

    
   // 6.
     if((getState() == 1) && !(checkProtestor(getX(), getY(), getDirection(), 2))){ // if the protestor is not in the tunnelMan's radius

         // check if you cant see the tunnelman,
         if(getNumSquaresToMoveInCurrentDirection() <= 0){
             setDirection(randDir()); // set the direction to a random direction
             setNumSquaresToMoveInCurrentDirection(rand() % 53 +8);

         }
         else{
             decNumSquaresToMoveInCurrentDirection();
         }

     }


////    7.
    if((getState() == 1) && (((getDirection() == left||getDirection() == right)&& getWorld()-> getTo(getX(), getY(),1)&&getWorld()-> getTo(getX(), getY(),2))|| ((getDirection() == up||getDirection() == down)&&getWorld()-> getTo(getX(), getY(),3)&&getWorld()-> getTo(getX(), getY(),4)))){ // if at intersection move perpendicular ( can move up and down or right and left)
         if(getCountPerp() <= 0){
             
         bool canMove = false;
             int randNum = rand() % 53 +8;
             setNumSquaresToMoveInCurrentDirection(randNum);
         while(!canMove){
             int randDir = rand() % 2;
             if(getDirection() == right || getDirection() == left){
                 if(randDir == 0){
                     setDirection(up);
                 }
                 else{
                     setDirection(down);
                 }
             }
             else if(getDirection() == up || getDirection() == down){
                 if(randDir == 0){
                     setDirection(right);
                 }
                 else{
                     setDirection(left);

                 }
             }
             if(getWorld()->getTo(getX(), getY(), getDirection())){
                         setDirection(up);
                         break;
                     }
         }
             setCountPerp(200);
        }
        else{
            decCountPerp();
        }
    }
//
//    //7.
    if((getState() == 1) && getWorld()->getTo(getX(), getY(), getDirection())){
  

            if(getDirection() == up){
                moveTo(getX(), getY()+1);
            }
            else if(getDirection() == down){
                moveTo(getX(), getY()-1);
            }
            else if(getDirection() == left){
                moveTo(getX()-1, getY());
            }
            else if(getDirection() == right){
                moveTo(getX()+1, getY());
            }
            setTicksProt(getOriginalTicks());
        setState(0);

    }

//    //9.
    else {
        setNumSquaresToMoveInCurrentDirection(0);
        return;

    }
    return;
}








bool Protester:: checkProtestor(int x, int y, Direction dir, int  state){
    //state = 1, checks for tunnelman in range
    //state = 2 checks if tunnelman in vertical or horizontal line
    if(state == 1){ // check if protester is in range to shout at tunnelman
        if (sqrt(pow(x -getWorld()->getTunnelMan()-> getX(), 2) + pow(y - getWorld()->getTunnelMan()-> getY(), 2)) <= 4) {
            if(dir == getDir(x, y, -1)){
                return true;
            }
        }

    }
    if(state == 2){ // check if protestor is in horizontal or vertical range to tunnelman
        
        if ((y == getWorld()->getTunnelMan()-> getY() || x == getWorld()->getTunnelMan()-> getX()) &&  (sqrt(pow(x - getWorld()->getTunnelMan()->getX(), 2) + pow(y - getWorld()->getTunnelMan()->getY(), 2)) > 4) && (getWorld()->getTo(x, y, 5))){
            return true;
        }
    }

    return false; // false if none of the above are true
}


Actor::Direction Protester:: getDir(int x, int y, int XorY){
    //if tunnelman is above protestor, set dir to up
    if(XorY == 2 || XorY == -1){ // smae vertical level
        if((getWorld()-> getTunnelMan()-> getY() )>  y){
            return up;
        }
        //if tunnelman is below protestor, set dir to down
        else if(getWorld()-> getTunnelMan()-> getY() < y){
            return down;
        }
    }
    else if(XorY == 1 ||  XorY == -1){ // if we are on same horizontal level
    //if tunnelman is to the left of protestor, set dir to left
        if(getWorld()-> getTunnelMan()-> getX() < x){
            return left;
        }
        //if tunnelman is to the right of protestor, set dir to right
        else if(getWorld()-> getTunnelMan()-> getX() > x){
            return right;
        }
    }
   
        return getDirection();


}

Actor::Direction Protester:: randDir(){
    bool valid = false;
    Direction dir;
    int check;
    while(!valid){
        unsigned int randDir = rand() % 4 + 1;
        if(randDir == 1){
            dir =  up;
            check = 1;//
        }
        else if(randDir == 2){
            dir =  down;
            check = 2;
        }
        else if(randDir == 3){
            dir =  left;
            check = 3;
             
        }
        else {
            dir =  right;
            check = 4;
             
        }
        
         if(getWorld()->getTo(getX(), getY(), check)){
                valid = true;

             break;
        }
        
    }
    return dir;
}



void Protester::Annoy(int amt){
    if(amt == -45000000){ //if protestor found gold
        getWorld()-> playSound(SOUND_PROTESTER_FOUND_GOLD);
        setState(2);
        return;
    }
//    if(getTicksProt()<=0){
        changeHitPoints(amt);
    
    
    if(getHitPoints()<=0){ //if protestor dies any way
        getWorld()-> playSound(SOUND_PROTESTER_GIVE_UP);
        setTicksProt(0);
        setState(2);
    }
    else{ // if protestor is annoyed but still alive
        getWorld()-> playSound(SOUND_PROTESTER_ANNOYED);
        int level = getWorld()->getLevel();
        int N = max(50, 100 - level * 10);
        setTicksProt(N);
        setState(0);
    }

}



 
//// Function to check if a cell
//// is be visited or not
bool Protester:: isValid(int track[][64],int x, int y)
{
    // If cell lies out of bounds
    if (x < 0 || y < 0
        || x > 56 || y > 60 || getWorld()-> getGrid(x,y) == TID_EARTH|| getWorld()-> getGrid(x,y) == TID_BOULDER)
        return false;

    // If cell is already visited
    if (track[x][y] != 0)
        return false;

    // Otherwise
    return true;
}

// Function to perform the BFS traversal
void Protester:: BFS(int track[][64], int x, int y)

{

    for (int i = 0; i < 64; i++)
        {
            for (int j = 0; j < 64; j++)
            {
                track[i][j] = 0;
            }
        }
    // Direction vectors
    int dRow[] = { -1, 0, 1, 0 };
    int dCol[] = { 0, 1, 0, -1 };
    // Stores indices of the matrix cells
    queue<pair<int, int> > q;

    // Mark the starting cell as visited
    // and push it into the queue
    q.push({ x, y });
    int count = 1;
    track[x][y] = count;
    count ++;

    // Iterate while the queue
    // is not empty
    while (!q.empty()) {

        pair<int, int> cell = q.front();
        int first = cell.first;
        int second = cell.second;


        q.pop();
        if(getX() == 56 && getY() == 60){
            break;
        }
        // Go to the adjacent cells
        for (int i = 0; i < 4; i++) {

            int adjx = first + dRow[i];
            int adjy = second + dCol[i];

            if (isValid(track, adjx, adjy)) {
                q.push({ adjx, adjy });
                track[adjx][adjy] = count;// track[x][y]+1;
                count ++ ;
            }
        }


    }
}

stack<Actor::Direction> Protester:: Moveit(int track[][64], int x, int y){
    stack<Direction> loc;
    int dRow[] = { -1, 0, 1, 0 };
    int dCol[] = { 0, 1, 0, -1 };
    int ex = 56;
    int ey = 60;
    bool flag = true;
    while(flag){

        int shortest = track[ex][ey];
        int dir;
        for (int i = 0; i < 4; i++) {

            int adjx = ex + dRow[i];
            int adjy = ey + dCol[i];
            if(track[adjx][adjy]!= 0 && track[adjx][adjy] < shortest){
                shortest = track[adjx][adjy];
                dir = i;
            }
        }
        if(dir == 0){
            loc.push(right);
            ex =ex + dRow[dir];
            ey =ey + dCol[dir];
    //        setDirection(left);
    //        moveTo(x + dRow[dir], y + dCol[dir]);
        }
        else if (dir == 1){
            loc.push(down);
            ex =ex + dRow[dir];
            ey =ey + dCol[dir];
    //        setDirection(up);
    //        moveTo(x + dRow[dir], y + dCol[dir]);
        }
        else if(dir == 2){
            loc.push(left);
            ex =ex + dRow[dir];
            ey =ey + dCol[dir];
    //        setDirection(right);
    //        moveTo(x + dRow[dir], y + dCol[dir]);
        }
        else{
            loc.push(up);
            ex =ex + dRow[dir];
            ey =ey + dCol[dir];
    //        setDirection(down);
    //        moveTo(x + dRow[dir], y + dCol[dir]);
        }
        if(ex == x && ey == y){
            flag = false;
        }
    }
    return loc;
}
