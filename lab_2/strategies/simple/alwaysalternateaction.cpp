#include "alwaysalternateaction.h"

ActionType AlwaysAlternateActionStrategy::GetAction() {
    return nextAction;
}

void AlwaysAlternateActionStrategy::UploadOtherAnswers(std::vector<ActionType> &answers, size_t ownNumber) {
    switch (nextAction) {
        case COOPERATE:
            nextAction = DEFECT;
            break;
        case DEFECT:
            nextAction = COOPERATE;
            break;
    }
}
