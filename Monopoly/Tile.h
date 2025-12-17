#pragma once

class Player;
class GameManager;

class Tile
{
	public:
		virtual ~Tile() = default;
		virtual void onLand(Player& player, GameManager& game) = 0;
		explicit Tile(const std::string& name) : m_name(name) {}
		std::string getName() const { return m_name; }
	private:
		std::string m_name;
};

