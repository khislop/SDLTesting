#pragma once
#ifndef DIALOGUE_H
#define DIALOGUE_H

#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include <cmath>
#include "init.h"
#include "button.h"
#include "texture.h"


void InitDialogue();
void CloseDialogue();
bool HandleDialogueEvents(SDL_Event* e);
bool UpdateDialogue(SDL_Event* e);
void UpdateCursor();
void UpdateLine();
static void DrawDialogue();
void LoadDialogue(std::string fileName);
bool DialogueLoaded();
bool NextWordHasRoom(std::string textString, int pos, int maxWidth, TTF_Font* font);



#endif