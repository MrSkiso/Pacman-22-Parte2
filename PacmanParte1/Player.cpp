
#include "Player.h"

Player::Player(COORD spawn)
{
    position = spawn;
}

void Player::Logic(Map::USER_INPUTS input, Map* pacman_map, std::vector<Enemy>* enemigos)
{
    bool playerDie = false;
    for (size_t i = 0; i < enemigos->size(); i++)
    {
        playerDie = enemigos->at(i).Logic(pacman_map, position);
        if (enemigos->at(i).Logic(pacman_map, position)) {
            playerDie = true;
        }
    }
    if (playerDie) {
        position = pacman_map->spawn_player;
        lifes--;
    }
    COORD position_new = position;
    switch (input)
    {
    case Map::USER_INPUTS::UP:
        position_new.Y--;
        break;
    case Map::USER_INPUTS::DOWN:
        position_new.Y++;
        break;
    case Map::USER_INPUTS::RIGHT:
        position_new.X++;
        break;
    case Map::USER_INPUTS::LEFT:
        position_new.X--;
        break;
    }
    if (position_new.X < 0)
    {
        position_new.X = pacman_map->Width - 1;
    }
    position_new.X %= pacman_map->Width;
    if (position_new.Y < 0)
    {
        position_new.Y = pacman_map->Height - 1;
    }
    position_new.Y %= pacman_map->Height;

    switch (pacman_map->GetTile(position_new.X, position_new.Y))
    {
    case Map::MAP_TILES::MAP_WALL:
        position_new = position;
        break;
    case Map::MAP_TILES::MAP_POINT:
        pacman_map->points--;
        player_points++;
        pacman_map->SetTile(position_new.X, position_new.Y, Map::MAP_TILES::MAP_EMPTY);
        break;
    }
    position = position_new;
    
}

void Player::Draw()
{
	ConsoleUtils::Console_SetPos(position);
	ConsoleUtils::Console_SetColor(foreground, background);
	std::cout << character;
}
