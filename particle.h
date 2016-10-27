#ifndef PARTICLE_H_INCLUDED
#define PARTICLE_H_INCLUDED

#ifdef _WIN32
    #include <SDL.h>
    #include <SDL_image.h>
    #include <SDL_ttf.h>
#elif __APPLE__
    #include <SDL2/SDL.h>
    #include <SDL2_image/SDL_image.h>
    #include <SDL2_ttf/SDL_ttf.h>
#endif

#include "Map.h"
#include <stdio.h>
#include <ostream>
#include <iostream>
#include <vector>
#include <cmath>
#include "animation.h"
#include "particle.h"
using std::ostream;
using std::cout;
using std::endl;
using std::vector;
using std::string;


class SolidText{
public:

    SolidText();
	SolidText(SDL_Renderer * renderer, SDL_Window * window, TTF_Font * font, int x, int y, int w, int h,SDL_Color c);
    void draw(string text);
private:
	int posX_;
	int posY_;
	int width_;
	int height_;

	int textWidth_;
	int textHeight_;

	int win_w_;
	int win_h_;

	string text_;
    int fheight_;
	SDL_Renderer * textureRenderer_;
	SDL_Renderer * renderer_;
	SDL_Window * window_;

	SDL_Rect * border_;
	SDL_Rect * fill_;
	SDL_Rect * textPos_;

	SDL_Texture * txtTexture_;
	SDL_Texture * button_;

	TTF_Font * font_;

	SDL_Color textColor_;



};
class Particle
{
public:
    Particle();
    void setPosX(double);
    void setPosY(double);
    void setVelX(double);
    void setVelY(double);
    void setAngle(int);
    double getPosX();
    double getPosY();
    double getVelX();
    double getVelY();
    int getFloor();
    void setFloor(int);
    int getAngle();
    void setFrame(int);
    int getFrame();
private:
    double posX_;
	double posY_;
	double velX_;
	double velY_;
	SDL_Texture * srcImg_;
	SDL_Renderer * renderer_;

    int angle_;
    int floor_;
    int frame_;

};

class ParticleEngine
{
public:

    ParticleEngine();
    void start(SDL_Renderer * renderer,int s,int,int,string,int,int,int);
    void splat(SDL_Renderer * renderer,int s,int,int,string,int,int,int,SDL_Window *);
    void draw();
    void update();
private:

    SDL_Renderer * renderer_;
    int size_;
    Particle *splatter_;
    string IMGpath_;
    vector<SDL_Rect> srcRect_;
    int frame_w_;
    int frame_h_;
    int sizeX_;
    int sizeY_;
    int win_w_;
    int win_h_;
    double accX_;
    double accY_;

};

#endif
