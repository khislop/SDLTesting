//Using SDL, SDL_image, standard IO, math, and strings
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include <cmath>
#include "init.h"
#include "button.h"
#include "texture.h"
#include "main_menu.h"
#include "time.h"

// Using statments to reduce excess syntax
using std::to_string;

// Define button IDs
enum ButtonStates{
    BUTTON_START,
    BUTTON_QUIT,
    MAX_BUTTONS
};

// Define backgrounds

// Define quit flag
bool quit = false;

// Define timers

// Define backgrounds

// Define misc images

// Define text textures
Texture titleText = Texture();

// Define fonts
TTF_Font* fontSnackerComic52;

// Define colors
SDL_Color white = {255, 255, 255};
SDL_Color black = {255, 255, 255};

// Define button structure
Button buttons[MAX_BUTTONS];

// Define internal variables

bool HandleEvents( SDL_Event* e ){
    int x, y;

    //Handle events on queue
    while( SDL_PollEvent( e ) != 0 )
    {
        //User requests quit
        if( e->type == SDL_QUIT )
        {
            quit = true;
        }

        //Right click down
        if( e->type == SDL_MOUSEBUTTONDOWN && e->button.button == SDL_BUTTON_RIGHT){
            // Do stuff
        }

        //Click down
        if( e->type == SDL_FINGERDOWN || e->type == SDL_MOUSEBUTTONDOWN){
            //Get mouse x and y
            x = e->button.x;
            y = e->button.y;

            // For each button if pressed, set pressed var
            for( int i = 0; i < MAX_BUTTONS; i++ )
            {
                if(buttons[i].inside(x, y)){
                    buttons[i].pressed = true;
                }
            }

        } 

        //Release click
        if( e->type == SDL_FINGERUP || e->type == SDL_MOUSEBUTTONUP){
            x = e->button.x;
            y = e->button.y;

            // For each button if clicked
            for( int i = 0; i < MAX_BUTTONS; i++ )
            {
                if(buttons[i].inside(x, y) && 
                    buttons[i].pressed && 
                    buttons[i].active)
                {
                    ButtonAction(i);               
                }
            }


            // For each button make sure pressed is false
            for( int i = 0; i <= MAX_BUTTONS; i++ )
            {
                buttons[i].pressed = false;
            }


        }

        // Movement

    }

    return quit;

}

void ButtonAction(int i){

    switch(buttons[i].id){
        case BUTTON_START:
            break;
        case BUTTON_QUIT:
            break;
    }

}

// Runs every loop game loop
bool UpdateLoop( SDL_Event* e )
{
    // Call functions we want to run every loop
    HandleEvents( e );
    DrawGraphics();

    return quit;
}

void ClearButtons(){
    for(int i = 0; i < MAX_BUTTONS; i++){
        buttons[i].clear();
    }
}

void DrawGraphics()
{
    SDL_Renderer *renderer = getRenderer();

    //Clear screen
    SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );
    //SDL_SetRenderDrawColor( renderer, 0x00, 0x00, 0x00, 0x00 );
    SDL_RenderClear( renderer );

    // Draw backgrounds

    // Draw text
    titleText.render(100, 100);

    // Draw buttons
    for( int i = 0; i <= MAX_BUTTONS; i++ )
    {
        if(buttons[i].visible == true){
            buttons[i].draw(renderer);
        }
    }

    //Update screen
    SDL_RenderPresent( renderer );

}

void InitDisplay (){

    // Open TTF font
    fontSnackerComic52 = TTF_OpenFont( "fonts/SnackerComic.ttf", 52 );

    // Define colors
    //white = {255, 255, 255};

    // Initilize perameters

    // Define Backgrounds

    // Define misc images 

    // Initilize text textures
    //titleText = Texture();
    titleText.loadText("This is a text", white, fontSnackerComic52);
   
   
    // Set up buttons
  
    // Set up blend mode
}

void CloseDisplay(){

}