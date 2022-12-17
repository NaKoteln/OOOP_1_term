#include "alwaysdefect.h"

ActionType AlwaysDefectStrategy::GetAction() {
    return DEFECT;
}

void AlwaysDefectStrategy::UploadOtherAnswers(std::vector<ActionType> &answers, size_t ownNumber) {

}
