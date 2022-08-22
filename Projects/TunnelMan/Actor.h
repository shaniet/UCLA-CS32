#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"
#include "GameConstants.h"
#include <algorithm>
#include <queue>
#include <utility>


// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp

// Base class for Game's objects

class StudentWorld;

class Actor: public GraphObject
{
private:
    bool m_life;
    StudentWorld* m_world;
public:
    //Base class constructor
    Actor(int imageID, int startX, int startY, StudentWorld* world, Direction dir = right, double size = 1.0, unsigned int depth = 0): GraphObject(imageID,startX,startY,dir,size,depth),m_life(true),m_world(world){}
    //base class destructor
    virtual ~Actor() {}
    //pure virtual function to be overridden by derived classes
    void virtual doSomething() = 0;
    // pure virtual function to be overridden by derived classes
    void virtual Annoy(int amt) = 0;
    void virtual setOwnVisible(bool visible)=0;

    // check if the actor is alive
    bool isAlive()const { return m_life; }
    // set the actor's life to false
    void die() { m_life = false; }
    // get the student world pointer
    StudentWorld* getWorld() { return m_world; }
};

    class TunnelMan: public Actor{
    private:
        int hitPoints, water, sonar, nugget, score, barrels;;
        

    public:
        
        TunnelMan(StudentWorld* world):Actor(TID_PLAYER,30,60,world, right, 1.0, 0),hitPoints(10),water(5),sonar(1),nugget(0), score(0){setVisible(true);}//TunnelMan constructor
        
        virtual void doSomething();//TunnelMan doSomething function
        virtual void Annoy(int amt);
        virtual void setOwnVisible(bool visible){}
        // public helper functions
        
        void changeHitPoints(int change){
            hitPoints += change;
            if (hitPoints <= 0)
                die();
        }
        void changeWater(int change){
            water += change;
        }
        void changeSonar(int change){
            sonar += change;
        }
        void changeNugget(int change){
            nugget+= change;
        }
       
        void changeScore(int change){
            score += change;
        }
        void changeBarrels(int change){
            barrels += change;
        }
        void setBarrels(int numbarrels){
            barrels = numbarrels;
        }
        //public getter functions: get hit points, get water, get sonar, get nugget

        int getHitPoints() const{
            return hitPoints;
        }
        int getWater() const{
            return water;
        }
        int getSonar() const{
            return sonar;
        }
        int getNugget() const{
            return nugget;
        }
        int getScore() const{
            return score;
        }
        int getBarrels() const{
            return barrels;
        }
        virtual ~TunnelMan(){}    //TunnelMan destructor
    };

    class Earth: public Actor{
    public:

        Earth(int startX, int startY, StudentWorld* world): Actor(TID_EARTH,startX,startY,world,right,.25,3){setVisible(true);}     //Earth constructor
        
        virtual void doSomething(){}  // earth's do something function(doesnt do anything)
        virtual void Annoy(int amt){} //Earth annoy function (doesnt annoy)
        virtual void setOwnVisible(bool visible){}
        virtual ~Earth() {}    //Earth destructor
    };

    class Boulder: public Actor{
    private:
        int m_state; //(0 = stable, 1 = waiting, 2 = falling)
        int m_waitTicks; //number of ticks to wait before falling
    public:
       
        //Boulder constructor
        Boulder(int startX, int startY, StudentWorld* world): Actor(TID_BOULDER,startX,startY,world,down,1.0,1){setVisible(true); setState(0);}
        //Boulder doSomething function
        virtual void doSomething();
        virtual void Annoy(int amt){}; //Boulder annoy function (doesnt annoy)
        //Boulder destructor
        void setState(int state){
            m_state = state;
        }
        void setWaitTicks(int ticks){
            m_waitTicks = ticks;
        }
        void decTicks(){
            m_waitTicks--;
        }
        int getState() const{
            return m_state;
        }
        int getTicks(){
            return m_waitTicks;
        }
     
        virtual void setOwnVisible(bool visible){}

        virtual ~Boulder() {}

    };

    class Squirt: public Actor{
    private:
        int m_travel = 4;
    public:
        Squirt(int startX, int startY, StudentWorld* world, Direction dir): Actor(TID_WATER_SPURT,startX,startY,world,dir,1.0,0){setVisible(true); }//Squirt constructor
        virtual void doSomething(); //Squirt doSomething function
        virtual void Annoy(int amt) {} //Squirt annoy function (doesnt annoy)
        int getTravel() {
            return m_travel;
        }
        void decTravel(){
            m_travel--;
        }
        virtual void setOwnVisible(bool visible){}
        virtual ~Squirt() {}

    };

    class Goodies: public Actor{ // oil, gold, sonar, water
    private:
            bool m_visible;
            int m_ticks;
    public:
        Goodies(int imageID, int startX, int startY, StudentWorld* world): Actor(imageID,startX,startY,world,right,1.0,2){}
        virtual void doSomething(){}
        virtual void Annoy(int amt){}
        virtual void setOwnVisible(bool visible){
                setVisible(visible);
                m_visible = visible;
            }
        bool getVisible(){
        return m_visible;
        }
        void setTicks(int ticks){
            m_ticks = ticks;
        }
        int getTicks(){
                return m_ticks;
            }
        void decTicks(){
            m_ticks--;
        }
        virtual ~Goodies() {}
    };

        class Barrel: public Goodies{
        
            
        public:
            Barrel(int startX, int startY, StudentWorld* world): Goodies(TID_BARREL,startX,startY,world){setOwnVisible(false);}
            virtual void doSomething();
            virtual void Annoy(int amt){} //Oil annoy function (doesnt annoy)
            virtual ~Barrel() {}
        };

        class Gold: public Goodies{
        private:
           
            bool m_pickupT;
            bool m_state;
        public:
            // pickupT == true -> can be picked up by tunnelMan only, else: protesters
            // state = true -> permanent, else: temporary
            Gold(int startX, int startY, StudentWorld* world, bool visible, bool pickupT, bool state): Goodies(TID_GOLD,startX,startY,world), m_pickupT(pickupT), m_state(state){setOwnVisible(visible); if(!m_state){setTicks(100);}}//changed
            virtual void doSomething();
            virtual ~Gold() {}
            bool getPickupT(){
                return m_pickupT;
            }
            bool getState(){
                return m_state;
            }
        };

        class Sonar: public Goodies{
        
        public:
            Sonar(int startX, int startY, StudentWorld* world, int ticks): Goodies(TID_SONAR,startX,startY,world){setOwnVisible(true); setTicks(ticks);}
            virtual void doSomething();
            virtual ~Sonar() {}
        };

        class Water: public Goodies{
        public:
            Water(int startX, int startY, StudentWorld* world, int ticks): Goodies(TID_WATER_POOL,startX,startY,world){setOwnVisible(true); setTicks(ticks);}
            virtual void doSomething();
//            virtual void Annoy(int amt){} //Water annoy function (doesnt annoy)
            virtual ~Water() {}
        };

    class Protester: public Actor{
    

        public:
        Protester(int imageID, int startX, int startY, StudentWorld* world, int numSquaresToMove): Actor(imageID,startX,startY,world,left,1.0,0){setOriginalTicks(numSquaresToMove);}
        virtual void doSomething(); // Do something function for Protester
        virtual void Annoy(int amt);// Annoy function for Protester
        bool checkProtestor(int x, int y, Direction dir, int state);
        Direction getDir(int x, int y, int XorY);
        Direction randDir();
        void setState(int state){ // 0: rest state 1: active state state 2: dead
            m_state = state;
        }
        int getState(){
            return m_state;
        }
        void setHitPoints(int hp){
            hitPoints = hp;
        }
        void changeHitPoints(int amt){
            hitPoints += amt;
        }
        int getHitPoints(){
            return hitPoints;
        }
        void setNumSquaresToMoveInCurrentDirection(int num){
            numSquaresToMoveInCurrentDirection = num;
        }
        int getNumSquaresToMoveInCurrentDirection(){
            return numSquaresToMoveInCurrentDirection;
        }
        void decNumSquaresToMoveInCurrentDirection(){
            numSquaresToMoveInCurrentDirection--;
        }
        void setTicksProt(int ticks){
            ticksToWaitBetweenMoves = ticks;
        }
        int getTicksProt(){
            return ticksToWaitBetweenMoves;
        }
        void decTicksProt(){
            ticksToWaitBetweenMoves--;
        }
        void setCountPerp(int count){
            countPerp = count;
        }
        void decCountPerp(){
            countPerp--;
        }
        int getCountPerp(){
            return countPerp;
        }
        void setOriginalTicks(int num){
            originalTicks = num;
        }
        int getOriginalTicks(){
            return originalTicks;
        }
//        int getTrack(int x, int y){
//            return track[x][y];
//        }
        void BFS(int track[][64],int x, int y);
        bool isValid(int track[][64],int x, int y);
        std::stack<Direction> Moveit(int track[][64], int x, int y);
//        void Exit(int track[][64], int x, int y,int ex, int ey);
        virtual void setOwnVisible(bool visible){}

        virtual ~Protester(){}
        private:
            int ticksToWaitBetweenMoves;
    
            int hitPoints;
            int countPerp;
            int numSquaresToMoveInCurrentDirection;
            int m_state;
       
            int originalTicks;

    };

        class RegularProtester: public Protester{
        public:
            RegularProtester(int startX, int startY, StudentWorld* world, int numSquaresToMove, int ticks): Protester(TID_PROTESTER,startX,startY,world, ticks){setNumSquaresToMoveInCurrentDirection(numSquaresToMove); setState(0); setHitPoints(5); setTicksProt(ticks); setVisible(true);}
           
            virtual ~RegularProtester() {}
        private:
          
        };

        class HardcoreProtester: public Protester{
        public:
            HardcoreProtester(int startX, int startY, StudentWorld* world, int numSquaresToMove, int ticks): Protester(TID_HARD_CORE_PROTESTER,startX,startY,world, ticks){setNumSquaresToMoveInCurrentDirection(numSquaresToMove); setState(0); setHitPoints(20); setTicksProt(ticks); setVisible(true);}
            virtual ~HardcoreProtester() {}

        };




#endif // ACTOR_H_
