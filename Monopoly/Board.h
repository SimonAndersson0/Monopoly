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
    Tile* getTileById(int ID) const;
    

	int getSize() const { return static_cast<int>(m_tiles.size()); }

private:
    std::vector<std::unique_ptr<Tile>> m_tiles;
    int m_nextTileID = 0; // 1-?

    // Helper to load XML
    void loadFromXML(const std::string& xmlFilePath);
};
