#ifndef LAB_2_GAMEMODE_H
#define LAB_2_GAMEMODE_H

#include "simulator.h"

class GameModeBase {
protected:
    using Pairs = std::vector<std::pair<std::string, int>>;

public:
    virtual void Play() = 0;

    virtual ~GameModeBase() = default;

    virtual Pairs GetTotalScore() = 0;

    virtual void PrintTotalScore() = 0;
};

#endif //LAB_2_GAMEMODE_H
