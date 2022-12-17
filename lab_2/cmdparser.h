#ifndef LAB_2_CMDPARSER_H
#define LAB_2_CMDPARSER_H

#include <vector>
#include <string>
#include <map>
#include "strategy.h"

enum GameMode {
    DETAILED = 1,
    FAST,
    TOURNAMENT
};

using ParseResult = struct ParseResult {
private:
public:

    GameMode mode;
    GameMatrix matrix;
    std::vector<std::string> strategiesNames;
    int steps;
};

class MyCmdParser {
public:
    static ParseResult ParseCmdArgs(int argC, char **argV);
};

#endif //LAB_2_CMDPARSER_H
