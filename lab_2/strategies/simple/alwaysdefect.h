#ifndef LAB_2_ALWAYSDEFECT_H
#define LAB_2_ALWAYSDEFECT_H

#include "../../strategy.h"

class AlwaysDefectStrategy : public StrategyBase {
public:
    AlwaysDefectStrategy(std::string strategyName) : StrategyBase(strategyName) {}
    ~AlwaysDefectStrategy() override = default;

    ActionType GetAction() override;

    void UploadOtherAnswers(std::vector<ActionType> &answers, size_t ownNumber) override;
};

#endif //LAB_2_ALWAYSDEFECT_H
