﻿#include "Key.h"
#include <iostream>
#include <windows.h>

using namespace std;

void Key::Draw()
{
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(console, (int)m_colour);

    cout << "+";
    SetConsoleTextAttribute(console, (int)ActorColour::Regular);
}