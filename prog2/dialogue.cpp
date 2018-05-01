//Using SDL, SDL_image, standard IO, math, and strings
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include <sstream>
#include <iostream>
#include <cmath>
#include <vector>
#include "init.h"
#include "button.h"
#include "texture.h"
#include "dialogue.h"
#include "time.h"

// Dialogue visual peramiters
#define CHARACTER_SCROLL_SPEED	20
#define DIALOGUE_FONT_SIZE		38
#define DIALOGUE_START_X		45
#define DIALOGUE_START_Y		475
#define DIALOGUE_MAX_WIDTH		1200
#define ROW_SPACE_BUFFER		15
#define SPEAKER_START_X			45
#define SPEAKER_START_Y			405



// Using statments to reduce excess syntax
using std::to_string;

// Define button IDs
enum ButtonStates {
	MAX_BUTTONS
};

// Define backgrounds

// Define quit flag
static bool dialogueExit = false;
// Define timers
long characterTimer;

// Define backgrounds
static Texture* dialogueBackground = new Texture();
static Texture dialogueBox = Texture();

// Define misc images

// Define text textures
static Texture titleText = Texture();
static Texture speakerText = Texture();
static std::vector<Texture*> dialogueText;

// Define fonts
static TTF_Font* fontSnackerComic52;
static TTF_Font* fontDialogue;

// Define colors
static SDL_Color white = { 255, 255, 255 };
static SDL_Color black = { 255, 255, 255 };

// Define sprite textures
static StaticTexture spriteOne = StaticTexture();

// Define button structure
//static Button* buttons[MAX_BUTTONS];

// Define internal variables
static int mouseX, mouseY;
static int dialogueCursor;
static int currentLine;
static int characterScrollSpeed = CHARACTER_SCROLL_SPEED;
static int dialogueFontSize = DIALOGUE_FONT_SIZE;
static std::string dialogueString;
static std::string dialogueFrame;
static std::string speaker;
static std::stringstream dialogueStream;


bool HandleDialogueEvents(SDL_Event* e) {
	int x, y;

	//Handle events on queue
	while (SDL_PollEvent(e) != 0)
	{
		//User requests quit
		if (e->type == SDL_QUIT)
		{
			QuitGame();
		}

		//Right click down
		if (e->type == SDL_MOUSEBUTTONDOWN && e->button.button == SDL_BUTTON_RIGHT) {
			// Do stuff
		}

		//Click down
		if ((e->type == SDL_FINGERDOWN || e->type == SDL_MOUSEBUTTONDOWN) && e->button.button == SDL_BUTTON_LEFT) {
			//Get mouse x and y
			x = e->button.x;
			y = e->button.y;


			// Stream in the next line of dialogue, if there is no more, exit.7
			if (dialogueCursor >= dialogueFrame.size()) {
				UpdateLine();
			}
			else {
				// Proccess cahracters till the entrie line is finished
				while (dialogueCursor < (dialogueFrame.size() + 1)) {UpdateCursor();
				}
			}
		}

		//Release click
		if (e->type == SDL_FINGERUP || e->type == SDL_MOUSEBUTTONUP) {
			x = e->button.x;
			y = e->button.y;


		}

		// Movement

	}

	return dialogueExit;

}

// Runs every loop game loop
bool UpdateDialogue(SDL_Event* e)
{
	// Call functions we want to run every loop
	HandleDialogueEvents(e);
	DrawDialogue();


	// Update dialogue cursor
	if (IsTimerUp(characterTimer, CHARACTER_SCROLL_SPEED) && dialogueCursor < (dialogueFrame.size() + 1) && !dialogueExit) {
		UpdateCursor();
	}

	// Get mouse x and y
	SDL_GetMouseState(&mouseX, &mouseY);




	return dialogueExit;
}

void UpdateLine() {
	int dStart = 0;
	if (!std::getline(dialogueStream, dialogueFrame, '\n')) {
		dialogueExit = true;
	}
	// Reset cursor
	dialogueCursor = 0;
	// Cut off newline and retern char if there is one
	if (dialogueFrame.find('\n') != std::string::npos) {
		dialogueFrame.erase(dialogueFrame.find('\n'), 1);
	}
	if (dialogueFrame.find('\r') != std::string::npos) {
		dialogueFrame.erase(dialogueFrame.find('\r'), 1);
		// WHY DOES THIS PRINT STATMENT BREAK EVERYTHING?
		//printf("FOUND RETURN: `%s`\n", dialogueFrame);
	}

	// Clear speaker
	speaker = "";

	// If there is a speaker, save their name
	dStart = dialogueFrame.find(':');
	if (dStart >= 0) {
		// Set speaker
		speaker = dialogueFrame.substr(0, dStart);
		// Remove speaker and ':' character from frame
		dialogueFrame = dialogueFrame.substr(dStart + 1);
		// Remove any tab or spaces at the front of the string
		while (dialogueFrame[0] == ' ' || dialogueFrame[0] == '\t') {
			dialogueFrame = dialogueFrame.substr(1);
		}
	}


	// If there is a speaker load texture
	if (speaker.size() > 0) {
		speakerText.loadText(speaker, white, fontDialogue);
	}

	// Redraw texture
	dialogueText[currentLine]->loadText(dialogueFrame.substr(0, dialogueCursor + 1), white, fontDialogue);
}

void UpdateCursor() {
	// If the next word will be too long to fit the box, move to next line
	if (dialogueFrame[dialogueCursor - 1] == ' ' && !NextWordHasRoom(dialogueFrame, dialogueCursor, DIALOGUE_MAX_WIDTH, fontDialogue)) {
		currentLine++;
		dialogueText.push_back(new Texture());
		dialogueFrame = dialogueFrame.substr(dialogueCursor);
		dialogueCursor = 0;
	}
	dialogueText[currentLine]->loadText(dialogueFrame.substr(0, dialogueCursor + 1), white, fontDialogue);
	characterTimer = GetTimer();
	dialogueCursor++;
}

void DrawDialogue()
{
	SDL_Renderer *renderer = getRenderer();

	//Clear screen

	// Draw backgrounds
	if (dialogueBackground != NULL) {
		dialogueBackground->render(0, 0);
	}

	// Draw dialogue box
	dialogueBox.render(0, 0);

	// Draw speaker if it is set
	if (speakerText.textureLoaded()) {
		speakerText.render(SPEAKER_START_X, SPEAKER_START_Y);
	}

	// Draw text
	titleText.render(GetWindowWidth()/2, GetWindowHeight()/4, 0.5, 0.5);
	for (int i = 0; i < dialogueText.size(); i++) {
		dialogueText[i]->render(DIALOGUE_START_X, DIALOGUE_START_Y + (dialogueText[i]->getHeight() * i) + ROW_SPACE_BUFFER);
	}

	spriteOne.render();

	//Update screen
	SDL_RenderPresent(renderer);

}

bool DialogueLoaded() {
	return !(dialogueString.empty());
}

bool NextWordHasRoom(std::string textString, int pos, int maxWidth, TTF_Font* font) {
	Texture sizer = Texture();
	// Find position of next space
	int spacePos = textString.substr(pos).find(' ');
	// Generate texture
	sizer.loadText(textString.substr(0, spacePos + pos), {0, 0, 0}, font);
	
	if (sizer.getWidth() > maxWidth) {
		return false;
	}
	else {
		return true;
	}



}

void LoadDialogue(std::string fileName) {

	//Loading success flag
	bool success = true;
	char buff;

	// Clear previous dialogue
	dialogueString = "";
	dialogueText.clear();
	dialogueText.push_back(new Texture());
	currentLine = 0;

	//Open file for reading in binary
	SDL_RWops* file = SDL_RWFromFile(fileName.c_str(), "r");

	//File does not exist
	if (file == NULL)
	{
		printf("Error: Unable to open file! SDL Error: %s\n", SDL_GetError());
		success = false;
	}
	//File exists
	else
	{
		//Load data
		printf("Reading file...!\n");
		while (SDL_RWread(file, &buff, sizeof(char), 1)) {
			dialogueString += buff;
		}

		//Close file handler
		SDL_RWclose(file);
	}

		// Set up string stream
		dialogueStream.str(dialogueString);

		// Set up the first line
		UpdateLine();

	// Setup character timer
	characterTimer = GetTimer();

}

void LoadSprite() {
	// Test
}

void InitDialogue() {

	// Open TTF font
	fontSnackerComic52 = TTF_OpenFont("fonts/SnackerComic.ttf", 52);
	fontDialogue = TTF_OpenFont("fonts/Chapaza.ttf", dialogueFontSize);

	// Initilize perameters

	// Define Backgrounds
	dialogueBackground = NULL;
	dialogueBox.loadFromFile("graphics/DialogueBox.png");

	// Define misc images 

	// Initilize text textures
	titleText.loadText("This ins a text", white, fontSnackerComic52);

	spriteOne = StaticTexture("graphics/MaleSprite.png", 0, 1);

}

void CloseDialogue() {

}