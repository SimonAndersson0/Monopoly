#pragma once
#include "ActionTile.h"
class TaxTile :
    public ActionTile
{
    public:
        explicit TaxTile(const std::string& name, int taxAmount)

            : ActionTile(name), m_taxAmount(taxAmount) {}

        void onLand(Player& player, GameManager& game) override;

	    int getTaxAmount() const { return m_taxAmount; }

    private:
		int m_taxAmount;
};

