#pragma once
#include <string>
#include <vector>

using namespace std;

class PlaceableActor;

using namespace std;

class Level
{
    char* m_pLevelData;
    int m_width;
    int m_height;

    vector<PlaceableActor*> m_pActors;
    
public:
    Level();
    ~Level();

    bool Load(string levelName, int* playerX, int* playerY);
    void Draw();
    PlaceableActor* UpdateActors(int x, int y);

    bool IsSpace(int x, int y);
    bool IsWall(int x, int y);

    int GetHeight() {return m_height;}
    int GetWidth() {return m_width;}

    static constexpr char WAL = (char)219;

private:
    bool Convert(int* playerX, int* playerY);
    int GetIndexFromCoordinates(int x, int y);    
};
