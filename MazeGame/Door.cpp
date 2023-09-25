#include "Door.h"
#include <iostream>
#include <windows.h>

using namespace std;

Door::Door(int x, int y, ActorColour colour, ActorColour closedColour)
    : PlaceableActor(x, y, colour)
    , m_IsOpen(false)
    , m_closedColour(closedColour)
{

}

void Door::Draw()
{
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    if (m_IsOpen)
    {
        SetConsoleTextAttribute(console, (int)m_colour);
    }
    else
    {
        SetConsoleTextAttribute(console, (int)m_closedColour);
    }
    cout << "|";
    SetConsoleTextAttribute(console, (int)ActorColour::Regular);
}