
#pragma once

class GameManager;
class UI;

class Action
{
public:
    virtual ~Action() = default;
    virtual void execute(GameManager& game) = 0;
};
