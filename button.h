#ifndef BUTTON_H_INCLUDED
#define BUTTON_H_INCLUDED

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

// #include "Functions.h"
#include "slider.h"

#include <string>
#include <vector>
#include <iostream>

using std::vector;
using std::string;
using std::cout;
using std::endl;

class Button{
public:
	Button();

	Button(SDL_Renderer * renderer, SDL_Window * window, TTF_Font * font);

	Button(SDL_Renderer * renderer, SDL_Window * window, TTF_Font * font, int x, int y, int w, int h);

	Button(const Button &other);

	void operator=(const Button &other);

	void getTargetRects();

	void draw(string text);

	void draw();

	SDL_Rect * rect();

	int showScoresheet(SDL_Event &e, vector<int> &scores);

	void setTextColor(Uint8 r, Uint8 g, Uint8 b);

	bool SDL_PointInRect(const SDL_Point *p, const SDL_Rect *r);

	void position(int x, int y, int w, int h);

	SDL_Point position();

	void animateRect(int final_X, int final_Y, int final_W, int final_H);

	/**
	 * @brief animates a rectangle
	 * @details draws portions of the texture to the screen for an animated revealing effect
	 * 
	 * @param texture SDL_Texture * , to the texture to be shown
	 * @param final_X final X position of the texture
	 * @param final_Y final Y position of the texture
	 * @param final_W final width of the texture
	 * @param final_H final height of the texture
	 */
	void animateRect(SDL_Texture * texture, int final_X, int final_Y, int final_W, int final_H);

	/**
	 * @brief Shows the main menu
	 * @details uses passed texture as background, sets up main menu with 3 buttons and volume sliders
	 * 
	 * @param e SDL_Event object, by reference
	 * @param background SDL_Texture * 
	 * @param musicVol custom Slider object, by reference
	 * @param effectsVol custom Slider object, by reference
	 * @param scores vector<ints> with the scores, ideally loaded from a file
	 * @return 0 to quit program, 1 to reset map, -1 otherwise
	 */
	int mainMenu(SDL_Event &e, SDL_Texture * background, Slider &musicVol, Slider &effectsVol, vector<int> &scores);

	/**
	 * @brief Shows the pause menu
	 * @details uses the animatRect function to set up a filled rectangle, and populates it with 3 buttons and volume sliders
	 * 
	 * @param e SDL_Event, by reference
	 * @param musicVol custom Slider object
	 * @param effectsVol custom Slider object
	 * @return 0 to quit program, 1 to reset map, 3 to open main menu, -1 otherwise
	 */
	int pauseMenu(SDL_Event &e, Slider &musicVol, Slider &effectsVol);

	void setScoreVec(vector<int> &vec);
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

	SDL_Renderer * textureRenderer_;
	SDL_Renderer * renderer_;
	SDL_Window * window_;

	SDL_Rect * border_;
	SDL_Rect * fill_;
	SDL_Rect * textPos_;

	SDL_Texture * txtTexture_;
	SDL_Texture * button_;
	SDL_Texture * background_;

	TTF_Font * font_;

	SDL_Color textColor_;

	vector<int> * scores_;
};


#endif


