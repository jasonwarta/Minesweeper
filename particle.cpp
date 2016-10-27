#ifdef _WIN32
    #include <SDL.h>
    #include <SDL_image.h>
    #include <SDL_ttf.h>
#elif __APPLE__
    #include <SDL2/SDL.h>
    #include <SDL2_image/SDL_image.h>
    #include <SDL2_ttf/SDL_ttf.h>
#endif

#include "Functions.h"
#include "Map.h"
#include "Tile.h"
#include "animation.h"
#include "particle.h"
#include <stdio.h>
#include <math.h>
#include <vector>
#include<cstring>

using std::cout;
using std::cin;
using std::endl;
using std::vector;
using std::string;






SolidText::SolidText(){
	text_ = "";
	posX_ = 0;
	posY_ = 0;
	width_ = 0;
	height_ = 0;
}

SolidText::SolidText(SDL_Renderer * renderer, SDL_Window * window, TTF_Font * font, int x, int y, int w, int h,SDL_Color c)
{
	renderer_ = renderer;
	textureRenderer_ = SDL_CreateRenderer(window,-1,SDL_RENDERER_TARGETTEXTURE);
	SDL_GetWindowSize(window, &win_w_, &win_h_);
	window_ = window;
	posX_ = x;
	posY_ = y;
	width_ = w;
	height_ = h;
	font_ = font;
    fheight_ = TTF_FontHeight(font_)+2;

	textColor_ = c;
	txtTexture_ = SDL_CreateTextureFromSurface(renderer_,TTF_RenderText_Solid(font_,text_.c_str(),textColor_));

	int width;
	int height;
	SDL_QueryTexture(txtTexture_,NULL,NULL,&width,&height);

	textWidth_ = width;
	textHeight_ = TTF_FontHeight(font_)+1;
}

void SolidText::draw(string text)
{

        int winW;
        int winH;
        SDL_GetWindowSize(window_,&winW,&winH);
        int w, h;
        SDL_Texture * temp = SDL_CreateTextureFromSurface(renderer_,TTF_RenderText_Solid(font_,text.c_str(),textColor_));
		SDL_QueryTexture(temp,NULL,NULL,&w,&h);
		SDL_Rect tempSpot_;
        tempSpot_.x = (winW - text.size()*fheight_*1.5)/2;
		tempSpot_.y = winH/2;
		tempSpot_.w = text.size()*fheight_*1.5;
		tempSpot_.h = fheight_*4;
		SDL_RenderCopy(renderer_,temp,NULL,&tempSpot_);
}


ParticleEngine::ParticleEngine()
{
}


void ParticleEngine::start(SDL_Renderer * renderer,int s,int x, int y,string IMGpath,int frames,int sizeX,int sizeY)
{
    renderer_ = renderer;
    size_ = s;
    IMGpath_ =  IMGpath;
    srcRect_ = vector<SDL_Rect>(frames);
    SDL_Texture * tempImg = SDL_CreateTextureFromSurface(renderer,IMG_Load(IMGpath.c_str()));

    sizeX_ = sizeX;
    sizeY_= sizeY;

    if(SDL_QueryTexture(tempImg,NULL,NULL,&frame_w_,&frame_h_) != 0)
    {
        cout << "Error getting width and height in Animation constructor" << endl;
    }
    accX_ = 0;
    accY_ = 0.2;
    frame_w_ /=frames;
    for(int i = 0; i < frames; ++i)
    {
        srcRect_[i].x = frame_w_ * i;
        srcRect_[i].y = 0;
        srcRect_[i].w = frame_w_;
        srcRect_[i].h = frame_h_;
    }
	splatter_ = new Particle[size_];
    double randX;
    double randY;
    double randF;
    double randPX;
    double randPY;
    double randXM;
    double randA;
	for(int i = 0; i < size_; ++i)
    {
        splatter_[i].setFrame(rand() % frames);
        randX = (rand() % 200)-100;
        randXM = (rand() % 2);

        randY = (rand() % 50 )-80;
        randY /=10;
        randX /=10;
        randF = (rand() % 1000 )-500;
        randPX = (rand() % 50 )-25;
        randPX /=10;
        randPY = (rand() % 50 )-25;
        randPY /=10;
        randA = (rand() % 100 );

        splatter_[i].setPosX(x+randPX);
        splatter_[i].setPosY(y+randPY);
        splatter_[i].setVelX(randX);
        splatter_[i].setVelY(randY);
        splatter_[i].setAngle(randA);
        splatter_[i].setFloor(splatter_[i].getPosY()+100+randF);
	}
}

void ParticleEngine::splat(SDL_Renderer * renderer,int s,int x, int y,string IMGpath,int frames,int sizeX,int sizeY,SDL_Window * window)
{
    SDL_GetWindowSize(window, &win_w_, &win_h_);
    renderer_ = renderer;
    size_ = s;
    IMGpath_ =  IMGpath;
    srcRect_ = vector<SDL_Rect>(frames);
    SDL_Texture * tempImg = SDL_CreateTextureFromSurface(renderer,IMG_Load(IMGpath.c_str()));

    sizeX_ = sizeX;
    sizeY_= sizeY;
    if(SDL_QueryTexture(tempImg,NULL,NULL,&frame_w_,&frame_h_) != 0)
    {
        cout << "Error getting width and height in Animation constructor" << endl;
    }
    accX_ = 0;
    accY_ = 0;
    frame_w_ /=frames;
    for(int i = 0; i < frames; ++i)
    {
        srcRect_[i].x = frame_w_ * i;
        srcRect_[i].y = 0;
        srcRect_[i].w = frame_w_;
        srcRect_[i].h = frame_h_;
    }
	splatter_ = new Particle[size_];

    double randPX;
    double randPY;
    double randA;

	for(int i = 0; i < size_; ++i)
    {
        splatter_[i].setFrame(rand() % frames);

        randPX = (rand() % win_w_ );
        randPY = (rand() % win_h_ );

        randA = (rand() % 100 );

        splatter_[i].setPosX(randPX);
        splatter_[i].setPosY(randPY);
        splatter_[i].setVelX(0);
        splatter_[i].setVelY(0.4);
        splatter_[i].setAngle(randA);
        splatter_[i].setFloor(win_h_+400);
	}
}


void ParticleEngine::draw()
{

    SDL_Texture * tempImg = SDL_CreateTextureFromSurface(renderer_,IMG_Load(IMGpath_.c_str()));
    SDL_Point rotpt_ = {32,32};
    for(int i = 0; i < size_; ++i)
    {
        SDL_RenderCopyEx(renderer_,tempImg,&srcRect_[splatter_[i].getFrame()], getTargetRect(splatter_[i].getPosX(),splatter_[i].getPosY(),sizeX_,sizeY_),(splatter_[i].getAngle()), &rotpt_, SDL_FLIP_NONE);
    }
}

void ParticleEngine::update()
{

    for(int i = 0; i < size_; ++i)
    {
        if (splatter_[i].getPosY()< splatter_[i].getFloor() || (splatter_[i].getVelY()<0))
        {
            splatter_[i].setPosX(splatter_[i].getPosX()+splatter_[i].getVelX());
            splatter_[i].setVelY(splatter_[i].getVelY()+accY_);
            splatter_[i].setVelY(splatter_[i].getVelY()+accX_);
            splatter_[i].setPosY(splatter_[i].getPosY()+splatter_[i].getVelY());
        }
    }
}

Particle::Particle()
{
    posX_ = 0;
    posY_ = 0;
	velX_ = 0;
	velY_ = 0;

}

void Particle::setFrame(int x)
{
    frame_ = x;

}

void Particle::setAngle(int x)
{
    angle_ = x;

}
void Particle::setPosX(double x)
{
    posX_ = x;
}

void Particle::setPosY(double x)
{
 posY_ = x;
}
void Particle::setVelX(double x)
{
    velX_ = x;
}

void Particle::setVelY(double x)
{
    velY_ = x;
}



double Particle::getPosX()
{
    return posX_;
}


double Particle::getPosY()
{
    return posY_;
}

double Particle::getVelX()
{
    return velX_;
}

double Particle::getVelY()
{
    return velY_;
}

int Particle::getFloor()
{
    return floor_;
}

int Particle::getAngle()
{
    return angle_;
}

void Particle::setFloor(int x)
{
 floor_ = x;
}

int Particle::getFrame()
{
    return frame_;
}


