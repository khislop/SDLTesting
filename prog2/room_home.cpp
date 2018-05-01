//Using SDL, SDL_image, standard IO, math, and strings
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include <cmath>
#include "init.h"
#include "button.h"
#include "texture.h"
#include "room_home.h"
#include "dialogue.h"

// Using statments to reduce excess syntax
using std::to_string;

// Define button IDs
enum ButtonStates{
    BUTTON_ONE,
    BUTTON_TWO,
	BUTTON_THREE,
    MAX_BUTTONS
};

// Define backgrounds

// Define quit flag
static bool quit = false;

// Define timers

// Define backgrounds
static Texture roomBackground = Texture();

// Define misc images

// Define text textures
static Texture titleText = Texture();

// Define fonts
static TTF_Font* fontSnackerComic52;
static TTF_Font* fontNizzoliB24;
static TTF_Font* fontTechnott24;

// Define colors
static SDL_Color white = {255, 255, 255};
static SDL_Color black = {0, 0, 0};

// Define button structure
static Button* buttons[MAX_BUTTONS];

// Define internal variables
bool inDialogue;

static bool HandleEvents( SDL_Event* e ){
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
                if(buttons[i]->inside(x, y)){
                    buttons[i]->pressed = true;
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
                if(buttons[i]->inside(x, y) && 
                    buttons[i]->pressed && 
                    buttons[i]->active)
                {
                    ButtonAction(i);               
                }
            }


            // For each button make sure pressed is false
            for( int i = 0; i < MAX_BUTTONS; i++ )
            {
                buttons[i]->pressed = false;
            }


        }

        // Movement

    }

    return quit;

}

static void ButtonAction(int i){

    switch(buttons[i]->id){
        case BUTTON_ONE:
            break;
        case BUTTON_TWO:
            break;
		case BUTTON_THREE:
			break;
    }

}

// Runs every loop game loop
static bool UpdateLoop( SDL_Event* e )
{
    // Call functions we want to run every loop
	DrawGraphics();
	if (!inDialogue) {
		HandleEvents(e);
	}
	else {
		if (UpdateDialogue(e)) {
			inDialogue = false;
		}
	}

    return quit;
}

static void ClearButtons(){
    for(int i = 0; i < MAX_BUTTONS; i++){
        buttons[i]->clear();
    }
}

static void DrawGraphics()
{
    SDL_Renderer *renderer = getRenderer();

    //Clear screen
    SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );
    //SDL_SetRenderDrawColor( renderer, 0x00, 0x00, 0x00, 0x00 );
    SDL_RenderClear( renderer );

    // Draw backgrounds
	roomBackground.render(0, 0);

    // Draw text
    titleText.render(GetWindowWidth()/4, GetWindowHeight()/2, 0.5, 0.5);

    // Draw buttons
    for( int i = 0; i < MAX_BUTTONS; i++ )
    {
        if(buttons[i]->visible == true){
            buttons[i]->draw(renderer);
        }
    }

    //Update screen
	if (!inDialogue) {
		SDL_RenderPresent(renderer);
	}

}

void InitRoomHome (){
    // Tell main to call this files main loop
    SetRoomLoop(UpdateLoop);

    // Open TTF font
    fontSnackerComic52 = TTF_OpenFont( "fonts/SnackerComic.ttf", 52 );
    fontNizzoliB24 = TTF_OpenFont( "fonts/NizzoliSemiBold.ttf", 24 );
    fontTechnott24 = TTF_OpenFont( "fonts/technott.ttf", 24 );

    // Define colors
    //white = {255, 255, 255};

    // Initilize perameters

    // Define Backgrounds
	roomBackground.loadFromFile("graphics/Background.png");

    // Define misc images 

    // Initilize text textures
    //titleText = Texture();
    titleText.loadText("Welcome to home.", black, fontSnackerComic52);
   
   
    // Set up buttons
	buttons[BUTTON_ONE] = new Button(BUTTON_ONE, GetWindowWidth() * 0.7, GetWindowHeight() * 0.2, NULL, NULL, (char*)"graphics/BlankButton.png", (char*)"graphics/BlankButtonP.png");
    buttons[BUTTON_ONE]->setText("Button 1", black, fontNizzoliB24 );
	buttons[BUTTON_TWO] = new Button(BUTTON_TWO, GetWindowWidth() * 0.7, GetWindowHeight() * 0.4, NULL, NULL, (char*)"graphics/BlankButton2.png", (char*)"graphics/BlankButton2P.png");
    buttons[BUTTON_TWO]->setText("Button 2", black, fontTechnott24);
	buttons[BUTTON_THREE] = new Button(BUTTON_THREE, GetWindowWidth() * 0.7, GetWindowHeight() * 0.6, NULL, NULL, (char*)"graphics/Button2.png", (char*)"graphics/Button2P.png");
  
    // If there is dialogue loaded, play dialogue
	if (DialogueLoaded()) {
		inDialogue = true;
	}
}

void CloseRoomHome(){

}