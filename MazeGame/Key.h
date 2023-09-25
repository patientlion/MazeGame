#pragma once
#include "PlaceableActor.h"

class Key : public PlaceableActor
{
public:
    Key(int x, int y, ActorColour colour)
        : PlaceableActor(x, y, colour)
    {}
    virtual void Draw() override;
};
