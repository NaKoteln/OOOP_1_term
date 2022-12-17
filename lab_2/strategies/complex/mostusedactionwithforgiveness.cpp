#include "mostusedactionwithforgiveness.h"

ActionType MostUsedActionWithForgivenessStrategy::GetAction() {
    return nextAction;
}

void MostUsedActionWithForgivenessStrategy::UploadOtherAnswers(std::vector<ActionType> &answers, size_t ownNumber) {
    int cooperateCount = 0;
    int defectCount = 0;

    for (size_t i = 0; i < answers.size(); i++) {
        if (i == ownNumber) continue;

        if (answers[i] == COOPERATE) {
            cooperateCount++;
        } else {
            defectCount++;
        }
    }

    int chanceToForgive = std::rand() % 100;

    if (cooperateCount < defectCount) {
        nextAction = (chanceToForgive < 10) ? COOPERATE : DEFECT;
    } else {
        nextAction = COOPERATE;
    }
}

