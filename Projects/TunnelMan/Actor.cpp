#include "Actor.h"
#include "StudentWorld.h"

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
    int ch=-1;
    if(getWorld()-> getKey(ch)){
        switch(ch)
        {
            case KEY_PRESS_RIGHT:
          
                // check if the tunnelman is within the bounds of the screen
                if(getX() <60 && getDirection() == right){ 
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
                if(getX() >0 && getDirection() == left){
                    // if so move the tunnelman left
                    moveTo(getX() -1, getY());
                    //remove earth from the screen
                    getWorld()->removeEarth(getX(), getY());
                }
                // set the direction to left
                    setDirection(left);
                break;
            case KEY_PRESS_UP:
          
                if(getY() <60 && getDirection() == up){
                    // if so move the tunnelman up
                    moveTo(getX(), getY()+1);
                    //remove earth from the screen
                    getWorld()->removeEarth(getX(), getY());
                }
                // set the direction to up
                    setDirection(up);
                break;
            case KEY_PRESS_DOWN:
           
                if(getY() >0 && getDirection() == down){
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
//                    getWorld()->shootWater(getX(), getY());
                    break;
                }
            case 'Z':
            case 'z':
                // if (sonar <= 0)
                    break;
                // sonar--;
        }
    }
}
