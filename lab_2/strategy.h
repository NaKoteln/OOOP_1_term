#ifndef LAB_2_STRATEGY_H
#define LAB_2_STRATEGY_H

#include <vector>
#include <string>
#include <map>

enum ActionType {
    COOPERATE,
    DEFECT
};

using GameMatrix = std::map<std::vector<ActionType>, std::vector<int>>;

class StrategyBase {
protected:
    int score;
    std::string name;

public:
    StrategyBase(std::string& strategyName) : name(strategyName), score(0) {}

    virtual ~StrategyBase() = default;

    virtual ActionType GetAction() = 0;

    virtual void UploadOtherAnswers(std::vector<ActionType> &answers, size_t ownNumber) = 0;

    void AddScore(int additionScore) { score += additionScore; }

    int GetScore() const { return score; }

    std::string GetName() const { return name; }
};

#endif //LAB_2_STRATEGY_H
