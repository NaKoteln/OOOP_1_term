#include <iostream>
#include "competitionwithdetails.h"

std::string ToString(ActionType actionType);

void CompetitionWithDetailsMode::Play() {
    size_t ternNumber = 0;
    std::cin.exceptions(std::istream::failbit | std::istream::badbit);
    while (!std::cin.eof()) {
        std::string currentLine;
        getline(std::cin, currentLine);

        if (currentLine == "quit") return;

        ternNumber++;

        auto answers = simulator->DoNextTurn();
        auto scores = simulator->GetScoresFromAnswers(answers);

        simulator->AddScores(scores);
        simulator->UploadOtherAnswers(answers);
        auto namesWithTotalScores = simulator->GetTotalScores();

        for (size_t i = 0; i < namesWithTotalScores.size(); i++) {
            std::cout
                    << "Turn " << ternNumber << ": " << namesWithTotalScores[i].first
                    << ": [Action: " << ToString(answers[i])
                    << ", Total Score: " << namesWithTotalScores[i].second
                    << ", Score Per Turn: " << scores[i] << "]" << std::endl;
        }
    }
}

void CompetitionWithDetailsMode::PrintTotalScore() {
    auto scores = simulator->GetTotalScores();
    std::cout << "########## TOTAL SCORE: ##########" << std::endl;
    for (auto &score: scores) {
        std::cout << score.first << ": " << score.second << std::endl;
    }
    std::cout << "##################################" << std::endl;
}

GameModeBase::Pairs CompetitionWithDetailsMode::GetTotalScore() {
    return simulator->GetTotalScores();
}

std::string ToString(ActionType actionType) {
    return actionType == COOPERATE ? "COOPERATE" : "DEFECT";
}
