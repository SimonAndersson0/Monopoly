#include "Dice.h"
#include <chrono>

Dice::Dice(int amount, int maxValue)
    : m_amount(amount)
    , m_maxValue(maxValue)
    , m_rng(static_cast<unsigned>(
        std::chrono::high_resolution_clock::now().time_since_epoch().count()))
    , m_dist(1, maxValue)
{
}

std::vector<int> Dice::roll()
{
    std::vector<int> results;
    results.reserve(m_amount);

    for (int i = 0; i < m_amount; ++i)
    {
        results.push_back(m_dist(m_rng));
    }

    return results;
}

int Dice::rollTotal()
{
    int total = 0;
    for (int value : roll())
        total += value;

    return total;
}

int Dice::getAmount() const
{
    return m_amount;
}

int Dice::getMaxValue() const
{
    return m_maxValue;
}
