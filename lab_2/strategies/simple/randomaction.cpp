#include "randomaction.h"

ActionType RandomActionStrategy::GetAction() {
    return (std::rand() % 2) ? COOPERATE : DEFECT;
}

void RandomActionStrategy::UploadOtherAnswers(std::vector<ActionType> &answers, size_t ownNumber) { }
