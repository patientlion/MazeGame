#include "Game.h"




Game::Game()
    : m_pGameStateMachine(nullptr)
{
    
}

void Game::Initialise(GameStateMachine* pGameStateMachine)
{
    if (pGameStateMachine)
    {
        pGameStateMachine->Init();
        m_pGameStateMachine = pGameStateMachine;
    }
}

void Game::RunGameLoop()
{
    bool isGameOver = false;
    while (!isGameOver)
    {
        Update(false);
        Draw();
        isGameOver = Update();
    }
    Draw();
}

void Game::Deinitialise()
{
    if (m_pGameStateMachine)
    {
        m_pGameStateMachine->CleanUp();
            }
}

bool Game::Update(bool processInput)
{
    return m_pGameStateMachine->UpdateCurrentState(processInput);
}

void Game::Draw()
{
    m_pGameStateMachine->DrawCurrentState();
}








