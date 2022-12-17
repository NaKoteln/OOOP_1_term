#include "defectifanydefect.h"

ActionType DefectIfAnyDefectStrategy::GetAction() {
    return nextAction;
}

void DefectIfAnyDefectStrategy::UploadOtherAnswers(std::vector<ActionType> &answers, size_t ownNumber) {
    int defectCount = 0;

    for (size_t i = 0; i < answers.size(); i++) {
        if (i == ownNumber) continue;

        if (answers[i] == DEFECT) {
            defectCount++;
            break;
        }
    }

    nextAction = (defectCount) ? DEFECT : COOPERATE;
}
