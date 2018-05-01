//Using SDL, SDL_image, standard IO, math, and strings
#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <cmath>
#include "init.h"
#include "button.h"
#include "texture.h"
#include "dialogue.h"
#include "main_menu.h"

// Using statments to reduce excess syntax
using std::to_string;

// Define button IDs
enum ButtonStates{
    BUTTON_START,
	BUTTON_LOAD,
    BUTTON_QUIT,
    MAX_BUTTONS
};

// Define backgrounds

// Define quit flag
static bool quit = false;

// Define timers

// Define backgrounds
static Texture mainMenuBackground = Texture();

// Define misc images

// Define text textures
static Texture titleText = Texture();

// Define fonts
static TTF_Font* fontSnackerComic52;

// Define colors
static SDL_Color white = {255, 255, 255};
static SDL_Color black = {255, 255, 255};

// Define button structure
static Button* buttons[MAX_BUTTONS];

// Define internal variables
static int mouseX, mouseY;


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
        case BUTTON_START:
			LoadDialogue("dialogue/Test.txt");
            InitRoomHome();
            break;
		case BUTTON_LOAD:

			break;
        case BUTTON_QUIT:
			quit = true;
            break;
    }

}

// Runs every loop game loop
static bool UpdateLoop( SDL_Event* e )
{
    // Call functions we want to run every loop
    HandleEvents( e );
    DrawGraphics();

	// Get mouse x and y
	SDL_GetMouseState(&mouseX, &mouseY);

	// Button hover functionality
	for (int i = 0; i < MAX_BUTTONS; i++) {
		// If mouse on button
		if (buttons[i]->inside(mouseX, mouseY)) {
			buttons[i]->hover = true;
		}
		else {
			buttons[i]->hover = false;
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
    //SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );
    SDL_SetRenderDrawColor( renderer, 0x00, 0x00, 0x00, 0x00 );
    SDL_RenderClear( renderer );

    // Draw backgrounds
	mainMenuBackground.render(0, 0);

    // Draw text
    //titleText.render(GetWindowWidth()/2, GetWindowHeight()/4, 0.5, 0.5);

    // Draw buttons
    for( int i = 0; i < MAX_BUTTONS; i++ )
    {
        if(buttons[i]->visible == true){
            buttons[i]->draw(renderer);
        }
    }


    //Update screen
    SDL_RenderPresent( renderer );

}

void InitMainMenu (){
    // Tell main to call this files main loop
    SetRoomLoop(UpdateLoop);

    // Open TTF font
    fontSnackerComic52 = TTF_OpenFont( "fonts/SnackerComic.ttf", 52 );

    // Define colors
    //white = {255, 255, 255};

    // Initilize perameters

    // Define Backgrounds
	mainMenuBackground.loadFromFile("graphics/TitleScreen.png");

    // Define misc images 

    // Initilize text textures
    titleText = Texture();
    titleText.loadText("This is a text", white, fontSnackerComic52);
   
   
    // Set up buttons
    buttons[BUTTON_START] = new Button(BUTTON_START, GetWindowWidth() / 2, 380, NULL, NULL, (char*)"graphics/BlankButton.png", (char*)"graphics/BlankButtonP.png", (char*)"graphics/BlankButton.png");
	buttons[BUTTON_START]->center();
	buttons[BUTTON_LOAD] = new Button(BUTTON_LOAD, GetWindowWidth() / 2, 500, NULL, NULL, (char*)"graphics/BlankButton.png", (char*)"graphics/BlankButtonP.png", (char*)"graphics/BlankButton.png");
	buttons[BUTTON_LOAD]->center();
	buttons[BUTTON_QUIT] = new Button(BUTTON_QUIT, GetWindowWidth() / 2, 620, NULL, NULL, (char*)"graphics/BlankButton.png", (char*)"graphics/BlankButtonP.png", (char*)"graphics/BlankButton.png");
	buttons[BUTTON_QUIT]->center();


	

    // Set up blend mode
}

void CloseMainMenu(){

}