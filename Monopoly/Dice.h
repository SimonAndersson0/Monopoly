#pragma once

#include <random>
#include <vector>

class Dice
{
public:
    // amount = number of dice
    // maxValue = max value per die (e.g. 6)
    Dice(int amount, int maxValue);

    // Roll all dice and return individual values
    std::vector<int> roll();

    // Roll and return sum
    int rollTotal();

    int getAmount() const;
    int getMaxValue() const;

private:
    int m_amount;
    int m_maxValue;

    std::mt19937 m_rng;
    std::uniform_int_distribution<int> m_dist;
};
