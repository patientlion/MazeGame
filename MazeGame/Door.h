#pragma once
#include "PlaceableActor.h"

class Door : public PlaceableActor
{
public:
    Door (int x, int y, ActorColour colour, ActorColour closedColour);
    virtual void Draw() override;

    bool IsOpen() {return m_IsOpen;}
    void Open() {m_IsOpen = true;}
private:
    bool m_IsOpen;
    ActorColour m_closedColour;        
};
