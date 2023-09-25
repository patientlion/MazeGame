#pragma once
#include "Player.h"
#include "Level.h"

class Game
{

public:
    Game();
    ~Game();

    
    void Run();

        
private:
    bool Update();
    void Draw();

    
};
