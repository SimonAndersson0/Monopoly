#pragma once

#include <string>
#include <vector>
#include <random>

class Card;

class CardDeck
{
	public:
		CardDeck(const std::string& xmlFilePath); //initialize an deck

		Card draw();
		void returnCard(const Card& card);//returnCard() takes a reference to avoid copying twice
		void shuffle();

	private:
		std::vector<Card> m_cards;
		std::mt19937 m_rng; // Random number generator for shuffling

		// Helper to load XML
		void loadFromXML(const std::string& xmlFilePath);

};

