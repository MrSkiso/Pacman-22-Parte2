#pragma once
#include "Map.h"
#include "Enemy.h"

class Player
{
public:
	COORD position;
	int player_points = 0;
	int lifes = 3;
private:
	char character = 'O';
	ConsoleUtils::CONSOLE_COLOR foreground = ConsoleUtils::CONSOLE_COLOR::DARK_YELLOW;
	ConsoleUtils::CONSOLE_COLOR background = ConsoleUtils::CONSOLE_COLOR::BLACK;
public:

	Player(COORD spawn);
	void Logic(Map::USER_INPUTS input, Map* pacman_map, std::vector<Enemy>* enemigos);
	void Draw();

	
};
