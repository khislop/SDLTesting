#ifndef TEXTURE_H
#define TEXTURE_H

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <string>

#define TOP_LEFT 0
#define MIDDLE_CENTER 1
#define MIDDLE_LEFT 2
#define MIDDLE_RIGHT 3

class Texture
{
    public:
        //Initializes variables
        Texture();

        //Deallocates memory
        ~Texture();

        //Loads image at specified path
        bool loadFromFile( std::string path );

        //Creates image from font string
        bool loadText( std::string textureText, SDL_Color textColor, TTF_Font* gFont );

        //Deallocates texture
        void free();

        //Set color modulation
        void setColor( Uint8 red, Uint8 green, Uint8 blue );

        //Set blending
        void setBlendMode( SDL_BlendMode blending );

        //Set alpha modulation
        void setAlpha( Uint8 alpha );
        
        //Renders texture at given point
        virtual void render( int x, int y, double xAnchor = 0, double yAnchor = 0, SDL_Rect* clip = NULL );
        virtual void render( int x, int y, double angle, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE );

		bool textureLoaded();

        //Gets image dimensions
        int getWidth();
        int getHeight();

        //Pixel manipulators
        bool lockTexture();
        bool unlockTexture();
        void* getPixels();
        int getPitch();

        //The actual hardware texture
        SDL_Texture* mTexture;
        void* mPixels;
        int mPitch;

        //Image dimensions
        int mWidth;
        int mHeight;
};


class StaticTexture : public Texture {
public:

    StaticTexture();
	StaticTexture(std::string imageFile,  int x, double scaleIn = 1, int yOffset = 0);

    void render();

private:
	int xPos;
	int yOff;
	int scale;
};

#endif