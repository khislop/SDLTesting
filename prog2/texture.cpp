#include "texture.h"
#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include "init.h"

Texture::Texture()
{
    //Initialize
    mTexture = NULL;
    mWidth = 0;
    mHeight = 0;
    mPixels = NULL;
    mPitch = 0;
}

Texture::~Texture()
{
    //Deallocate
    free();
}

bool Texture::loadFromFile( std::string path )
{
    //Get rid of preexisting texture
    free();

    //The final texture
    SDL_Texture* newTexture = NULL;

    //Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
    if( loadedSurface == NULL )
    {
        printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
    }
    else
    {
        //Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface( getRenderer(), loadedSurface );
        if( newTexture == NULL )
        {
            printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
        }
        else
        {
            //Get image dimensions
            mWidth = loadedSurface->w;
            mHeight = loadedSurface->h;
        }

        //Get rid of old loaded surface
        SDL_FreeSurface( loadedSurface );
 
    }

    //Return success
    mTexture = newTexture;
    return mTexture != NULL;
}

bool Texture::loadText( std::string textureText, SDL_Color textColor, TTF_Font* gFont)
{
    //Get rid of preexisting texture
    free();
    //printf("Loading: %s\n", textureText.c_str());

    //Render text surface
    SDL_Surface* textSurface = TTF_RenderText_Blended( gFont, textureText.c_str(), textColor ); 
    if( textSurface == NULL )
    {
        printf( "Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError() );
    }
    else
    {
        //Create texture from surface pixels
        mTexture = SDL_CreateTextureFromSurface( getRenderer(), textSurface );
        if( mTexture == NULL )
        {
            printf( "Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError() );
        }
        else
        {
            //Get image dimensions
            mWidth = textSurface->w;
            mHeight = textSurface->h;
        }

        //Get rid of old surface
        SDL_FreeSurface( textSurface );
    }

    //Return success
    return mTexture != NULL;
}

void Texture::free()
{
    //Free texture if it exists
    if( mTexture != NULL )
    {
        SDL_DestroyTexture( mTexture );
        mTexture = NULL;
        mWidth = 0;
        mHeight = 0;
        mPixels = NULL;
        mPitch = 0;
    }
}

void Texture::setColor( Uint8 red, Uint8 green, Uint8 blue )
{
    //Modulate texture rgb
    SDL_SetTextureColorMod( mTexture, red, green, blue );
}

void Texture::setBlendMode( SDL_BlendMode blending )
{
    //Set blending function
    SDL_SetTextureBlendMode( mTexture, blending );
}

void Texture::setAlpha( Uint8 alpha )
{
    //Modulate texture alpha
    SDL_SetTextureAlphaMod( mTexture, alpha );
}

void Texture::render( int x, int y, double xAnchor, double yAnchor, SDL_Rect* clip )
{
    SDL_Rect renderQuad;
    //Set rendering space and render to screen
    renderQuad = { (int)(x - mWidth*xAnchor), (int)(y - mHeight*yAnchor), mWidth, mHeight };

    //Set clip rendering dimensions
    if( clip != NULL )
    {
        renderQuad.w = clip->w;
        renderQuad.h = clip->h;
    }

    //Render to screen
    SDL_RenderCopy( getRenderer(), mTexture, clip, &renderQuad );

}

void Texture::render( int x, int y, double angle, SDL_Point* center, SDL_RendererFlip flip )
{
    //Set rendering space and render to screen
    SDL_Rect renderQuad = { x, y, mWidth, mHeight };

    //Render to screen
    SDL_RenderCopyEx( getRenderer(), mTexture, NULL, &renderQuad, angle, center, flip );
}

bool Texture::textureLoaded() {
	if (mTexture != NULL) {
		return true;
	}
	else {
		return false;
	}
}

int Texture::getWidth()
{
    return mWidth;
}

int Texture::getHeight()
{
    return mHeight;
}

bool Texture::lockTexture()
{
    bool success = true;

    //Texture is already locked
    if( mPixels != NULL )
    {
        printf( "Texture is already locked!\n" );
        success = false;
    }
    //Lock texture
    else
    {
        if( SDL_LockTexture( mTexture, NULL, &mPixels, &mPitch ) != 0 )
        {
            printf( "Unable to lock texture! %s\n", SDL_GetError() );
            success = false;
        }
    }

    return success;
}

bool Texture::unlockTexture()
{
    bool success = true;

    //Texture is not locked
    if( mPixels == NULL )
    {
        printf( "Texture is not locked!\n" );
        success = false;
    }
    //Unlock texture
    else
    {
        SDL_UnlockTexture( mTexture );
        mPixels = NULL;
        mPitch = 0;
    }

    return success;
}

void* Texture::getPixels()
{
    return mPixels;
}

int Texture::getPitch()
{
    return mPitch;
}

StaticTexture::StaticTexture()
{
    //Initialize
    mTexture = NULL;
    mWidth = 0;
    mHeight = 0;
    mPixels = NULL;
    mPitch = 0;
    scale = 0;
    xPos = 0;
    yOff = 0;

}

StaticTexture::StaticTexture(std::string imageFile, int x, double scaleIn, int yOffset)
{
	//Initialize
	scale = scaleIn;
	xPos = x;
	yOff = yOffset;

	// Load texture
	loadFromFile(imageFile);
}

void StaticTexture::render()
{
    SDL_Rect renderQuad;
    //Set rendering space and render to screen
    //renderQuad = { (int)(xPos*GetWindowWidth() - mWidth*0.5), (int)(GetWindowHeight() - mHeight), mWidth*scale, mHeight*scale };
    renderQuad = { 0, 0, mWidth, mHeight };

    //Render to screen
    SDL_RenderCopy( getRenderer(), mTexture, NULL, &renderQuad );

}
