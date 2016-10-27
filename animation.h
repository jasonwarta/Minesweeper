#ifndef ANIMATION_H_INCLUDED
#define ANIMATION_H_INCLUDED

#ifdef _WIN32
    #include <SDL.h>
    #include <SDL_image.h>
    #include <SDL_ttf.h>
#elif __APPLE__
    #include <SDL2/SDL.h>
    #include <SDL2_image/SDL_image.h>
    #include <SDL2_ttf/SDL_ttf.h>
#endif

// #include "game.h"
#include "Map.h"
#include "Tile.h"
#include "textbox.h"
#include "button.h"

#include <cstdio>
#include <cmath>
#include <iostream>
#include <cmath>
#include <vector>

using std::cout;
using std::cin;
using std::endl;
using std::vector;
using std::string;

class Animation{
public:
	Animation();

	Animation(SDL_Renderer * renderer, SDL_Window * window, Map &map, Textbox &textbox, vector<Button> &buttons, string IMGpath, int frames, int tileSize, int timeDelay);

	~Animation();

	void up();
	void down();
	void left();
	void right();

	void draw();
	void drawAtMouse(SDL_Point point);

	void rotpt(SDL_Point point);
	SDL_Point rotpt();

	void pathParabola(int x, int y, Animation * pc);

	void posX(int x);
	int posX();

	void poxY(int y);
	int posY();

	int offsetX();
	int offsetY();

	int mapX();
	int mapY();

	void restart();

private:
	void loadSrcRects();

	double slope(int x, double &y, int dist);

	SDL_Rect * getTargetRect(int x, int y, int w, int h);

	vector<SDL_Rect> srcRect_;
	SDL_Texture * srcImg_;
	SDL_Renderer * renderer_;
	SDL_Point rotpt_;

	Map * map_;
	Textbox * textbox_;
	vector<Button> * buttons_;

	string imgPath_;

	int frames_;
	int timeDelay_;

	int win_w_;
	int win_h_;
	int tileSize_;
	int * bounds_;

	int charposX_;
	int charposY_;

	int charoffsetX_;
	int charoffsetY_;

	int frame_w_;
	int frame_h_;
	int mapX_; // * Character's position IN the minefield, x
	int mapY_; // * Character's position in the minefield, y

};

#endif
