#pragma once
#include <string>

class Player;
class GameManager;

class Tile
{
	public:
		virtual ~Tile() = default;

		virtual void onLand(Player& player, GameManager& game) = 0;

		explicit Tile(const int& ID, const std::string& name);

		std::string getName() const { return m_name; }
		int getID() const { return m_ID; }
	private:
		
	protected:
		std::string m_name;
		int m_ID;

};

