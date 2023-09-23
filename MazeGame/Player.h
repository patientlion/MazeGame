#pragma once
#include "Point.h"

class Player
{
    Point m_position;
    bool m_hasKey;
public:
    Player();
    ~Player();

    int GetXPosition() {return m_position.x;}
    int GetYPosition() {return m_position.y;}

    int* GetXPositionPtr() {return &m_position.x;}
    int* GetYPositionPtr() {return &m_position.y;}
    
    void SetPosition(int x, int y);

    bool HasKey();
    void PickUpKey();
    void UseKey();

    void Draw();
};
