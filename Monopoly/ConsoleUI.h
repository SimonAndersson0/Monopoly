#pragma once
#include "UI.h"
#include <string>
struct Decision;
struct TradeOffer;

class ConsoleUI : public UI
{
public:
    // Observer
    void onTurnStarted(const Player& player) override;
    void onDiceRolled(const Player& player, int total) override;
    void onPlayerMoved(const Player& player, const Tile& tile) override;
    void onMoneyChanged(const Player& player, int newAmount) override;
    void onGameOver() override;
	void onPropertyBought(const Player& player, const PropertyTile& property) override;
	void onBankruptcy(const Player& player) override;
    void onPassGo(const Player& player) override;
    void onTradeProposed(const TradeOffer& trade) override;


    // Input
    void waitForRoll(const Player& player) override;
    bool requestBuyProperty(const Player&, const PropertyTile&) override;
    PropertyTile* requestMortgageProperty(const Player&) override;

    //temp solution for starting 
    int requestPlayerCount() override;
    std::string requestPlayerName(int index) override;
    bool requestIsBot(const std::string& playerName) override;

    //temp
    void showMessage(const std::string& msg);
    void waitForEnter(const std::string& msg);
    int askInt(const std::string& prompt);
    std::string askString(const std::string& prompt);
    bool askYesNo(const std::string& prompt);

	void onDecisionRequested(const Decision& decision) override;

};
