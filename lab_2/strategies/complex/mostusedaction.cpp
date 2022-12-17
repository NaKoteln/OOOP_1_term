#include "mostusedaction.h"

ActionType MostUsedActionStrategy::GetAction() {
    return nextAction;
}

void MostUsedActionStrategy::UploadOtherAnswers(std::vector<ActionType> &answers, size_t ownNumber) {
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

    nextAction = (cooperateCount < defectCount) ? DEFECT : COOPERATE;
}
