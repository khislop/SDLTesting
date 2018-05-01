#ifndef ROOM_HOME_H
#define ROOM_HOME_H

#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include <cmath>
#include "init.h"
#include "button.h"
#include "texture.h"


void InitRoomHome();
void CloseRoomHome();
static void DrawGraphics();
static void ButtonAction(int i);
static bool UpdateLoop( SDL_Event* e );
static void ClearButtons();
static bool HandleEvents( SDL_Event* e );

#endif