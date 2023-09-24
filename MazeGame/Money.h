#pragma once
#include "PlaceableActor.h"

class Money : public PlaceableActor
{
public:
    Money (int x, int y, int worth);

    int GetWorth() {return m_worth;}

    virtual void Draw() override;

private:
    int m_worth;    
};
