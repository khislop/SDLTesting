
//Using SDL, SDL_image, standard IO, math, and strings
#include <SDL.h>
#include <SDL_image.h>
#include <string>
	
#include "init.h"
#include "button.h"
#include "texture.h"

Button::Button(){
		
}


Button::Button(int idin, int xin, int yin, int w, int h, char* ii, char* iip, char* iih){
	id = idin;
	x = xin;
	y = yin;
	width = w;
	height = h;
	pressed = false;
	active = true;
	visible = true;
	typematic = false;
	hover = false;
	centered = false;

	// Initilize text texture
	button_text = Texture();

	// Idle Image
	if(ii == NULL){
		image_idle = NULL;
	}else{
		image_idle = loadTexture(ii);
		if(width == NULL) {
			SDL_QueryTexture(image_idle, NULL, NULL, &width, NULL);
		}
		if (height == NULL) {
			SDL_QueryTexture(image_idle, NULL, NULL, NULL, &height);
		}
	}
	// Pressed image
	if(iip == NULL){
		image_idle_pressed = NULL;
	}else{
		image_idle_pressed = loadTexture(iip);
	}
	// Hover image
	if (iih == NULL) {
		image_idle_hover = NULL;
	}
	else {
		image_idle_hover = loadTexture(iih);
	}


}

void Button::setText(std::string text, SDL_Color color, TTF_Font* font){
	button_text.loadText(text, color, font);
}

void Button::setTypematic(){
	typematic = true;
}

void Button::draw(SDL_Renderer* renderer){
	SDL_Texture* i;
	int drawx = x;
	int drawy = y;
	if(centered){
		drawx -= width / 2;
		drawy -= height / 2;
	}
	//Pressed
	if(pressed){
		i = image_idle_pressed;
	}else{
		// Hovered
		if (hover) {
			i = image_idle_hover;
		}
		// Idle
		else {
			i = image_idle;
		}
	}
    SDL_Rect rect = {drawx, drawy, width, height};
    SDL_RenderCopy(renderer, i, NULL, &rect);
    button_text.render(x+width/2, y+height/2, 0.5, 0.5);
}

void Button::center() {
	centered = true;
}

bool Button::inside(int xin, int yin){
	int drawx = x;
	int drawy = y;
	if (centered) {
		drawx -= width / 2;
		drawy -= height / 2;
	}
	if(xin > drawx && xin < drawx+width && yin > drawy && yin < drawy+height){
		return true;
	}else{
		return false;
	}
}

void Button::enable(){
	visible = true;
	active = true;
}

void Button::disable(){
	active = false;
	visible = true;
}

void Button::clear(){
	active = false;
	visible = false;
}

LatchingButton::LatchingButton(int idin, int xin, int yin, int w, int h, char* ii, char* iip, char* iis, char* iips) : Button(idin, xin, yin, w, h, ii, iip) {

	selected = false;

	image_idle_selected = loadTexture(iis);
	image_idle_pressed_selected = loadTexture(iips);


}

void LatchingButton::draw(SDL_Renderer* renderer){
	SDL_Texture* i;
	if(selected){
		if(pressed){
			i = image_idle_pressed_selected;
		}else{
			i = image_idle_selected;
		}
	}else{
		if(pressed){
			i = image_idle_pressed;
		}else{
			i = image_idle;
		}
	}	
    SDL_Rect rect = {x, y, width, height};
    SDL_RenderCopy(renderer, i, NULL, &rect);
}

//
//TextButton::TextButton(int idin, int xin, int yin, std::string bT) {
//
//	buttonText = bT;
//	id = idin;
//	x = xin;
//	y = yin;
//
//
//
//
//}
