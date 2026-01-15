#include "Board.h"

#include "ThirdParty/tinyxml2/tinyxml2.h"   // XML parser
#include "Tile.h"       // Base class
#include "StreetTile.h"
#include "UtilityTile.h"
#include "RailroadTile.h"
#include "GoTile.h"
#include "JailTile.h"
#include "CardTile.h"
#include "CardTileType.h"
#include "TaxTile.h"
#include "FreeParkingTile.h"
#include <string>
#include <iostream>
#include <vector>
#include <sstream>


using namespace tinyxml2;

Board::Board(const std::string& xmlFilePath)
{
    loadFromXML(xmlFilePath);

    //// Debug check
    //std::cout << "Board loaded with "
    //    << m_tiles.size()
    //    << " tiles\n";
}

Tile* Board::getTileAt(int position) const
{
    if (position < 0 || position >= static_cast<int>(m_tiles.size()))
        return nullptr;
    return m_tiles[position].get();
}

Tile* Board::getTileById(int id) const
{
    for (const auto& tilePtr : m_tiles)
    {
        if (tilePtr->getID() == id)
        {
            return tilePtr.get();
        }
    }

    return nullptr; // not found
}

static std::vector<int> parseRentVector(const char* rentText)
{
    std::vector<int> rents;
    if (!rentText) return rents;

    std::stringstream ss(rentText);
    std::string item;

    while (std::getline(ss, item, ','))
    {
        rents.push_back(std::stoi(item));
    }

    return rents;
}

void Board::loadFromXML(const std::string& xmlFilePath)
{
    XMLDocument doc;
    if (doc.LoadFile(xmlFilePath.c_str()) != XML_SUCCESS)
    {
        std::cerr << "FAILED to load board XML!" << std::endl;
        return;
    }

    XMLElement* root = doc.FirstChildElement("MonopolyBoard");
    if (!root) return;

    XMLElement* boardSpaces = root->FirstChildElement("BoardSpaces");
    if (!boardSpaces) return;

    for (XMLElement* space = boardSpaces->FirstChildElement("Space");
        space;
        space = space->NextSiblingElement("Space"))
    {
		int ID = m_nextTileID++;

        XMLElement* typeElem = space->FirstChildElement("Type");
        XMLElement* nameElem = space->FirstChildElement("Name");

        const char* typeText = typeElem ? typeElem->GetText() : nullptr;
        const char* nameText = nameElem ? nameElem->GetText() : nullptr;

        if (!typeText || !nameText) continue;

        std::string type = typeText;
        std::string name = nameText;

        std::unique_ptr<Tile> tile;

        if (type == "Street")
        {
            XMLElement* colorElem = space->FirstChildElement("Color");
            XMLElement* rentElem = space->FirstChildElement("Rent");

            const char* colorText = colorElem ? colorElem->GetText() : nullptr;
            const char* rentText = rentElem ? rentElem->GetText() : nullptr;

            if (!colorText || !rentText) continue;

            int price = space->FirstChildElement("Price")->IntText();
            int houseCost = space->FirstChildElement("HouseCost")->IntText();

            std::vector<int> rent = parseRentVector(rentText);

            tile = std::make_unique<StreetTile>(ID, name, price, rent, colorText, houseCost);
        }
        else if (type == "Utility")
        {
            XMLElement* rentElem = space->FirstChildElement("Rent");
            const char* rentText = rentElem ? rentElem->GetText() : nullptr;
            if (!rentText) continue;

            int price = space->FirstChildElement("Price")->IntText();
            std::vector<int> rent = parseRentVector(rentText);

            tile = std::make_unique<UtilityTile>(ID, name, price, rent);
        }
        else if (type == "TrainStation")
        {
            XMLElement* rentElem = space->FirstChildElement("Rent");
            const char* rentText = rentElem ? rentElem->GetText() : nullptr;
            if (!rentText) continue;

            int price = space->FirstChildElement("Price")->IntText();
            std::vector<int> rent = parseRentVector(rentText);

            tile = std::make_unique<RailroadTile>(ID, name, price, rent);
        }
        else if (type == "Go")
        {
            tile = std::make_unique<GoTile>(ID,name);
        }
        else if (type == "Jail")
        {
            tile = std::make_unique<JailTile>(ID, name);
        }
        else if (type == "Chance")
        {
            tile = std::make_unique<CardTile>(ID, name, CardTileType::Chance);
        }
        else if (type == "CommunityChest")
        {
            tile = std::make_unique<CardTile>(ID, name, CardTileType::CommunityChest);
        }
        else if (type == "FreeParking")
        {
            tile = std::make_unique<FreeParkingTile>(ID, name);
        }
        else if (type == "Tax")
        {
            int amount = space->FirstChildElement("Amount")->IntText();
            tile = std::make_unique<TaxTile>(ID, name, amount);
        }

        if (tile)
            m_tiles.push_back(std::move(tile));
    }
}


