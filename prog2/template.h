#ifndef MAIN_MENU_H
#define MAIN_MENU_H

#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include <cmath>
#include "init.h"
#include "button.h"
#include "texture.h"


void InitDisplay ();
void CloseDisplay();
void DrawGraphics();
void ButtonAction(int i);
bool UpdateLoop( SDL_Event* e );
void ClearButtons();
bool HandleEvents( SDL_Event* e );
void RestoreStateDisplay();

#endif