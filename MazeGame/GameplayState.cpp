#include "GameplayState.h"
#include <iostream>
#include <conio.h>
#include <assert.h>

#include "Enemy.h"
#include "Money.h"
#include "Goal.h"
#include "Key.h"
#include "Door.h"
#include "AudioManager.h"
#include "Utility.h"
#include "StateMachineExampleGame.h"

constexpr int kArrowInput = 224;
constexpr int kUpArrow = 72;
constexpr int kDownArrow = 80;
constexpr int kLeftArrow = 75;
constexpr int kRightArrow = 77;
constexpr int kQuitKey = 113;

GameplayState::GameplayState(StateMachineExampleGame* pOwner)
    : m_pOwner(pOwner)
    , m_beatLevel(false)
    , m_skipFrameCount(0)
    , m_currentLevel(0)
    , m_pLevel(nullptr)
{
    m_LevelNames.push_back("Level1.txt");
    m_LevelNames.push_back("Level2.txt");
    m_LevelNames.push_back("Level2.txt");
}

GameplayState::~GameplayState()
{
    delete m_pLevel;
    m_pLevel = nullptr;
}

bool GameplayState::Load()
{
    if (m_pLevel)
    {
        delete m_pLevel;
        m_pLevel = nullptr;
    }
    m_pLevel = new Level();
    
    return m_pLevel->Load(m_LevelNames.at(m_currentLevel), m_player.GetXPositionPtr(), m_player.GetYPositionPtr());
}

void GameplayState::Enter()
{
    Load();
}

bool GameplayState::Update(bool processInput)
{
    if (processInput && !m_beatLevel)
    {
        int input = _getch();
        int arrowInput = 0;
        int newPlayerX = m_player.GetXPosition();
        int newPlayerY = m_player.GetYPosition();

        // One of the arrow keys was pressed
        if (input == kArrowInput)
        {
            arrowInput = _getch();
        }

        if ((input == kArrowInput && arrowInput == kLeftArrow)  || (char)input == 'A' || (char)input == 'a')
        {
            newPlayerX--;
        }
        else if ((input == kArrowInput && arrowInput == kRightArrow) || (char)input == 'D' || (char)input == 'd')
        {
            newPlayerX++;
        }
        else if ((input == kArrowInput && arrowInput == kUpArrow) || (char)input == 'W' || (char)input == 'w')
        {
            newPlayerY--;
        }
        else if ((input == kArrowInput && arrowInput == kDownArrow) || (char)input == 'S' || (char)input == 's')
        {
            newPlayerY++;
        }
        else if (input == kQuitKey)
        {
            m_pOwner->LoadScene(StateMachineExampleGame::SceneName::MainMenu);
        }
        else if ((char)input == 'Z' || (char)input == 'z')
        {
            m_player.DropKey();
        }

        // If position never changed
        if (newPlayerX == m_player.GetXPosition() && newPlayerY == m_player.GetYPosition())
        {
            
        }
        else
        {
            HandleCollision(newPlayerX, newPlayerY);
        }
    }

    if (m_beatLevel)
    {
        ++m_skipFrameCount;
        if (m_skipFrameCount > kFramesToSkip)
        {
            m_beatLevel = false;
            m_skipFrameCount = 0;
            ++m_currentLevel;
            if (m_currentLevel == m_LevelNames.size())
            {
                Utility::WriteHighScore(m_player.GetMoney());
                AudioManager::GetInstance()->PlayWinSound();
                m_pOwner->LoadScene(StateMachineExampleGame::SceneName::Win);
            }
            else
            {
                Load();
            }
        }
    }
    
    return false;
}

void GameplayState::HandleCollision(int newPlayerX, int newPlayerY)
{
    bool isGameDone = false;
    PlaceableActor* collidedActor = m_pLevel->UpdateActors(newPlayerX, newPlayerY);
    if (collidedActor != nullptr && collidedActor->IsActive())
    {
        
        {
            switch (collidedActor->GetType())
            {
            case ActorType::Enemy:
                {
                    Enemy* collidedEnemy = dynamic_cast<Enemy*>(collidedActor);
                    assert(collidedEnemy);
                    AudioManager::GetInstance()->PlayLoseLivesSound();
                    collidedEnemy->Remove();
                    m_player.SetPosition(newPlayerX, newPlayerY);
                    m_player.DecreaseLives();
                    if (m_player.GetLives() <= 0)
                    {
                        AudioManager::GetInstance()->PlayWinSound();
                        m_pOwner->LoadScene(StateMachineExampleGame::SceneName::Lose);
                    }
                    break;
                }
            case ActorType::Money:
                {
                    Money* collidedMoney = dynamic_cast<Money*>(collidedActor);
                    assert (collidedMoney);
                    AudioManager::GetInstance()->PlayMoneySound();
                    collidedMoney->Remove();
                    m_player.AddMoney(collidedMoney->GetWorth());
                    m_player.SetPosition(newPlayerX, newPlayerY);
                    break;
                }
                
            case ActorType::Key:
                {
                    Key* collidedKey = dynamic_cast<Key*>(collidedActor);
                    assert (collidedKey);                
                    if (!m_player.HasKey())
                    {
                        m_player.PickUpKey(collidedKey);
                        collidedKey->Remove();
                        m_player.SetPosition(newPlayerX, newPlayerY);
                        AudioManager::GetInstance()->PlayKeyPickupSound();
                    }
                    break;
                }
            case ActorType::Door:
                {
                    Door* collidedDoor = dynamic_cast<Door*>(collidedActor);
                    assert (collidedDoor);
                    if (!collidedDoor->IsOpen())
                    {
                        if(m_player.HasKey(collidedDoor->GetColour()))
                        {
                            collidedDoor->Open();
                            collidedDoor->Remove();
                            m_player.UseKey();
                            m_player.SetPosition(newPlayerX, newPlayerY);
                            AudioManager::GetInstance()->PlayDoorOpenSound();
                        }
                        else
                        {
                            AudioManager::GetInstance()->PlayDoorCloseSound();
                        }
                    }
                    else
                    {
                        m_player.SetPosition(newPlayerX, newPlayerY);
                    }
                    break;
                }
            case ActorType::Goal:
                {
                    Goal* collidedGoal = dynamic_cast<Goal*>(collidedActor);
                    assert (collidedGoal);
                    collidedGoal->Remove();
                    m_player.SetPosition(newPlayerX, newPlayerY);
                    m_beatLevel = true;
                    break;
                }
            default:
                break;
            }
        }
    }
    else if (m_pLevel->IsSpace(newPlayerX, newPlayerY)) // no collision
    {
        m_player.SetPosition(newPlayerX, newPlayerY);
    }
    else if (m_pLevel->IsWall(newPlayerX, newPlayerY))
    {
        // wall collision, do nothing
    }
}

void GameplayState::Draw()
{
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    system("cls");

    m_pLevel->Draw();

    // set cursor position for player
    COORD actorCursorPositon;
    actorCursorPositon.X = m_player.GetXPosition();
    actorCursorPositon.Y = m_player.GetYPosition();
    SetConsoleCursorPosition(console, actorCursorPositon);
    m_player.Draw();

    // set cursor to end of level
    COORD currentCursorPositon;
    currentCursorPositon.X = 0;
    currentCursorPositon.Y = m_pLevel->GetHeight();
    SetConsoleCursorPosition(console, currentCursorPositon);

    DrawHUD(console);
}

void GameplayState::DrawHUD(const HANDLE& console)
{
    cout << endl;
    //Top border
    for (int i = 0; i < m_pLevel->GetWidth(); i++)
    {
        cout << Level::WAL;
    }
    cout << endl;

    // Left border
    cout << Level::WAL;
    
    cout << " wasd-move" << Level::WAL << "z-drop key" << Level::WAL << "q-quit";
    cout << " $: " << m_player.GetMoney() << Level::WAL;
    cout << " lives: " << m_player.GetLives() << Level::WAL;
    cout << " key: ";
    if (m_player.HasKey())
    {
        m_player.GetKey()->Draw();
    }
    else
    {
        cout << " ";
    }

    // Right border
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(console, &csbi);

    COORD pos;
    pos.X = m_pLevel->GetWidth() - 1;
    pos.Y = csbi.dwCursorPosition.Y;
    SetConsoleCursorPosition(console,pos);

    cout << Level::WAL;
    cout << endl;

    // bottom border
    for (int i = 0; i < m_pLevel->GetWidth(); i++)
    {
        cout << Level::WAL;
    }
    cout << endl;
}