#include "Player.h"
#include <iostream>
#include "Key.h"

using namespace std;

constexpr int kStartingNumberOfLives = 3;


Player::Player()
    : PlaceableActor(0, 0)
    , m_pCurrentKey(nullptr)
    , m_money(0)
    , m_lives(kStartingNumberOfLives)
{}

bool Player::HasKey()
{
    return m_pCurrentKey != nullptr;
}

bool Player::HasKey(ActorColour colour)
{
    return HasKey() && m_pCurrentKey->GetColour() == colour;
}

void Player::PickUpKey(Key* pKey)
{
    m_pCurrentKey = pKey;
}

void Player::UseKey()
{
    m_pCurrentKey->Remove();
    m_pCurrentKey = nullptr;
}

void Player::DropKey()
{
    if (m_pCurrentKey)
    {
        m_pCurrentKey->Place(m_pPosition->x, m_pPosition->y);
        m_pCurrentKey = nullptr;
    }
}

void Player::Draw()
{
    cout << "@";
}
