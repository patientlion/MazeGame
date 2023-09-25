#include "MainMenuState.h"
#include <iostream>
#include <conio.h>
#include "StateMachineExampleGame.h"

using namespace std;

constexpr int kQuitKey = 113;
constexpr char kPlay = '1';
constexpr char kHighScore = '2';
constexpr char kSettings = '3';
constexpr char kQuit = '4';

MainMenuState::MainMenuState(StateMachineExampleGame* pOwner)
    : m_pOwner(pOwner)
{}

bool MainMenuState::Update(bool processInput)
{
    bool shouldQuit = false;
    if (processInput)
    {
        int input = _getch();
        if (input == kQuitKey || (char)input == kQuit)
        {
            shouldQuit = true;
        }
        else if ((char)input == kPlay)
        {
            m_pOwner->LoadScene(StateMachineExampleGame::SceneName::Gameplay);
        }
        else if ((char)input == kHighScore)
        {
            m_pOwner->LoadScene(StateMachineExampleGame::SceneName::Highscore);
        }
        else if ((char)input == kSettings)
        {
            m_pOwner->LoadScene(StateMachineExampleGame::SceneName::Settings);
        }
    }
    return shouldQuit;
}

void MainMenuState::Draw()
{
    system("cls");
    cout << endl << endl << endl;
    cout << "Main Menu" << endl;
    cout << kPlay << ".   Play" << endl;
    cout << kHighScore << ".   HighScores" << endl;
    cout << kSettings << ".   Settings" << endl;
    cout << kQuit << ".   Quit" << endl;
}