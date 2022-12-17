#include <cassert>
#include "simulator.h"

std::vector<ActionType> Simulator::DoNextTurn() {
    std::vector<ActionType> answers(strategies.size());

    for (size_t i = 0; i < strategies.size(); i++) {
        answers[i] = strategies[i]->GetAction();
    }

    return answers;
}

std::vector<int> Simulator::GetScoresFromAnswers(std::vector<ActionType> &answers) {
    auto it = gameMatrix.find(answers);
    if (it == gameMatrix.end()) {
        throw MappingNotFoundException(answers);
    }

    auto scores = it->second;
    return scores;
}

void Simulator::AddScores(std::vector<int> &scores) {
    for (size_t i = 0; i < strategies.size(); i++) {
        strategies[i]->AddScore(scores[i]);
    }
}

void Simulator::UploadOtherAnswers(std::vector<ActionType> &answers) {
    for (size_t i = 0; i < strategies.size(); i++) {
        strategies[i]->UploadOtherAnswers(answers, i);
    }
}

void FillDefaultMatrix(std::map<std::vector<ActionType>, std::vector<int>>& matrix);

Simulator::Simulator(StrategyFactory &factory, std::vector<std::string> &strategiesNames, GameMatrix &matrix) {
    for (auto& name : strategiesNames) {
        strategies.push_back(factory.GetStrategyByName(name));
    }

    if (matrix.empty()) {
        FillDefaultMatrix(gameMatrix);
    } else {
        gameMatrix = matrix;
    }
}

Simulator::~Simulator() {
    for (auto it = strategies.begin(); it < strategies.end(); ) {
        delete *it;
        it = strategies.erase(it);
    }
//    strategies.clear();
    assert(strategies.empty());
}

Simulator::Pairs Simulator::GetTotalScores() {
    Pairs result;
    for (auto& strategy : strategies) {
        result.push_back({strategy->GetName(), strategy->GetScore()});
    }

    return result;
}

void FillDefaultMatrix(std::map<std::vector<ActionType>, std::vector<int>>& matrix) {
    matrix[{COOPERATE,  COOPERATE,  COOPERATE}] = {7, 7, 7};
    matrix[{COOPERATE,  COOPERATE,  DEFECT}]    = {3, 3, 9};
    matrix[{COOPERATE,  DEFECT,     COOPERATE}] = {3, 9, 3};
    matrix[{DEFECT,     COOPERATE,  COOPERATE}] = {9, 3, 3};
    matrix[{COOPERATE,  DEFECT,     DEFECT}]    = {0, 5, 5};
    matrix[{DEFECT,     COOPERATE,  DEFECT}]    = {5, 0, 5};
    matrix[{DEFECT,     DEFECT,     COOPERATE}] = {5, 5, 0};
    matrix[{DEFECT,     DEFECT,     DEFECT}]    = {1, 1, 1};
}
