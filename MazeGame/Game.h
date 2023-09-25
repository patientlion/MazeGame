#pragma once
#include "GameStateMachine.h"

class Game
{
    GameStateMachine* m_pGameStateMachine;
public:
    Game();
    void Initialise(GameStateMachine* pGameStateMachine);
    void RunGameLoop();
    void Deinitialise();
        
private:
    bool Update(bool processInput = true);
    void Draw();
};
