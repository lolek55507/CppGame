#ifndef MAINHEADERFILE_H_
#define MAINHEADERFILE_H_

#include <string>
#include <vector>
#include <string>

/*
		Problem 1: Snake:

		The object of the snake game is to collect as many fruits randomly generated on the board which guarantes points to the player and increase player size.
		the player should has an optien to choose the direction to which the snake is going to and its tail should follow that direction  in the point where the player changed the snakes direction.
		snake starts at the top left corner of the board. if it hits border of the board with its head or touches its tail then the game ends and player should get prompted with a game over screen
		and points and button to start the game again.



		what variables do I need:

		General:
		________
		Snake
		Border
		Fruits
		Score
		GameState


		Snake
		_____
		Snake Direction
		Snake Size
		Snake PositionY
		Snake PositionX
		Snanke Sprite

		Border
		______
		Border Width
		Border Height
		Border Position

		Fruits
		______
		Fruit PositionY
		Fruit PositionX
		Fruit Sprite

		GameState
		_________
		Game
		Pause
		Playing
*/
enum
{
	BR_SIZE_LEFT_RIGH = 100,
	PLAYER_SHOOT_NOT_IN_PLAY,
	FPS = 20,
};


const char* BorderSprite[] = { "---------------------------------------------------------------------------------------------------" };
const char* PlayerSprite[] = { "==A==", "=====", "=X=X="};

enum GameState
{
	GS_GAME_OVER = 0,
	GS_START_SCREEN,
	GS_PLAYING,
};
enum Direction
{
	DR_LEFT = 0,
	DR_RIGHT,
	DR_DOWN,
	DR_UP,
};
struct Game
{
	int currentState;
};
struct Position
{
	int	x;
	int y;
};
struct Size
{
	int width;
	int height;
};
struct Border
{
	int spriteSize;
	Position position;
	Direction direction;
};
struct Fruits
{
	Position position;
	Size size;
};
struct Player
{
	Position position;
	Position missile;
	int score;
};
struct Enemy
{
	Position position;
	int height;
};




















#endif /* MAINHEADERFILE_H_ */