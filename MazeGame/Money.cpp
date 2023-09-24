#include "Money.h"
#include <iostream>

using namespace std;

Money::Money(int x, int y, int worth)
    : PlaceableActor(x, y)
    , m_worth(worth)
{

}

void Money::Draw()
{
    cout << "$";
}