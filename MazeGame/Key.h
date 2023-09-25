#pragma once
#include "PlaceableActor.h"

class Key : public PlaceableActor
{
public:
    Key(int x, int y, ActorColour colour)
        : PlaceableActor(x, y, colour)
    {}

    virtual ActorType GetType() override {return ActorType::Key;}
    virtual void Draw() override;
};
