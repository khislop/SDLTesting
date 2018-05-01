#ifndef INIT_H
#define INIT_H

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "time.h"

// Points to the main loop of current screen
extern bool (*RoomLoop)( SDL_Event* e );

//Starts up SDL and creates window
bool init();

//Frees media and shuts down SDL
void close();

// Quit function to be able to quit from anywhere
void QuitGame();
bool GetQuit();


//Loads individual image as texture
SDL_Texture* loadTexture( std::string path );

//Loads text as texture
SDL_Texture* loadTextureText( std::string textureText, TTF_Font* gFont, SDL_Color textColor );

long GetTimer();
bool IsTimerUp(clock_t start_time, int num_mseconds);
long GetTimePassed(clock_t start_time);

void SetRoomLoop(bool (*func)( SDL_Event* e ));

//Getters
SDL_Renderer* getRenderer();
SDL_Window* GetWindow();
const int GetWindowWidth();
const int GetWindowHeight();

// Redefine init functions so each room doesn't have to inclue eachother
void InitMainMenu();
void InitRoomHome();
void InitDialogue();

#endif