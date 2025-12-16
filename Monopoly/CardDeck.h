#pragma once

#include <string>
#include <vector>

class Card;

class CardDeck
{
	public:
		CardDeck();
	private:
	std::vector<Card*> m_properties;
};

