#pragma once
#include "PlaceableActor.h"

class Key;

class Player : public PlaceableActor
{
public:
    Player();

    bool HasKey();
    bool HasKey(int colour);
    void PickUpKey(Key* Key);
    void UseKey();
    void DropKey();

    void AddMoney(int money) {m_money += money;}
    int GetMoney() {return m_money;}

    int GetLives() {return m_lives;}
    void DecreaseLives() {m_lives--;}

    virtual void Draw() override;
    
private:
    Key* m_pCurrentKey;
    int m_money;
    int m_lives;
};
