#include "SettingsState.h"
#include <iostream>
#include <conio.h>

#include "AudioManager.h"
#include "StateMachineExampleGame.h"

using namespace std;

constexpr int kQuitKey = 113;
constexpr char kSound = '1';
constexpr char kMainMenu = '2';

SettingsState::SettingsState(StateMachineExampleGame* pOwner)
    : m_pOwner(pOwner)
{}

bool SettingsState::Update(bool processInput)
{
    bool shouldQuit = false;
    if (processInput)
    {
        int input = _getch();
        if (input == kQuitKey || (char)input == kMainMenu)
        {
            m_pOwner->LoadScene(StateMachineExampleGame::SceneName::MainMenu);
        }
        else if ((char)input == kSound)
        {
            AudioManager::GetInstance()->ToggleSound();
            AudioManager::GetInstance()->PlayMoneySound();
        }
    }
    return false;
}

void SettingsState::Draw()
{
    system("cls");
    cout << endl << endl << endl;
    cout << "Settings" << endl;
    cout << kSound << ".   Toggle Sound" << endl;
    if(AudioManager::GetInstance()->IsSoundOn())
    {
        cout << "Sound is ON" << endl;
    }
    else
    {
        cout << "Sound is OFF" << endl;
    }
    cout << kMainMenu<< ".   Return to Main Menu" << endl;
}