#pragma once
#include "Point.h"

class Player
{
private:    
    Point m_position;
    bool m_hasKey;
public:
    Player();
    ~Player();

    int GetXPosition() {return m_position.x;}
    int GetYPosition() {return m_position.y;}

    void SetPosition(int x, int y);

    bool HasKey();
    void PickUpKey();
    void UseKey();

    void Draw();
};
