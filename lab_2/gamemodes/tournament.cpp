#include <iostream>
#include <algorithm>
#include "tournament.h"
#include "competitionnodetails.h"

using StrategiesNamesCombination = std::vector<std::string>;

std::vector<StrategiesNamesCombination> GetStrategiesNamesCombinations(std::vector<std::string> &strategiesNames);

void Tournament::Play() {
    auto strategiesNamesCombinations = GetStrategiesNamesCombinations(strategiesNames);

    for (auto &combination : strategiesNamesCombinations) {
        auto newGame = CompetitionNoDetailsMode(factory, combination, steps, gameMatrix);
        newGame.Play();
        auto namesWithScores = newGame.GetTotalScore();

        for (auto &nameWithScore : namesWithScores) {
            strategiesScores[nameWithScore.first] += nameWithScore.second;
        }
    }
}

void Tournament::PrintTotalScore() {
    std::cout << "########## TOTAL SCORE: ##########" << std::endl;
    for (auto &nameWithScore : strategiesScores) {
        std::cout << nameWithScore.first << ": " << nameWithScore.second << std::endl;
    }
    std::cout << "##################################" << std::endl;
}

GameModeBase::Pairs Tournament::GetTotalScore() {
    Pairs result;
    for (auto &nameWithScore : strategiesScores) {
        result.push_back({nameWithScore.first, nameWithScore.second});
    }

    return result;
}

void CheckForDuplicates(std::vector<std::string> strings) {
    std::sort(strings.begin(), strings.end());

    auto duplicate = std::adjacent_find(strings.begin(), strings.end());

    if (duplicate != strings.end()) {
        throw DuplicateStrategyNameException(*duplicate);
    }
}

std::vector<StrategiesNamesCombination> GetStrategiesNamesCombinations(std::vector<std::string> &strategiesNames) {
    CheckForDuplicates(strategiesNames);

    std::vector<StrategiesNamesCombination> result;

    for (size_t i = 0; i < strategiesNames.size() - 2; i++) {
        for (size_t j = i + 1; j < strategiesNames.size() - 1; j++) {
            for (size_t k = j + 1; k < strategiesNames.size(); k++) {
                result.push_back({strategiesNames[i], strategiesNames[j], strategiesNames[k]});
            }
        }
    }

    return result;
}
