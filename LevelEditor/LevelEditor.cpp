#include <iostream>
#include <conio.h>

using namespace std;

constexpr char kCursor = '_';

constexpr char kTopRightBorder = 187;
constexpr char kTopLeftBorder = 201;
constexpr char kBottomRightBorder = 188;
constexpr char kBottomLeftBorder = 200;
constexpr char kHorizontalBorder = 205;
constexpr char kVerticalBorder = 186;

constexpr int kArrowInput = 224;
constexpr int kUpArrow = 72;
constexpr int kDownArrow = 80;
constexpr int kLeftArrow = 75;
constexpr int kRightArrow = 77;

constexpr int kEscape = 27;

void GetLevelDimensions(int& width, int& height);
void DisplayLevel(char* pLevel, int width, int height, int cursorX, int cursorY);
int GetIndexFromXY(int x, int y, int width);
void DisplayTopBorder(int width);
void DisplayBottomBorder(int width);
void DisplayLeftBorder();
void DisplayRightBorder();
bool EditLevel(char* pLevel, int& cursorX, int& cursorY, int width, int height);

int main()
{
    int levelWidth;
    int levelHeight;

    GetLevelDimensions(levelWidth, levelHeight);

    char* pLevel = new char[levelWidth * levelHeight];

    for (int i = 0; i < levelWidth * levelHeight; i++)
    {
        pLevel[i] = ' ';
    }

    int cursorX = 0;
    int cursorY = 0;
    bool doneEditing = false;
    while(!doneEditing)
    {
        system("cls");
        DisplayLevel(pLevel, levelWidth, levelHeight, cursorX, cursorY);
        doneEditing = EditLevel(pLevel, cursorX, cursorY, levelWidth, levelHeight);
    }

    system("cls");
    DisplayLevel(pLevel, levelWidth, levelHeight, -1, -1);
    
    delete[] pLevel;
    pLevel = nullptr;
}

bool EditLevel(char* pLevel, int& cursorX, int& cursorY, int width, int height)
{
    int newCursorX = cursorX;
    int newCursorY = cursorY;

    int intInput = _getch();

    if (intInput == kArrowInput)
    {
        int arrowInput = _getch();
        switch (arrowInput)
        {
            case kLeftArrow:
                newCursorX--;
                break;
            case kRightArrow:
                newCursorX++;
                break;
            case kUpArrow:
                newCursorY--;
                break;
            case kDownArrow:
                newCursorY++;
                break;
        }

        if (newCursorX < 0)
        {
            newCursorX = 0;
        }
        else if (newCursorX == width)
        {
            newCursorX = width - 1;
        }
        if (newCursorY < 0)
        {
            newCursorY = 0;
        }
        else if (newCursorY == width)
        {
            newCursorY = width - 1;
        }

        cursorX = newCursorX;
        cursorY = newCursorY;
    }
    else
    {
        if (intInput == kEscape)
        {
            return true;
        }
        else
        {
            int index = GetIndexFromXY(cursorX, cursorY, width);
            pLevel[index] = (char)intInput;
        }
    }
    return false;
}


void GetLevelDimensions(int& width, int& height)
{
    cout << "Enter level width: ";
    cin >> width;
    cout << "Enter level height: ";
    cin >> height;
}

void DisplayLevel(char* pLevel, int width, int height, int cursorX, int cursorY)
{
    DisplayTopBorder(width);

    for (int y = 0; y < height; y++)
    {
        DisplayLeftBorder();
        for (int x = 0; x < width; x++)
        {
            if(cursorX == x && cursorY == y)
            {
                cout << kCursor;
            }
            else
            {
               int index = GetIndexFromXY(x, y, width);
               cout << pLevel[index];
            }

        }
        DisplayRightBorder();
    }
    
    DisplayBottomBorder(width);
}

void DisplayTopBorder(int width)
{
    cout << kTopLeftBorder;
    for (int i = 0; i < width; i++)
    {
        cout << kHorizontalBorder;
    }
    cout << kTopRightBorder << endl;
}

void DisplayBottomBorder(int width)
{
    cout << kBottomLeftBorder;
    for (int i = 0; i < width; i++)
    {
        cout << kHorizontalBorder;
    }
    cout << kBottomRightBorder << endl;
}

void DisplayLeftBorder()
{
    cout << kVerticalBorder;
}

void DisplayRightBorder()
{
    cout << kVerticalBorder << endl;
}

int GetIndexFromXY(int x, int y, int width)
{
    return x + y * width;
}