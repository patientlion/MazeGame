#pragma once
#include "PlaceableActor.h"

class Money : public PlaceableActor
{
public:
    Money (int x, int y, int worth);

    int GetWorth() {return m_worth;}

    virtual ActorType GetType() override {return ActorType::Money;}
    virtual void Draw() override;

private:
    int m_worth;    
};
