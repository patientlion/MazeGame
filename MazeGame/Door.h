#pragma once
#include "PlaceableActor.h"

class Door : public PlaceableActor
{
public:
    Door (int x, int y, int colour, int closedColour);
    virtual void Draw() override;

    bool IsOpen() {return m_IsOpen;}
    void Open() {m_IsOpen = true;}
private:
    bool m_IsOpen;
    int m_closedColour;        
};
