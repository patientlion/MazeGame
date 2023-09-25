﻿#include "StateMachineExampleGame.h"

#include "Game.h"
#include "GameState.h"
#include "MainMenuState.h"
#include "GameplayState.h"

StateMachineExampleGame::StateMachineExampleGame(Game* pOwner)
    : m_pOwner(pOwner)
    , m_pCurrentState(nullptr)
    , m_pNewState(nullptr)
{
    
}

bool StateMachineExampleGame::Init()
{
    LoadScene(SceneName::MainMenu);
    return true;
}

bool StateMachineExampleGame::UpdateCurrentState(bool processInput)
{
    bool done = false;
    if (m_pNewState != nullptr)
    {
        ChangeState(m_pNewState);
        m_pNewState = nullptr;
    }

    if (m_pCurrentState != nullptr)
    {
        done = m_pCurrentState->Update(processInput);
    }
    return done;
}

void StateMachineExampleGame::DrawCurrentState()
{
    if (m_pCurrentState)
    {
        m_pCurrentState->Draw();
    }
}

void StateMachineExampleGame::ChangeState(GameState* pNewState)
{
    if (m_pCurrentState)
    {
        m_pCurrentState->Exit();
    }
    delete m_pCurrentState;
    m_pCurrentState = pNewState;
    pNewState->Enter();
}

bool StateMachineExampleGame::CleanUp()
{
    if (m_pCurrentState)
    {
        m_pCurrentState->Exit();
        delete m_pCurrentState;
    }
    return true;
}

void StateMachineExampleGame::LoadScene(SceneName scene)
{
    switch (scene)
    {
        case SceneName::MainMenu:
            m_pNewState = new MainMenuState(this);
            break;
        case SceneName::Gameplay:
            m_pNewState = new GameplayState(this);
            break;
        default:
            break;
    }
}