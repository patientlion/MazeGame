#include "PlaceableActor.h"

PlaceableActor::PlaceableActor(int x, int y, int colour)
    : m_pPosition(new Point(x, y))
    , m_IsActive(true)
    , m_colour(colour)
{
}

PlaceableActor::~PlaceableActor()
{
    delete m_pPosition;
}

int PlaceableActor::GetXPosition()
{
    return m_pPosition->x;
}

int PlaceableActor::GetYPosition()
{
    return m_pPosition->y;
}

int* PlaceableActor::GetXPositionPtr()
{
    return &(m_pPosition->x);
}

int* PlaceableActor::GetYPositionPtr()
{
    return &(m_pPosition->y);
}

void PlaceableActor::SetPosition(int x, int y)
{
    m_pPosition->x = x;
    m_pPosition->y = y;
}

void PlaceableActor::Place(int x, int y)
{
    m_pPosition->x = x;
    m_pPosition->y = y;
    m_IsActive = true;
}

