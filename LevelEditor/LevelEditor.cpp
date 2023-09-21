#include <iostream>

using namespace std;

constexpr char kTopRightBorder = 187;
constexpr char kTopLeftBorder = 201;
constexpr char kBottomRightBorder = 188;
constexpr char kBottomLeftBorder = 200;
constexpr char kHorizontalBorder = 205;
constexpr char kVerticalBorder = 186;

void GetLevelDimensions(int& width, int& height);
void DisplayLevel(char* pLevel, int width, int height);
int GetIndexFromXY(int x, int y, int width);
void DisplayTopBorder(int width);
void DisplayBottomBorder(int width);
void DisplayLeftBorder();
void DisplayRightBorder();

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

    DisplayLevel(pLevel, levelWidth, levelHeight);
    
    delete[] pLevel;
    pLevel = nullptr;
}

void GetLevelDimensions(int& width, int& height)
{
    cout << "Enter level width: ";
    cin >> width;
    cout << "Enter level height: ";
    cin >> height;
}

void DisplayLevel(char* pLevel, int width, int height)
{
    DisplayTopBorder(width);

    for (int y = 0; y < height; y++)
    {
        DisplayLeftBorder();
        for (int x = 0; x < width; x++)
        {
            int index = GetIndexFromXY(x, y, width);
            cout << pLevel[index];
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