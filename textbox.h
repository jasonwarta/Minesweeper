#ifndef TEXTBOX_H_INCLUDED
#define TEXTBOX_H_INCLUDED

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

#include <string>
#include <iostream>
#include <vector>

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::vector;

class Textbox
{
public:
	/*
	 * Textbox constructor
	 * Takes a SDL_Renderer, a TTF_Font, and a SDL_Window
	 * Creates a chatbox with a preset size in the lower left corner of the window
	 */
	Textbox(SDL_Renderer * renderer, TTF_Font * font, SDL_Window * window);

	/*
	 * Textbox destructor
	 * Does nothing atm
	 */
	~Textbox();

	/*
	 * Write function
	 * Takes a SDL_Renderer and a string to be written
	 * Adds the text to a vector
	 * Draws current vector contents to the screen within the confines of the textbox
	 */
	void write(string s);

	/*
	 * Draw function
	 * Takes a SDL_Renderer
	 * Redraws the textbox with existing text
	 */
	void draw();

	/*
	 * Add function
	 * Takes a string
	 * Tdds the string to the vector of text
	 * You will need to manually call the draw or write functions to update the screen
	 */
	void add(string s);


private:
	// * Assign area to draw text to
	void assignTextRects();

	int width_;
	int height_;
	static const int posX_ = 0;
	int posY_;

	SDL_Rect * boxDestRect_;
	vector<SDL_Rect> textSpots_;
	SDL_Texture * background_;
	TTF_Font * font_;

	SDL_Renderer * renderer_;

	int lines_;
	int fheight_;

	vector<string> input_;
};

#endif
