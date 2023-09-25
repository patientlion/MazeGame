#include <iostream>
#include "Game.h"
#include "AudioManager.h"

using namespace std;

int main()
{
    Game myGame;

    if (myGame.Load())
    {
        while (!myGame.IsGameOver())
        {
            myGame.Run();
        }

        if (myGame.DidUserQuit())
        {
            cout << "Thanks for playing!" << endl;
        }
        else if (myGame.GetPlayerLives() < 0)
        {
            cout << "You Lose!" << endl;
            AudioManager::GetInstance()->PlayLoseSound();
        }
        else
        {
            cout << "You Win!" << endl;
            AudioManager::GetInstance()->PlayWinSound();
        }
    }
    else
    {
        cout << "Failed to load game. Terminating now!" << endl;
    }

    AudioManager::DestroyInstance();

    return 0;
}