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
                if((getX() <60 && getDirection() == right)&& (getWorld ()->checkBoulder(getX()+1,getY()))){
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
                     if(getWater() > 0){ //TODO: implement the getWater
                         // if so, set the water to 0
                         changeWater(-1);

                        Squirt *s = new Squirt(getX(), getY(), getWorld(), getDirection());
                        getWorld()->addActor(s);

                     }
           
               
                    break;
                }
            case 'Z':
            case 'z':

                if(getSonar() > 0){ 
                    getWorld()-> checkField(getX(), getY(),6);
                    getWorld()-> playSound(SOUND_SONAR);
                    changeSonar(-1);
                }
                    break;
            case KEY_PRESS_TAB:
                {
//                    check Gold function decGold()
                    if (getNugget() > 0){ //TODO: set num nuggets
                        

                        Gold *gold = new Gold(getX(), getY(), getWorld(), true, false, false);
                        getWorld()->addActor(gold);
                        changeNugget(-1);
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
    else if(getState() == 0){ // if stable
        if(getWorld()-> checkField(getX(), getY(), 0)){

            setState(1);
            setWaitTicks(30);
            
        }
    }
    else if(getState () == 1){ //if waiting 
        if(getTicks() <1){
            setState(2);
        }
        else{
            decTicks();
            
        }
    }
    else if(getState() == 2){

        if(!(getWorld()-> checkField(getX(), getY(), 2))){
       
            moveTo(getX(), getY()-1);
         
        }
        else{
        setState(3);
        }
    }
    else{
        die();
    }
    
}

void Squirt::doSomething(){
   if(!isAlive()){
       return;
   }


    else{
        if(getTravel () >0){
            if(getDirection() == up && getY()<60){
                if(!(getWorld()-> checkField(getX(), getY()+4, 3))){
                    moveTo(getX(), getY()+1);
                    decTravel();
                }
                else{
                    die();
                    return;
                }
            }
            else if(getDirection() == down && getY()>0){
                if(!(getWorld()-> checkField(getX(), getY()-1, 3))){
                    moveTo(getX(), getY()-1);
                    decTravel();
                }
                else{
                    die();
                    return;
                }
            }
            else if(getDirection() == right&& getX()<60){
                if(!(getWorld()-> checkField(getX()+4, getY(), 3))){
                    moveTo(getX()+1, getY());
                    decTravel();
                }
                else{
                    die();
                    return;
                }
               
            }
            else if(getDirection() == left&& getX()>0){
                if(!(getWorld()-> checkField(getX()-1, getY(), 3))){
                    moveTo(getX()-1, getY());
                    decTravel();
                }
                else{
                    die();
                    return;
                }
            }
            
            else{
                decTravel();
            }
           
        }
        else{
            die();
        }
    }
}
        
void Barrel:: doSomething(){
    if(!isAlive()){
        return;
    }
    if((!getVisible()) && getWorld()->checkField(getX(), getY(), 4)){
        setOwnVisible(true);
        return ;
    }
    if((getVisible()) && (getWorld()->checkField(getX(), getY(), 5))){
        getWorld()->getTunnelMan()->changeScore(1000);
        die();
        getWorld()-> playSound(SOUND_FOUND_OIL);
        return;
        
    }
}

void Gold:: doSomething(){
    if(!isAlive()){
        return;
    }
    if((!getVisible()) && getWorld()->checkField(getX(), getY(), 4)){
        setOwnVisible(true);
        return ;
    }
    if((getVisible()) && (getWorld()->checkField(getX(), getY(), 5))){
        if(getState() && getPickupT()){
             getWorld()->getTunnelMan()->changeScore(10);
            die();
            getWorld()-> playSound(SOUND_GOT_GOODIE);
            getWorld()->getTunnelMan()->changeNugget(1);
            return;
        }
    }
     if(getTicks()>0){
         if(!getState() && getWorld()->checkField(getX(), getY(), 6)){
            die();
            getWorld() -> getTunnelMan()->changeScore(25);
            getWorld()-> playSound(SOUND_PROTESTER_FOUND_GOLD);
//            getWorld() -> sendProtestorBack(); //TODO: implement this function
            return;
        }
        else{
            decTicks();
        }

     }
     else if(!getState() &&getTicks() <= 0){
         die();
        return;
     }
    

}

void Sonar:: doSomething(){
    if(!isAlive()){
        return;
    }
    if(getTicks()>0){
        if(getWorld()->checkField(getX(), getY(), 5)){
        die();
        getWorld()-> playSound(SOUND_GOT_GOODIE);
        getWorld()->getTunnelMan()->changeSonar(1);
        getWorld()->getTunnelMan()->changeScore(75);
        return ;
        }
        else{
            decTicks();
        }
      
    }
    else if(getTicks() <= 0){
        die();
    }
    
    
}

void Water:: doSomething(){
    if(!isAlive()){
        return;
    }
    if(getTicks()>0){
        if(getWorld()->checkField(getX(), getY(), 5)){
        die();
        getWorld()-> playSound(SOUND_GOT_GOODIE);
        getWorld()->getTunnelMan()->changeWater(5);
        getWorld()->getTunnelMan()->changeScore(100);
        return ;
        }
        else{
            decTicks();
        }
      
    }
    else if(getTicks() <= 0){
        die();
    }
    
    
}
