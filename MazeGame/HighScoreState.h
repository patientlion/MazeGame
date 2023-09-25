#pragma once
#include "GameState.h"
#include <set>

using namespace std;

class StateMachineExampleGame;

class HighScoreState : public GameState
{
    StateMachineExampleGame* m_pOwner;
    set<int> m_highScores;
public:
    HighScoreState(StateMachineExampleGame* pOwner);
    ~HighScoreState() = default;

    virtual bool Update(bool processInput = true) override;
    virtual void Draw() override;
};
