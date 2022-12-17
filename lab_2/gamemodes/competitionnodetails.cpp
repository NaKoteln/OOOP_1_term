#include <iostream>
#include "competitionnodetails.h"

void CompetitionNoDetailsMode::Play() {
    for (int i = 0; i < n; i++) {
        auto answers = simulator->DoNextTurn();
        auto scores = simulator->GetScoresFromAnswers(answers);
        simulator->AddScores(scores);
        simulator->UploadOtherAnswers(answers);
    }
}

GameModeBase::Pairs CompetitionNoDetailsMode::GetTotalScore() {
    return simulator->GetTotalScores();
}

void CompetitionNoDetailsMode::PrintTotalScore() {
    auto namesWithScores = simulator->GetTotalScores();
    std::cout << "########## TOTAL SCORE: ##########" << std::endl;
    for (auto& nameWithScore : namesWithScores) {
        std::cout << nameWithScore.first << ": " << nameWithScore.second << std::endl;
    }
}
