#include "Level.h"
#include <iostream>
#include <fstream>
#include <windows.h>
#include "Enemy.h"
#include "Player.h"
#include "Door.h"
#include "Key.h"
#include "Goal.h"
#include "Money.h"
#include <assert.h>

using namespace std;

constexpr char WAL = (char)219;

Level::Level()
    : m_pLevelData(nullptr)
    , m_width(0)
    , m_height(0)
{
    
}

Level::~Level()
{
    if (m_pLevelData != nullptr)
    {
        delete[] m_pLevelData;
        m_pLevelData = nullptr;
    }
    while (!m_pActors.empty())
    {
        delete m_pActors.back();
        m_pActors.pop_back();
    }
}

bool Level::Load(string levelName, int* playerX, int* playerY)
{
    levelName.insert(0, "../");
    ifstream levelFile;
    levelFile.open(levelName);
    if (!levelFile)
    {
        cout << "Error opening file!" << endl;
        return false;
    }
    else
    {
        constexpr int tempSize = 25;
        char temp[tempSize];

        levelFile.getline(temp, tempSize, '\n');
        m_width = atoi(temp);

        levelFile.getline(temp, tempSize, '\n');
        m_height = atoi(temp);

        m_pLevelData = new char[m_width * m_height];
        levelFile.read(m_pLevelData, (long long)m_width * (long long)m_height);
        
        bool anyWarnings = Convert(playerX, playerY);
        if (anyWarnings)
        {
            cout << "There were warnings while loading the level." << endl;
            system("pause");
        }
        return true;
    }
}

void Level::Draw()
{
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(console, kRegularColour);

    // Draw the level
    for (int y = 0; y < GetHeight(); y++)
    {
        for (int x = 0; x < GetWidth(); x++)
        {
            int indexToPrint = GetIndexFromCoordinates(x, y);
            cout << m_pLevelData[indexToPrint];
        }
        cout << endl;
    }

    COORD actorCursorPositon;

    // Draw the actors
    for (auto actor = m_pActors.begin(); actor != m_pActors.end(); actor++)
    {
        if ((*actor)->IsActive())
        {
            actorCursorPositon.X = (*actor)->GetXPosition();
            actorCursorPositon.Y = (*actor)->GetYPosition();
            SetConsoleCursorPosition(console, actorCursorPositon);
            (*actor)->Draw();
        }
    }
}

bool Level::IsSpace(int x, int y)
{
    return m_pLevelData[GetIndexFromCoordinates(x, y)] == ' ';
}

bool Level::IsWall(int x, int y)
{
    return m_pLevelData[GetIndexFromCoordinates(x, y)] == WAL;
}

bool Level::Convert(int* playerX, int* playerY)
{
    bool anyWarnings = false;

    for (int y = 0; y < m_height; y++)
    {
        for (int x = 0; x < m_width; x++)
        {
            int index = GetIndexFromCoordinates(x, y);

            switch (m_pLevelData[index])
            {
            case '+':
            case '-':
            case '|':
                m_pLevelData[index] = WAL;
                break;
            case 'r':
                m_pLevelData[index] = ' ';
                m_pActors.push_back(new Key(x, y, kRedColour));
                break;
            case 'g':
                m_pLevelData[index] = ' ';
                m_pActors.push_back(new Key(x, y, kGreenColour));
                break;
            case 'R':
                m_pLevelData[index] = ' ';
                m_pActors.push_back(new Key(x, y, kRedColourSolid));
                break;
            case 'G':
                m_pLevelData[index] = ' ';
                m_pActors.push_back(new Key(x, y, kGreenColourSolid));
                break;
            case 'B':
                m_pLevelData[index] = ' ';
                m_pActors.push_back(new Key(x, y, kBlueColourSolid));
                break;
            case 'X':
                m_pLevelData[index] = ' ';
                m_pActors.push_back(new Goal(x, y));
                break;
            case '$':
                m_pLevelData[index] = ' ';
                m_pActors.push_back(new Money(x, y, 1 + rand() % 5));
                break;
            case '@':
                m_pLevelData[index] = ' ';
                if(playerX != nullptr && playerY != nullptr)
                    {
                        *playerX = x;
                        *playerY = y;
                    }
                break;
            case 'e':
                m_pActors.push_back(new Enemy(x, y));
                m_pLevelData[index] = ' ';
                break;
            case 'h':
                m_pActors.push_back(new Enemy(x, y, 3, 0));
                m_pLevelData[index] = ' ';
                break;
            case 'v':
                m_pActors.push_back(new Enemy(x, y, 0, 2));
                m_pLevelData[index] = ' ';
                break;
            case ' ':
                break;
            default:
                cout << "Warning: Unknown character in level file: " << m_pLevelData[index] << endl;
                anyWarnings = true;
                break;
            }    
        }
    }
    
    return anyWarnings;
}

int Level::GetIndexFromCoordinates(int x, int y)
{
    return x + y * m_width;
}

PlaceableActor* Level::UpdateActors(int x, int y)
{
    PlaceableActor* collidedActor = nullptr;

    for (auto actor = m_pActors.begin(); actor != m_pActors.end(); actor++)
    {
        (*actor)-> Update(); // Update all actors

        if (x == (*actor)->GetXPosition() && y == (*actor)->GetYPosition())
        {
            assert(collidedActor == nullptr); // There should only be one actor per space
            collidedActor = *actor;
        }
    }
    return collidedActor;
}
