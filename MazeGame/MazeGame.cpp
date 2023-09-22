#include <iostream>
#include <conio.h>

using namespace std;
constexpr char kPlayerSymbol = '@';
constexpr char WAL = 219;
constexpr char KEY = 232;
constexpr char DOR = 179;
constexpr char GOL = 36;

int GetIndexFromCoordinates(int x, int y, int width);
void DrawLevel(char level[], int width, int height, int playerX, int playerY);
bool UpdatePlayerPosition(char level[], int& playerX, int& playerY, int width, bool& playerHasKey);

int main()
{
    constexpr int kWidth = 25;
    constexpr int kHeight = 15;
    
    char levelArray[]
    {
        WAL, WAL, WAL, WAL, WAL, WAL, WAL, WAL, WAL, WAL, WAL, WAL, WAL, WAL, WAL, WAL, WAL, WAL, WAL, WAL, WAL, WAL, WAL, WAL, WAL,
        WAL, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', WAL, ' ', KEY, WAL,
        WAL, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', WAL, ' ', ' ', WAL,
        WAL, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', WAL, ' ', ' ', WAL,
        WAL, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', WAL, WAL, ' ', WAL,
        WAL, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', WAL,
        WAL, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', WAL,
        WAL, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', WAL,
        WAL, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', WAL,
        WAL, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', WAL,
        WAL, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', WAL,
        WAL, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', WAL, WAL, WAL, WAL, WAL, WAL, WAL, WAL, WAL, WAL, WAL,
        WAL, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', WAL, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', WAL,
        WAL, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', DOR, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', GOL, WAL,
        WAL, WAL, WAL, WAL, WAL, WAL, WAL, WAL, WAL, WAL, WAL, WAL, WAL, WAL, WAL, WAL, WAL, WAL, WAL, WAL, WAL, WAL, WAL, WAL, WAL
    };

    int playerX = 1;
    int playerY = 1;
    bool playerHasKey = false;
    bool gameOver = false;

    while (!gameOver)
    {
        system("cls");
        DrawLevel(levelArray, kWidth, kHeight, playerX, playerY);
        gameOver = UpdatePlayerPosition(levelArray, playerX, playerY, kWidth, playerHasKey);
    }
    system("cls");
    DrawLevel(levelArray, kWidth, kHeight, playerX, playerY);
    cout << "You win!" << endl;
}

int GetIndexFromCoordinates(int x, int y, int width)
{
    return x + y * width;
}

void DrawLevel(char level[], int width, int height, int playerX, int playerY)
{
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            if(playerX == x && playerY == y)
            {
                cout << kPlayerSymbol;
            }
            else
            {
                cout << level[GetIndexFromCoordinates(x, y, width)];
            }
        }
        cout << endl;
    }
}

bool UpdatePlayerPosition(char level[], int& playerX, int& playerY, int width, bool& playerHasKey)
{
    char input = _getch();

    int newPlayerX = playerX;
    int newPlayerY = playerY;
    
    switch (input)
    {
        case 'w':
        case 'W':       
            newPlayerY--;
            break;
        case 's':
        case 'S':
            newPlayerY++;
            break;
        case 'a':
        case 'A':
            newPlayerX--;
            break;
        case 'd':
        case 'D':
            newPlayerX++;
            break;
        default:
            break;
    }

    int index = GetIndexFromCoordinates(newPlayerX, newPlayerY, width);
    if (level[index] == ' ')
    {
        playerX = newPlayerX;
        playerY = newPlayerY;
    }
    else if (level[index] == KEY)
    {
        playerHasKey = true;
        level[index] = ' ';
        playerX = newPlayerX;
        playerY = newPlayerY;
    }
    else if (level[index] == DOR && playerHasKey)
    {
        level[index] = ' ';
        playerHasKey = false;
        playerX = newPlayerX;
        playerY = newPlayerY;
    }
    else if (level[index] == GOL)
    {
        level[index] = ' ';
        playerX = newPlayerX;
        playerY = newPlayerY;
        return true;
    }
    return false;
}