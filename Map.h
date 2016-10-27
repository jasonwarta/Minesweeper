#ifndef MAP_H_INCLUDED
#define MAP_H_INCLUDED

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
#include "Tile.h"

#include <iostream>
#include <ostream>
#include <cstdlib>
#include <ctime>
#include <sstream>
#include <vector>

using std::ostream;
using std::cout;
using std::endl;
using std::rand;
using std::stringstream;
using std::vector;

class Map{
public:
	/*
	 * Default Map constructor
	 */
	Map();

	/*
	 * Map constructor, use this in most cases
	 * Pass dimensions as size of minefield
	 * Constructor adds 2 to each dimension to account for borders
	 *
	 * Constructor takes ints for width, height, maxMines
	 * Creates an array of dimensions w+2,h+2, and seeds it with the number of mines
	 */
	Map(SDL_Renderer * renderer, int w, int h, int mines);

	/*
	 * Map copy constructor
	 */
	Map(Map &other);

	/*
	 * Map destructor
	 * sets all values to 0 and deletes arrays
	 */
	~Map();

	/*
	 * Width function
	 * Returns the width of the map
	 */

  void mapInit(); //Initiallizes the map on creation and reset.

	int width();

	/*
	 * Height function
	 * Returns the height of the map
	 */
	 int height();

	/*
	 * AddScore
	 * Adds passed int to score
	 */
	void addScore(int score);

	/*
	 * SubScore
	 * Subtracts passed int from score
	 */
	void subScore(int score);

	/*
	 * SetScore
	 * Sets score to passed int
	 */
	void setScore(int score);

	/*
	 * GetScore
	 * Returns int score
	 */
	int getScore();

	/*
	 * SeedMines
	 * Seeds random with time(0)
	 * Generates random ints for x and y coordinates, specifically avoiding borders
	 * Checks if the Tile at the generated coordinate has type_ GROUND
	 * If Tile is GROUND, places a mine, increments adjacent tiles, and repeats loop
	 * If Tile is MINE, does nothing and repeats loop
	*/
	void seedMines();

	/*
	 * IncrementAdjacentMines
	 * Increments the adjacentMines_ int in each neighboring Tile
	 */
	void incrementAdjacentMines(int x, int y);

	/*
	 * DecrementAdjacentMines
	 * Decrements the adjacentMines_ int in each neighboring Tile
	 */
	void decrementAdjacentMines(int x, int y);

	void rocketExplosion(int x, int y);


	void revealAdjacentTiles(int x, int y);

	/*
	 * ClearTile
	 * Takes x and y coordinates of the Tile in the minefield
	 * Call this when user or entity moves into a tile
	 */
	void clearTile(int x, int y, char t = ' ');

	/*
	 * Prints out a formated version of the map
	 * Tiles are marked with "[ ]"
	 * Mines are denoted by 'x'
	 * Other Tiles display their adjacentMines value
	 */
	void print(ostream &os = cout);

	int getTotalMines();

  	Tile* operator[](int idx);

	void offsetX(int x);

  	int offsetX();

  	void offsetY(int y);

  	int offsetY();

  	void addOffsetY(int y);

 	void addOffsetX(int x);

 	void subOffsetY(int y);

 	void subOffsetX(int x);

 	void draw();

 	void setTileSet(SDL_Texture * texture);

 	void loadTileSet(string filePath);

 	void setSrcRects(vector<SDL_Rect> &vec);

 	int minMapBorderX();

 	int minMapBorderY();

 	int maxMapBorderX();

 	int maxMapBorderY();

 	void setBounds(int minX, int minY, int maxX, int maxY);

 	void charStepInto(int x, int y,int* mode);
 	// * For the character stepping 'into' a square
 	// * Should a: check to see if there's a mine there(then blow him up)
 	// * b: clear the surrounding squares.

  void clearBorder();
  //Clears the border around the map - going into the map as necessary.

 	void restart();

 	void tileSize(int tileSize);
 	int tileSize();

 	// * Leave ints here
	int rockets_;
	int digs_;

private:
	void loadSrcRects();

	int minesTriggered_,minesDisabled_;
	int width_,height_;
	int maxMines_;
	int score_;
	Tile **field_;
	int totalMines_;

	int offsetX_;
	int offsetY_;

	SDL_Texture * tileSet_;
	SDL_Renderer * renderer_;
	vector<SDL_Rect> srcRects_;

	int minX_;
	int minY_;
	int maxX_;
	int maxY_;

	int tileSize_;
};


#endif
