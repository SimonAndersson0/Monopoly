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
#include <iostream>


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

void Board::loadFromXML(const std::string& xmlFilePath)
{
    //std::cout << "Loading board XML from: "
    //    << xmlFilePath << std::endl;

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
        const char* typeText = space->FirstChildElement("Type")->GetText();
        const char* nameText = space->FirstChildElement("Name")->GetText();
        if (!typeText || !nameText) continue;

        std::string type = typeText;
        std::string name = nameText;

        // We'll create the appropriate Tile subclass
        std::unique_ptr<Tile> tile;

        if (type == "Street")
        {
            const char* colorText = space->FirstChildElement("Color")->GetText();
			if (!colorText) continue;
            std::string color = colorText;
            int price = space->FirstChildElement("Price")->IntText();
            int rent = space->FirstChildElement("Rent")->IntText();
            int houseCost = space->FirstChildElement("HouseCost")->IntText();

            tile = std::make_unique<StreetTile>(name, price, rent, color, houseCost);
        }
        else if (type == "Utility")
        {
            int price = space->FirstChildElement("Price")->IntText();
            int rent = space->FirstChildElement("Rent")->IntText();
            tile = std::make_unique<UtilityTile>(name, price, rent);
        }
        else if (type == "TrainStation")
        {
            int price = space->FirstChildElement("Price")->IntText();
            int rent = space->FirstChildElement("Rent")->IntText();
            tile = std::make_unique<RailroadTile>(name, price, rent);
        }
        else if (type == "Go")
        {
            tile = std::make_unique<GoTile>(name);
        }
        else if (type == "Jail")
        {
            tile = std::make_unique<JailTile>(name);
        }
        else if (type == "Chance")
        {
            tile = std::make_unique<CardTile>(name, CardTileType::Chance);
        }
        else if (type == "CommunityChest")
        {
            tile = std::make_unique<CardTile>(name, CardTileType::CommunityChest);
        }
        else if (type == "FreeParking")
        {
            tile = std::make_unique<FreeParkingTile>(name);
        }
        else if (type == "Tax")
        {
            int amount = space->FirstChildElement("Amount")->IntText();
            tile = std::make_unique<TaxTile>(name, amount);
        }

        if (tile)
            m_tiles.push_back(std::move(tile));
    }
}
