#include <iostream>
#include "Game.h"
#include "AudioManager.h"
#include "StateMachineExampleGame.h"

using namespace std;

int main()
{
    Game myGame;

    StateMachineExampleGame gameStateMachine(&myGame);

    myGame.Initialise(&gameStateMachine);
    myGame.RunGameLoop();
    myGame.Deinitialise();

    AudioManager::DestroyInstance();

    return 0;
}