#include "Game.h"


using namespace std;



Game::Game()
    : m_isGameOver(false)
{
    
}

Game::~Game()
{
    
}



void Game::Run()
{
    Draw();

    m_isGameOver = Update();

    if (m_isGameOver)
    {
        Draw();
    }
}








