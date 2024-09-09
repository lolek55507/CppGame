#include "mainHeaderFile.h"
#include "Utills.h"
#include <curses.h>
#include <iostream>
#include <string>
#include <ctime>
#include <vector>
#include <random>
#include <chrono>
#include <thread>
using namespace std;
void InitBorders(Border& border, const int borderType);
void DrawBorders(Border& border, const int borderType);
void DrawStartScreen();
void InitGame(Game& game);
void DrawGameOverScreen(int sc);
void handleInputs(Game& game, bool& quit, Player& player, std::vector<Enemy*>& enemies, int& numberOfEnemiesToBePushed);
void DrawScoreInGameState(int& score);
void InitPlayer(Player& player);
void DrawPlayer(Player& player);
void PlayerShoot(Player& player);
void DrawPlayerMissile(Player& player, std::vector<Enemy*>& enemies, int& numberOfEnemieToBePushed);
void initMissile(Player& player);
void DrawTheGame(Player& player);
void InitEnemies(vector <Enemy*>& enemies, Player& player, int& numberOfEnemiesToBePushed);
void DrawEnemies(vector <Enemy*>& enemies, Player& player, Game& game);

const int rightBorderBlock = BR_SIZE_LEFT_RIGH - (sizeof(PlayerSprite[1]) - 3);
const int leftBorderBlock = 0;
int numberOfEnemiesToBePushed = 3;



int main()
{

    srand(time(NULL));

    bool quit = false;
    int borderWidth = 200;
    int borderHeight = 0;
    char borderCharacter = '|';
    int yPos = 30;
    int xPos = 30;
    char aCharacter = 't';
    vector <Enemy*> enemies;

    Border borderTopRight;
    Border borderBottomRight;
    Game game;
    Player player;
    InitBorders(borderTopRight, DR_RIGHT);
    InitBorders(borderBottomRight, DR_LEFT);
    InitializeCurses(true);
    InitGame(game);
    InitPlayer(player);
    int numberOfEnemiesToBePushed = 3;
    InitEnemies(enemies, player, numberOfEnemiesToBePushed);
    clock_t lastTime = clock();

    while (!quit)
    {
            handleInputs(game, quit, player, enemies, numberOfEnemiesToBePushed);
            clock_t currentTime = clock();
            clock_t dt = currentTime - lastTime;
        if (game.currentState == GS_START_SCREEN)
        {
            ClearScreen();

            DrawStartScreen();

            RefreshScreen();
        }
        else if (game.currentState == GS_GAME_OVER)
        {
            ClearScreen();
            DrawGameOverScreen(player.score);
            RefreshScreen();
        }
        else if (game.currentState == GS_PLAYING)
        {
            
            if (dt > CLOCKS_PER_SEC / FPS)
            {
                lastTime = currentTime;
                ClearScreen();
                DrawPlayerMissile(player, enemies, numberOfEnemiesToBePushed);
                DrawBorders(borderTopRight, DR_RIGHT);
                DrawBorders(borderBottomRight, DR_LEFT);
                DrawTheGame(player);
                DrawEnemies(enemies, player, game);
                RefreshScreen();
            }
            
            
            
            
            
        }


    }

    ShutdownCurses();
    return 0;
}

void InitBorders(Border& border, const int borderType)
{


    if (borderType == DR_RIGHT)
    {
        border.spriteSize = BR_SIZE_LEFT_RIGH;
        border.position.x = 1;
        border.position.y = 0;


    }
    else if (borderType == DR_LEFT)
    {
        border.spriteSize = BR_SIZE_LEFT_RIGH;
        border.position.x = 1;
        border.position.y = 28;
    }
}

void DrawBorders(Border& border, const int borderType)
{
    int offset = 0;
    int spriteHeight = 1; // Updated to match the height of BorderSprite
    DrawSprite(border.position.x, border.position.y, BorderSprite, spriteHeight, offset);


    int topPos = 0;
    int leftPos = 0;
    const char topBottomCharacter = '|';
    if (borderType == DR_RIGHT)
    {
        for (int i = 0; i < 29; i++)
        {
            DrawCharacter(leftPos, topPos, topBottomCharacter);
            topPos++;
        }
    }
    else
    {
        leftPos += BR_SIZE_LEFT_RIGH;
        for (int i = 0; i < 29; i++)
        {
            DrawCharacter(leftPos, topPos, topBottomCharacter);
            topPos++;
        }
    }

}

void InitGame(Game& game)
{
    game.currentState = GS_PLAYING;
}
void DrawStartScreen()
{
    string starScreenText = "PRESS SPACE TO START THE GAME OR PRESS Q TO QUIT";
    int drawStringY = 10;
    int drawStringX = 40;

    DrawString(drawStringX, drawStringY, starScreenText);
}

void DrawGameOverScreen(int sc)
{
    string gameOverString = "Game Over";
    string your = "Your Score was:";
    string whatToPress = "Press q to quit or space to go to starting screen";
    int drawStringY = 10;
    int drawStringX = 55;
    int scorePositionX = 59;
    int scorePositionY = 14;
    DrawString(drawStringX, drawStringY, gameOverString);
    DrawString(drawStringX - 3, drawStringY + 2, your);
    mvprintw(scorePositionY, scorePositionX, "%i", sc);
    DrawString(drawStringX - 20, drawStringY + 6, whatToPress);
}
void handleInputs(Game& game, bool& quit, Player& player, std::vector<Enemy*>& enemies, int& numberOfEnemiesToBePushed)
{
    int input = GetChar();

    switch (input)
    {
    case ' ':
        if (game.currentState == GS_START_SCREEN)
        {
            for (auto enemy : enemies) {
                delete enemy;
            }
            enemies.clear();
            numberOfEnemiesToBePushed = 3;
            InitEnemies(enemies, player, numberOfEnemiesToBePushed);
            player.missile.x = PLAYER_SHOOT_NOT_IN_PLAY;
            player.missile.y = PLAYER_SHOOT_NOT_IN_PLAY;
            game.currentState = GS_PLAYING;
        }
        else if (game.currentState == GS_GAME_OVER)
        {
            for (auto enemy : enemies) {
                delete enemy;
            }
            enemies.clear();
            game.currentState = GS_START_SCREEN;
            player.score = 0;
        }
        else if (game.currentState == GS_PLAYING)
        {
            PlayerShoot(player);
        }
        break;
    case'q':
        if (game.currentState == GS_START_SCREEN)
        {
            quit = true;
        }
        else if (game.currentState == GS_GAME_OVER)
        {
            quit = true;
        }
        else if (game.currentState == GS_PLAYING)
        {
            quit = true;
        }
        break;
    case 'a':
        if (game.currentState == GS_PLAYING)
        {
            if (player.position.x > leftBorderBlock + 1)
            {
                player.position.x -= 1;
            }

        }
        break;
    case 'd':
        if (game.currentState == GS_PLAYING)
        {
            if (player.position.x < rightBorderBlock)
            {
                player.position.x += 1;
            }

        }
        break;
    default:
        break;
    }
}

void DrawScoreInGameState(int& score)
{
    int scorePositionY = 0;
    int scorePositionX = 115;
    string scoreString = "Score: ";
    DrawString(scorePositionX - 7, scorePositionY, scoreString);
    mvprintw(scorePositionY, scorePositionX, "%i", score);
}
void initMissile(Player& player)
{
    player.missile.x = PLAYER_SHOOT_NOT_IN_PLAY;
    player.missile.y = PLAYER_SHOOT_NOT_IN_PLAY;
}
void InitPlayer(Player& player)
{
    player.position.x = BR_SIZE_LEFT_RIGH / 2;
    player.position.y = 26;
    initMissile(player);
    player.score = 0;
    
}
void DrawPlayer(Player& player)
{
    int playerHeight = 2;
    int playerOffSett = 0;
    DrawSprite(player.position.x, player.position.y, PlayerSprite, playerHeight, playerOffSett);
}
void PlayerShoot(Player& player)
{
    if (player.missile.x == PLAYER_SHOOT_NOT_IN_PLAY || player.missile.y == PLAYER_SHOOT_NOT_IN_PLAY)
    {
        player.missile.y = player.position.y - 1;
        player.missile.x = player.position.x + 2;
    }
    
    
}
void DrawPlayerMissile(Player& player, std::vector<Enemy*>& enemies, int& numberOfEnemieToBePushed)
{
    if (player.missile.y > 0 && player.missile.y != PLAYER_SHOOT_NOT_IN_PLAY && player.missile.x != PLAYER_SHOOT_NOT_IN_PLAY)
    {
        DrawCharacter(player.missile.x, player.missile.y, '|');
        
        player.missile.y -= 1;
    }
    else
    {

        player.missile.y = PLAYER_SHOOT_NOT_IN_PLAY;
        player.missile.x = PLAYER_SHOOT_NOT_IN_PLAY;
    }
    
    for (int i = 0; i < size(enemies); i++)
    {
        bool isCollision = false;

        for (int row = 2; row >= 0; --row) {
            int enemyBottomY = enemies[i]->position.y + row;
            if (player.missile.y == enemyBottomY) {
                int enemyLeftX = enemies[i]->position.x;
                int enemyRightX = enemies[i]->position.x + 6; 

                if (player.missile.x >= enemyLeftX && player.missile.x <= enemyRightX) {
                    isCollision = true;
                    break; 
                }
            }
        }

        if (isCollision) {
            delete enemies[i];
            enemies.erase(enemies.begin() + i);
            player.score += 10; 
            player.missile.x = PLAYER_SHOOT_NOT_IN_PLAY;
            player.missile.y = PLAYER_SHOOT_NOT_IN_PLAY;
            numberOfEnemiesToBePushed = 2;
            InitEnemies(enemies, player, numberOfEnemiesToBePushed);
        }
    }
}
void DrawTheGame(Player& player)
{
    DrawScoreInGameState(player.score);
    DrawPlayer(player);
}
void InitEnemies(vector <Enemy*>& enemies, Player& player, int& numberOfEnemiesToBePushed)
{
    int randomNumber = 0;
    for (int i = 0; i < numberOfEnemiesToBePushed; i++)
    {

        randomNumber = rand() % 90 + 6;
        Enemy* enemy = new Enemy();
        enemy->position.x = randomNumber;
        enemy->position.y = 1;
        enemies.push_back(enemy);
    }
    numberOfEnemiesToBePushed = 0;
}
void DrawEnemies(std::vector<Enemy*>& enemies, Player& player, Game& game)
{
    int offset = 0;
    int spriteHeight = 3;
    static std::chrono::steady_clock::time_point lastUpdate = std::chrono::steady_clock::now();
    static const std::chrono::milliseconds delayDuration(1000); 

    std::chrono::steady_clock::time_point currentTime = std::chrono::steady_clock::now();
    std::chrono::steady_clock::duration elapsedDuration = currentTime - lastUpdate;

    if (elapsedDuration < delayDuration) {
       
        for (size_t i = 0; i < enemies.size(); ++i) {
            
            DrawSprite(enemies[i]->position.x, enemies[i]->position.y, PlayerSprite, spriteHeight, offset);
        }
        return;
    }

    
    for (size_t i = 0; i < enemies.size(); ++i)
    {
        enemies[i]->position.y += 1; 
        if (enemies[i]->position.y > 28)
        {
            game.currentState = GS_GAME_OVER;
            enemies[i]->position.y = 1;
            player.position.x = BR_SIZE_LEFT_RIGH / 2;
            player.position.y = 26;

        }
        
    }

    lastUpdate = currentTime;
}

