#include "cmdparser.h"
#include "exceptions.h"
#include <getopt.h>
#include <fstream>

#define STEPS_DEFAULT 100

std::map<std::vector<ActionType>, std::vector<int>> GetMatrixFromFile(std::string &fileName);

ParseResult MyCmdParser::ParseCmdArgs(int argC, char **argV) {
    ParseResult result;
    struct option longOpts[] = {
            {"mode", required_argument, nullptr, 'm'},
            {"steps", required_argument, nullptr, 's'},
            {"matrix", required_argument, nullptr, 't'},
            {0, 0, 0, 0}
    };


    int opt;
    opterr = 0; // To disable printing in stderr on error
    result.mode = (GameMode) 0;
    result.steps = STEPS_DEFAULT;
    while((opt = getopt_long(argC, argV, "-m:s:t:", longOpts, nullptr)) != -1) {
        std::string optArg = optarg;
        switch (opt) {
            case ':':
                throw MissingArgumentException(std::string {(char) optopt});
            case '?':
                throw UnknownOptionException(std::string {(char) optopt});
            case 1:
                result.strategiesNames.emplace_back(optArg);
                break;
            case 'm':
                if (optArg == "fast") result.mode = FAST;
                else if (optArg == "detailed") result.mode = DETAILED;
                else if (optArg == "tournament") result.mode = TOURNAMENT;
                else throw UnknownOptionException("mode=" + optArg);
                break;
            case 's':
                result.steps = std::stoi(optArg);
                break;
            case 't':
                result.matrix = GetMatrixFromFile(optArg);
                break;
            default:
                throw UnknownOptionException("optarg=" + optArg);
        }
    }

    if (result.strategiesNames.size() < 3) {
        throw InvalidInputException("you should add at least 3 strategies");
    }
    if (result.mode == 0) {
        if (result.strategiesNames.size() == 3) {
            result.mode = DETAILED;
        } else {
            result.mode = TOURNAMENT;
        }
    }

    if (result.strategiesNames.size() > 3 && result.mode != TOURNAMENT) {
        throw InvalidInputException("you should add exactly 3 strategies for non-tournament mode");
    }

    return result;
}

std::pair<std::vector<ActionType>, std::vector<int>> GetActionMap(std::string& string);

std::map<std::vector<ActionType>, std::vector<int>> GetMatrixFromFile(std::string &fileName) {
    std::map<std::vector<ActionType>, std::vector<int>> matrix;
    std::ifstream ifstream = std::ifstream(fileName);

    ifstream.exceptions(std::istream::failbit | std::istream::badbit);
    while (!ifstream.eof()) {
        std::string currentLine;
        getline(ifstream, currentLine);
        auto mapPair = GetActionMap(currentLine);
        matrix[mapPair.first] = mapPair.second;
    }

    return matrix;
}

std::pair<std::vector<ActionType>, std::vector<int>> GetActionMap(std::string& string) {
    char actionsAsArray[3][100];
    std::string actions[3];
    int scores[3];

    int c = sscanf(string.c_str(), "%s %s %s => %d %d %d",
                   actionsAsArray[0], actionsAsArray[1], actionsAsArray[2], &scores[0], &scores[1], &scores[2]);

    for (int i = 0; i < 3; i++) {
        actions[i] = actionsAsArray[i];
    }

    if (c != 6) {
        throw MatrixCreatingException("Invalid mapping string: " + string +
                                      "\nYou should use correct line format: [C|D] [C|D] [C|D] => int int int");
    }
//    stream >> actions[0] >> actions[1] >> actions[2] >> delim >> scores[0] >> scores[1] >> scores[2];

    ActionType actionTypes[3];

    for (int i = 0; i < 3; i++) {
        if (actions[i] == "C") actionTypes[i] = COOPERATE;
        else if (actions[i] == "D") actionTypes[i] = DEFECT;
        else throw MatrixCreatingException(std::string("Unknown action type: ") + actions[i] +
                                           "\nYou only allowed to use 'C' and 'D' as action type");
    }

    return {{actionTypes[0], actionTypes[1], actionTypes[2]}, {scores[0], scores[1], scores[2]}};
}
