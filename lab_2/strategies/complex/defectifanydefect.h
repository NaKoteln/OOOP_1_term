#ifndef LAB_2_DEFECTIFANYDEFECT_H
#define LAB_2_DEFECTIFANYDEFECT_H

#include "../../strategy.h"

class DefectIfAnyDefectStrategy : public StrategyBase {
private:
    ActionType nextAction;

public:
    DefectIfAnyDefectStrategy(std::string strategyName) : StrategyBase(strategyName) { nextAction = COOPERATE; }

    ~DefectIfAnyDefectStrategy() override = default;

    ActionType GetAction() override;

    void UploadOtherAnswers(std::vector<ActionType> &answers, size_t ownNumber) override;
};

#endif //LAB_2_DEFECTIFANYDEFECT_H
