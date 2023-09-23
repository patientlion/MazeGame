#pragma once
#include "Point.h"

constexpr int kGreenColour = 10;
constexpr int kGreenColourSolid = 34;
constexpr int kRedColour = 12;
constexpr int kRedColourSolid = 68;
constexpr int kRegularColour = 7;
constexpr int kBlueColour = 9;
constexpr int kBlueColourSolid = 153;

class PlaceableActor
{
public:
    PlaceableActor(int x, int y, int colour = kRegularColour);
    virtual ~PlaceableActor();

    int GetXPosition();
    int GetYPosition();
    int* GetXPositionPtr();
    int* GetYPositionPtr();
    void SetPosition(int x, int y);

    int GetColour() {return m_colour;}

    void Remove() {m_IsActive = false;}
    bool IsActive() {return m_IsActive;}
    void Place(int x, int y);

    virtual void Draw() = 0;
    virtual void Update()
    {
        
    }
protected:
    Point* m_pPosition;
    bool m_IsActive;
    int m_colour;
};
