#pragma once

#include <vector>
#include <memory>
#include <string>

// Forward declaration
class Tile;

class Board
{
public:
    // Construct from an XML file
    Board(const std::string& xmlFilePath);

    //not needed since uníque_ptr is used
    ~Board() = default;

    // Access a tile by index
    Tile* getTileAt(int position) const;
    const std::vector<std::unique_ptr<Tile>>& getTiles() const { return m_tiles; }

private:
    std::vector<std::unique_ptr<Tile>> m_tiles;

    // Helper to load XML
    void loadFromXML(const std::string& xmlFilePath);
};
