#ifndef FUNCTIONS_H_INCLUDED
#define FUNCTIONS_H_INCLUDED

#ifdef _WIN32
    #include <SDL.h>
    #include <SDL_image.h>
    #include <SDL_ttf.h>
	#include <SDL_mixer.h>
#elif __APPLE__
    #include <SDL2/SDL.h>
    #include <SDL2_image/SDL_image.h>
    #include <SDL2_ttf/SDL_ttf.h>
	#include <SDL2_mixer/SDL_mixer.h>
#endif

// #include "game.h"
// #include "Map.h"
// #include "Tile.h"
// #include "textbox.h"
// #include "animation.h"
// #include "button.h"

#include <ostream>
#include <iostream>
#include <fstream>
#include <sstream>
#include <istream>

#include <cstdio>
#include <vector>
#include <cmath>

using std::ostream;
using std::cout;
using std::endl;
using std::vector;
using std::string;
using std::fstream;
using std::ios;
using std::ifstream;
using std::ofstream;
using std::stringstream;

SDL_Window * createWindow(const int, const int);
void loadImages(vector<SDL_Rect>&,int Size,SDL_Renderer *);
void displayText(SDL_Renderer *,TTF_Font *, int, int, int, int, SDL_Color, string *);
void loadScanningRects(vector<SDL_Rect> &vec);
void loadWalkingRects(vector<SDL_Rect> &vec);
SDL_Rect * getTargetRect(SDL_Rect * rect,int posX, int posY);
SDL_Rect* getTargetRect(int x, int y, int w, int h);
void init();
void loadSrcRects(vector<SDL_Rect> &vec, SDL_Texture *img, int frames);

void loadPrevScores(vector<int> &scores);
void saveScores(vector<int> &scores);

template<typename T>
void quicksort(vector<T> & vec, int bot, int top);

// * Stolen from SDL 2.0.4 library
bool SDL_PointInRect(const SDL_Point *p, const SDL_Rect *r);

template<typename F>
string toString(F var){
    stringstream ss;
    ss << var;
    return ss.str();
}


#endif
