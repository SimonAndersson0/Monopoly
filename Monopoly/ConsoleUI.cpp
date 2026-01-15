#include "ConsoleUI.h"
#include <iostream>
#include "Player.h"
#include "Tile.h"
#include "PropertyTile.h"
#include "Decision.h"
#include "TradeOffer.h"

void ConsoleUI::onTurnStarted(const Player& player)
{
    std::cout << "\n--- " << player.getName() << "'s turn ---\n";
}

void ConsoleUI::onDiceRolled(const Player& player, int total)
{
    std::cout << player.getName() << " rolled " << total << "\n";
}

void ConsoleUI::onPlayerMoved(const Player& player, const Tile& tile)
{
    std::cout << player.getName()
        << " landed on " << tile.getName() << "\n";
}

void ConsoleUI::onMoneyChanged(const Player& player, int amount)
{
    std::cout << player.getName()
        << " now has $" << amount << "\n";
}

void ConsoleUI::onGameOver()
{
    std::cout << "Game Over!\n";
}
void ConsoleUI::onPropertyBought(const Player& player, const PropertyTile& property)
{
    std::cout << player.getName() << " bought " << property.getName() << " for $" << property.getPrice() << "\n";
}
void ConsoleUI::onBankruptcy(const Player& player)
{
    std::cout << player.getName() << " has declared bankruptcy!\n";
}
void ConsoleUI::onPassGo(const Player& player) {
    showMessage(player.getName() + " Has passed go");
}

void ConsoleUI::onTradeProposed(const TradeOffer& trade)
{
	std::cout << trade.proposer->getName() << " has proposed a trade to " << trade.target->getName() << "\n";
}

void ConsoleUI::onMortgage(const Player& player, const PropertyTile& property)
{
    showMessage(player.getName() + " Has morgaged " + property.getName());
}


//inputs
void ConsoleUI::waitForRoll(const Player& player)
{
    waitForEnter(player.getName() + ", press ENTER to roll the dice...");
}

bool ConsoleUI::requestBuyProperty(
    const Player& player,
    const PropertyTile& property)
{
    std::string prompt =
        player.getName() + ", do you want to buy " +
        property.getName() +
        " for " + std::to_string(property.getPrice()) + "?";

    return askYesNo(prompt);
}

int ConsoleUI::requestMortgageProperty(const Player& player)
{
    const auto& properties = player.getProperties();

    if (properties.empty())
    {
        showMessage("You own no properties to mortgage.");
        return -1;
    }
	std::cout << "Your properties:\n";
    for (size_t i = 0; i < properties.size(); ++i)
    {
        const auto& prop = properties[i];
        std::cout << i + 1 << ". " << prop->getName()
			<< "(ID: )" << prop->getID()
            << " (Price: $" << prop->getPrice()
            << ", Mortgaged: " << (prop->isMortgaged() ? "Yes" : "No") << ")\n";
    }
	while (true) //loop till choice is valid or cancelled
    {
        int choice = askInt("Enter the ID of the property to mortgage (or 0 to cancel):");
        if (choice == 0)
        {
            showMessage("Mortgage cancelled.");
            return -1;
		}
        for (const auto& prop : properties)
        {
            if (prop->getID() == choice)
            {
                return prop->getID();
            }
            else {
                showMessage("Invalid property ID. Try again.");
			}
        }
	}

}

//temp solution for starting 
int ConsoleUI::requestPlayerCount()
{
    return askInt("Enter number of players:");
}
std::string ConsoleUI::requestPlayerName(int index)
{
    return askString("Enter name for player " + std::to_string(index + 1) + ":");
}
bool ConsoleUI::requestIsBot(const std::string& playerName)
{
    return askYesNo("Is " + playerName + " a bot?");
}

//TEMP
void ConsoleUI::waitForEnter(const std::string& msg)
{
    std::cout << msg;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int ConsoleUI::askInt(const std::string& prompt)
{
    int value;
    while (true)
    {
        std::cout << prompt << " ";
        if (std::cin >> value)
        {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return value;
        }

        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid number. Try again.\n";
    }
}

std::string ConsoleUI::askString(const std::string& prompt)
{
    std::string value;
    std::cout << prompt << " ";
    std::getline(std::cin, value);
    return value;
}

bool ConsoleUI::askYesNo(const std::string& prompt)
{
    char input;
    while (true)
    {
        std::cout << prompt << " (y/n): ";
        std::cin >> input;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        input = std::tolower(input);
        if (input == 'y') return true;
        if (input == 'n') return false;

        std::cout << "Invalid input. Please enter y or n.\n";
    }
}
void ConsoleUI::showMessage(const std::string& msg)
{
    std::cout << msg << "\n";
}

void ConsoleUI::onDecisionRequested(const Decision& decision)
{

    std::cout << "Decision requested: " ;
              
}