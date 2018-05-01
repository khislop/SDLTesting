#ifndef BUTTON_H
#define BUTTON_H

#include "init.h"
#include "texture.h"

class Button{
public:
	//Atributes
	int id;
	int x;
	int y;
	int width;
	int height;
	Texture button_text;
	SDL_Texture* image_idle;
	SDL_Texture* image_idle_pressed;
	SDL_Texture* image_idle_hover;

	//State flags
	bool typematic;
	bool pressed;
	bool active;
	bool visible;
	bool hover;
	bool centered;
	
	Button();

	Button(int idin, int xin, int yin, int w = NULL, int h = NULL, char* ii = NULL, char* iip = NULL, char* iih = NULL);

	void setText(std::string text, SDL_Color color, TTF_Font* font);

	void setTypematic();

	virtual void draw(SDL_Renderer* renderer);

	void center();

	bool inside(int xin, int yin);

	void enable();

	void disable();

	void clear();
};


class LatchingButton: public Button{
public:
	SDL_Texture * image_idle_selected;
	SDL_Texture* image_idle_pressed_selected;
	bool selected;

	LatchingButton(int idin, int xin, int yin, int w, int h, char* ii = NULL, char* iip = NULL, char* iis = NULL, char* iips = NULL);

	void draw(SDL_Renderer* renderer);
};

//
//class TextButton : public Button {
//public:
//	std::string buttonText;
//
//	TextButton(int idin, int xin, int yin, int w, int h, char* ii = NULL, char* iip = NULL, char* iis = NULL, char* iips = NULL);
//
//};

#endif