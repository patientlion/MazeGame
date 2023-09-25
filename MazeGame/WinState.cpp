#include "WinState.h"
#include <iostream>
#include <conio.h>
#include "StateMachineExampleGame.h"

using namespace std;

WinState::WinState(StateMachineExampleGame* pOwner)
    : m_pOwner(pOwner)
{}

bool WinState::Update(bool processInput)
{
    {

        int input = _getch();
        m_pOwner->LoadScene(StateMachineExampleGame::SceneName::MainMenu);

        return false;
    }
}
    
void WinState::Draw()
{
    system("cls");
    cout << endl << endl << endl;
    cout << "Well Done" << endl;
    cout << "You Beat The Game!" << endl;
    cout << "Press any key to return to the main menu." << endl;
}