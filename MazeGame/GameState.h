#pragma once

class GameState
{
public:
    virtual ~GameState() = default;

    virtual void Enter() {}
    virtual bool Update(bool processInput = true) {return false;}
    virtual void Draw() {}
    virtual void Exit() {}
};
