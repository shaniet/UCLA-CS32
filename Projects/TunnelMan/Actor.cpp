#include "Actor.h"
#include "StudentWorld.h"

// Students:  Add code to this file (if you wish), Actor.h, StudentWorld.h, and StudentWorld.cpp


void TunnelMan::Annoy() {
    // TODO hit pts dec by 2 and getter for hit points
    dec_hit_pts(2);
    if (setHitPoints == 0) {
        die();
        // TODO: Play I am dead sound

        // TODO: The StudentWorld class should check the
        // TunnelMan’s status during each tickand if he transitions to a dead state, it should
        // return the appropriate value indicating that the player lost a life.
    }
}

void TunnelMan::canMove(int ch, int dest_x, int dest_y) {

    bool same_direction = false;

    if (ch == KEY_PRESS_LEFT) { // Depending on the keystroke
        if (!(getDirection() == left)) {
            setDirection(left); // Set direction if not already the same
        } else
            same_direction = true; // If it is the same mark true
    }
    else if (ch == KEY_PRESS_RIGHT) {
        if (!(getDirection() == right)) {
            setDirection(right);
        }
        else
            same_direction = true;
    }
    else if (ch == KEY_PRESS_UP && getDirection() == up) {
        if (!(getDirection() == up)) {
            setDirection(up);
        }
        else
            same_direction = true;
    }
    else if (ch == KEY_PRESS_DOWN && getDirection() == down) {
        if (!(getDirection() == down)) {
            setDirection(down);
        }
        else
            same_direction = true;
    }
    // TODO: Implement isValidMove
    // If it is the same direction and a valid move then move using GameWorld
    if (same_direction && getWorld()->isValidMove(dest_x, dest_y)) { // Calls StudentWorld
        moveTo(dest_x, dest_y); // Calls GameWorld
    }


}

void TunnelMan::doSomething() {
    if (!isAlive) {
        return;
    } else {
        // TODO: If occupy same as earth remove and play sound

        int ch;
        if (getWorld()->getKey(ch) == true)
        {
            // user hit a key this tick!
            switch (ch)
            {
            case KEY_PRESS_LEFT:
                canMove(ch, getX() - 4, getY());
                break;
            case KEY_PRESS_RIGHT:
                canMove(ch, getX() + 4, getY());
                break;
            case KEY_PRESS_UP:
                canMove(ch, getX(), getY() + 4);
                break;
            case KEY_PRESS_DOWN:
                canMove(ch, getX(), getY() - 4);
                break;
            case KEY_PRESS_ESCAPE:
                // TODO: StudentWorld class should detect that
                // the TunnelMan has diedand address this appropriately(e.g., replay the level
                // from scratch, or end the game if the player has run out of lives).
                die();
                break;
            case KEY_PRESS_SPACE:
                //... TODO: add a Squirt in front of the player...;
                break;
            case KEY_PRESS_TAB:
                //... TODO: add a Gold Nugget object into the oil
                //field at their current x, y locationand reduce
                // their gold count by 1 unit....;
                break;
            case 'z': // TODO: How do we do this?
                // TODO: use sonar;
                break;
            default:
                break;
            }
        }
    }
}
