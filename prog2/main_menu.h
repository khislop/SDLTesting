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


void InitMainMenu();
void CloseMainMenu();
static void DrawGraphics();
static void ButtonAction(int i);
static bool UpdateLoop( SDL_Event* e );
static void ClearButtons();
static bool HandleEvents( SDL_Event* e );

#endif