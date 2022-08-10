#include "Actor.h"
#include "StudentWorld.h"

// Students:  Add code to this file (if you wish), Actor.h, StudentWorld.h, and StudentWorld.cpp


 



void TunnelMan::doSomething(){
    if(!isAlive()){
        return;
    }
    int ch=-1;
    if(getWorld()-> getKey(ch)){
        switch(ch)
        {
            case KEY_PRESS_LEFT:
                if(getX() >0 && getDirection() == left){
                    moveTo(getX() -1, getY());
                    getWorld()->setGridContent(getX(), getY(), 10);
                    getWorld()->setGridContent(getX()-1, getY(), TID_PLAYER);
                    getWorld()->removeEarth(getX(), getY());
                }
                else{
                    setDirection(left);
                }
            case KEY_PRESS_RIGHT:
                if(getX() <60 && getDirection() == right){
                    moveTo(getX() +1, getY());
//                    getWorld()->setGridContent(getX(), getY(), 10);
//                    getWorld()->setGridContent(getX()+1, getY(), TID_PLAYER);
                    getWorld()->removeEarth(getX(), getY());

                }
                else{
                    setDirection(right);
                }
            case KEY_PRESS_UP:
                if(getY() <60 && getDirection() == up){
                    moveTo(getX(), getY()+1);
//                    getWorld()->setGridContent(getX(), getY(), 10);
//                    getWorld()->setGridContent(getX(), getY()+1, TID_PLAYER);
                    getWorld()->removeEarth(getX(), getY());

                }
                else{
                    setDirection(up);
                }
            case KEY_PRESS_DOWN:
                if(getY() >0 && getDirection() == down){
                    moveTo(getX() , getY()-1);
//                    getWorld()->setGridContent(getX(), getY(), 10);
//                    getWorld()->setGridContent(getX(), getY()-1, TID_PLAYER);
                    getWorld()->removeEarth(getX(), getY());

                }
                else{
                    setDirection(down);
                }
            case KEY_PRESS_ESCAPE:
//                die();
                //kill player
                break;
            case KEY_PRESS_SPACE:
                {
//                    getWorld()->shootWater(getX(), getY());
                    break;
                }
            case 'Z':
            case 'z':
                if (sonar <= 0)
                    break;
                sonar--;
        }
    }
}
