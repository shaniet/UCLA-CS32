//
//  Game.h
//  Project1
//
//  Created by Shanie Talor on 6/25/22.
//

#ifndef Game_h
#define Game_h


class Arena;
class Game
{
  public:
        // Constructor/destructor
    Game(int rows, int cols, int nRobots);
    ~Game();

        // Mutators
    void play();

  private:
    Arena* m_arena;
};

#endif /* Game_h */
