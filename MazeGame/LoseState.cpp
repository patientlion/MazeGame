#include "LoseState.h"
#include <iostream>
#include <conio.h>
#include "StateMachineExampleGame.h"

using namespace std;

LoseState::LoseState(StateMachineExampleGame* pOwner)
    : m_pOwner(pOwner)
{}

bool LoseState::Update(bool processInput)
{

        int input = _getch();
        m_pOwner->LoadScene(StateMachineExampleGame::SceneName::MainMenu);

    return false;
}

void LoseState::Draw()
{
    system("cls");
    cout << endl << endl << endl;
    cout << "Game Over" << endl;
    cout << "Better Luck Next Time!" << endl;
    cout << "Press any key to return to the main menu." << endl;
}