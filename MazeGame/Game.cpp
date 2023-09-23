#include "Game.h"
#include <iostream>
#include <windows.h>
#include <conio.h>

using namespace std;

constexpr int kOpenDoorColour = 10;
constexpr int kClosedDoorColour = 12;
constexpr int kRegularColour = 7;

Game::Game()
    : m_isGameOver(false)
{
    
}

Game::~Game()
{
    
}

bool Game::Load()
{
    return m_level.Load("Level1.txt", m_player.GetXPositionPtr(), m_player.GetYPositionPtr());
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

bool Game::IsGameOver()
{
    return m_isGameOver;
}

bool Game::Update()
{
    char input = (char)_getch();

    int newPlayerX = m_player.GetXPosition();
    int newPlayerY = m_player.GetYPosition();
    
    switch (input)
    {
    case 'w':
    case 'W':       
        newPlayerY--;
        break;
    case 's':
    case 'S':
        newPlayerY++;
        break;
    case 'a':
    case 'A':
        newPlayerX--;
        break;
    case 'd':
    case 'D':
        newPlayerX++;
        break;
    default:
        break;
    }
    
    if (m_level.IsSpace(newPlayerX, newPlayerY))
    {
        m_player.SetPosition(newPlayerX, newPlayerY);
    }
    else if (m_level.IsKey(newPlayerX, newPlayerY))
    {
        m_level.PickUpKey(newPlayerX, newPlayerY);
        m_player.PickUpKey();
        m_player.SetPosition(newPlayerX, newPlayerY);
        //PlayKeyPickupSound();
    }
    else if (m_level.IsDoor(newPlayerX, newPlayerY) && m_player.HasKey())
    {
        m_level.OpenDoor(newPlayerX, newPlayerY);
        m_player.UseKey();
        m_player.SetPosition(newPlayerX, newPlayerY);
        //PlayDoorOpenSound();
    }
    else if (m_level.IsDoor(newPlayerX, newPlayerY) && !m_player.HasKey())
    {
        //PlayDoorCloseSound();
    }
    else if (m_level.IsGoal(newPlayerX, newPlayerY))
    {
        m_player.SetPosition(newPlayerX, newPlayerY);
        return true;
    }
    return false;
}

void Game::Draw()
{
    for (int y = 0; y < m_level.GetHeight(); y++)
    {
        for (int x = 0; x < m_level.GetWidth(); x++)
        {
            if(m_player.GetXPosition() == x && m_player.GetYPosition() == y)
            {
                m_player.Draw();
            }
            else
            {
                HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
                if (m_level.IsDoor(x, y))
                {
                    if (m_player.HasKey())
                    {
                        SetConsoleTextAttribute(console, kOpenDoorColour);
                    }
                    else
                    {
                        SetConsoleTextAttribute(console, kClosedDoorColour);
                    }
                }
                else
                {
                    SetConsoleTextAttribute(console, kRegularColour);
                }
                m_level.Draw(x, y);
            }
        }
        cout << endl;
    }
}
