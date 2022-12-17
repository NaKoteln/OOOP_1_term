#ifndef LAB_2_ALWAYSALTERNATEACTION_H
#define LAB_2_ALWAYSALTERNATEACTION_H

#include "../../strategy.h"

class AlwaysAlternateActionStrategy : public StrategyBase {
private:
    ActionType nextAction;
public:
    AlwaysAlternateActionStrategy(std::string strategyName) : StrategyBase(strategyName) { nextAction = COOPERATE; }
    ~AlwaysAlternateActionStrategy() override = default;

    ActionType GetAction() override;

    void UploadOtherAnswers(std::vector<ActionType> &answers, size_t ownNumber) override;
};

#endif //LAB_2_ALWAYSALTERNATEACTION_H
