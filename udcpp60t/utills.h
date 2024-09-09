#pragma once

#ifndef UTILLS_H_
#define UTILLS_H_

#include "curses.h"
#include <string>

enum ArrowKeys
{
	AK_UP = KEY_UP,
	AK_DOWN = KEY_DOWN,
	AK_LEFT = KEY_LEFT,
	AK_RIGHT = KEY_RIGHT
};

void InitializeCurses(bool noDelay);
void ShutdownCurses();
void ClearScreen();
void RefreshScreen();
int ScreenWdith();
int screenHeight();
int GetChar();
void DrawCharacter(int xPos, int yPos, char aCharacter);
void MoveCursor(int xPos, int yPos);
void DrawSprite(int xPos, int yPos, const char* sprite[], int spriteHeight, int offset);
void DrawString(int xPos, int yPos, const std::string& string);
#endif // UTILLS_H_

