#include "alwayscooperate.h"

ActionType AlwaysCooperateStrategy::GetAction() {
    return COOPERATE;
}

void AlwaysCooperateStrategy::UploadOtherAnswers(std::vector<ActionType> &answers, size_t ownNumber) {
}
