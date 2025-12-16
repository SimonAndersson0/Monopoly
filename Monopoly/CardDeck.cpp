#include "CardDeck.h"
#include "Card.h"
#include <algorithm>





CardDeck::CardDeck(const std::string& xmlFilePath)
    : m_rng(std::random_device{}()) // seed RNG
{
    loadFromXML(xmlFilePath);       // load cards
    shuffle();                      // shuffle deck immediately
}

Card CardDeck::draw()
{
    if (m_cards.empty())
        throw std::runtime_error("Deck is empty");

    Card card = m_cards.back();
    m_cards.pop_back();
    return card;
}


void CardDeck::returnCard(const Card& card)
{
    m_cards.insert(m_cards.begin(), card); // bottom of deck
}

void CardDeck::shuffle()
{
    std::shuffle(m_cards.begin(), m_cards.end(), m_rng);
}



void CardDeck::loadFromXML(const std::string& xmlFilePath)
{

}

