#include "Map.h"
#include "Enemy.h"
#include "TimeManager.h"
#include <vector>
#include "Player.h"

/// <summary>
/// Sets the needed variables
/// </summary>
void Setup();
/// <summary>
/// Handles the inputs
/// </summary>
void Input();
/// <summary>
/// Handles the logic of the game
/// </summary>
void Logic();
/// <summary>
/// Draws the screen
/// </summary>
void Draw();

enum USER_INPUTS { NONE, UP, DOWN, RIGHT, LEFT, QUIT };
Map pacman_map = Map();
Player player = Player(pacman_map.spawn_player);
std::vector<Enemy> enemigos = std::vector<Enemy>();
Map::USER_INPUTS input = Map::USER_INPUTS::NONE;
bool run = true;
bool win = false;
bool lose = false;

int main()
{
    Setup();
    while (run)
    {
        Input();
        Logic();
        Draw();
    }
}

void Setup()
{
    std::cout.sync_with_stdio(false);

    srand(time(NULL));

    int enemy_count = 0;

    std::cout << "How many enemies do you want?" << std::endl;
    std::cin >> enemy_count;

    for (size_t i = 0; i < enemy_count; i++)
    {
        enemigos.push_back(Enemy(pacman_map.spawn_enemy));
    }

}

void Input()
{
    input = Map::USER_INPUTS::NONE;
    if (ConsoleUtils::KeyPressed(VK_UP) || ConsoleUtils::KeyPressed('W'))
    {
        input = Map::USER_INPUTS::UP;
    }
    if (ConsoleUtils::KeyPressed(VK_DOWN) || ConsoleUtils::KeyPressed('S'))
    {
        input = Map::USER_INPUTS::DOWN;
    }
    if (ConsoleUtils::KeyPressed(VK_RIGHT) || ConsoleUtils::KeyPressed('D'))
    {
        input = Map::USER_INPUTS::RIGHT;
    }
    if (ConsoleUtils::KeyPressed(VK_LEFT) || ConsoleUtils::KeyPressed('A'))
    {
        input = Map::USER_INPUTS::LEFT;
    }
    if (ConsoleUtils::KeyPressed(VK_ESCAPE) || ConsoleUtils::KeyPressed('Q'))
    {
        input = Map::USER_INPUTS::QUIT;
    }
}

void Logic()
{
    
    
    switch (input)
    {
    case Map::QUIT:
        run = false;
        return;
    }
    
    if(!win && !lose)
    {
        player.Logic(input, &pacman_map, &enemigos);

        if (player.lifes <= 0) 
        {
            lose = true;
        }

        if (pacman_map.points <= 0)
        {
            win = true;
        }
    }
}

void Draw()
{
    ConsoleUtils::Console_SetPos(0, 0);
    pacman_map.Draw();
    for (size_t i = 0; i < enemigos.size(); i++)
    {
        enemigos[i].Draw();
    }
    player.Draw();
    ConsoleUtils::Console_ClearCharacter({ 0,(short)pacman_map.Height });
    ConsoleUtils::Console_SetColor(ConsoleUtils::CONSOLE_COLOR::CYAN);
    std::cout << "Puntuacion actual: " << player.player_points << " Puntuacion pendiente: " << pacman_map.points << std::endl;
    std::cout << "Vidas actuales: " << player.lifes << std::endl;

    std::cout << "Fotogramas: " << TimeManager::getInstance().frameCount << std::endl;
    std::cout << "DeltaTime: " << TimeManager::getInstance().deltaTime << std::endl;
    std::cout << "Time: " << TimeManager::getInstance().time << std::endl;

    if (win)
    {
        ConsoleUtils::Console_SetColor(ConsoleUtils::CONSOLE_COLOR::GREEN);
        std::cout << "Has ganado!" << std::endl;
    }

    if (lose)
    {
        ConsoleUtils::Console_SetColor(ConsoleUtils::CONSOLE_COLOR::RED);
        std::cout << "Has perdido!" << std::endl;
    }

    TimeManager::getInstance().nextFrame();
}

