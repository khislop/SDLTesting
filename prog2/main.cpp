/*This source code copyrighted by Lazy Foo' Productions (2004-2017)
and may not be redistributed without written permission.*/

//Using SDL, SDL_image, standard IO, and strings
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include "init.h"
#include "dialogue.h"




int main( int argc, char* args[] )
{

    //Start up SDL and create window
    if( !init() )
    {
        printf( "Failed to initialize!\n" );
        close();
        return 1;
    }

    // Run initilization for display code
    InitMainMenu();
	InitDialogue();

    // Main loop flag
    bool quit = false;

    // Event handler
    SDL_Event e;

    //Application main loop 
    while( !quit )
    {
        quit |= RoomLoop(&e);
		quit |= GetQuit();
    }

    //Free resources and close SDL
    close();

    return 0;
}
