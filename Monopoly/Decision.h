// Decision.h
#pragma once
#include <variant>
#include "DecisionTypes.h"

//ask
using Decision = std::variant<
    RollDiceDecision,
    BuyPropertyDecision,
    MortgagePropertyDecision
    // later:
    // AuctionBidDecision,
    // TradeDecision
>;

//resolve
using DecisionResult = std::variant<
    RollDiceResult,
    BuyPropertyResult,
    MortgageResult
>;