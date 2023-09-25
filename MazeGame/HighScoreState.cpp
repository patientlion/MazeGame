#include "HighScoreState.h"
#include <iostream>
#include <conio.h>

#include "Utility.h"
#include "StateMachineExampleGame.h"

using namespace std;

HighScoreState::HighScoreState(StateMachineExampleGame* pOwner)
    : m_pOwner(pOwner)
{
    m_highScores = Utility::WriteHighScore(0);
}

bool HighScoreState::Update(bool processInput)
{
    bool shouldQuit = false;
    if (processInput)
    {
        int input = _getch();
        m_pOwner->LoadScene(StateMachineExampleGame::SceneName::MainMenu);
    }
    return false;
}

void HighScoreState::Draw()
{
    system("cls");
    cout << endl << endl << endl;
    cout << "High Scores" << endl;
     for (auto score = m_highScores.rbegin(); score != m_highScores.rend(); ++score)
     {
          cout << *score << endl;
     }

    cout << endl << endl;
    cout << "Press any key to return to the main menu." << endl;
}