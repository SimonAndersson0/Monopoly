#pragma once
#include "ActionTile.h"
#include <string>

class Player;
class GameManager;

class TaxTile :
    public ActionTile
{
    public:
        explicit TaxTile(const int& ID, const std::string& name, int taxAmount)

            : ActionTile(ID,name), m_taxAmount(taxAmount) {}

        void onLand(Player& player, GameManager& game) override;

	    int getTaxAmount() const { return m_taxAmount; }

    private:
		int m_taxAmount;
};

