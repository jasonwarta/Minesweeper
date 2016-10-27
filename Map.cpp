#include "Map.h"
#include <vector>
using std::vector;
// * Default ctor
Map::Map(){
	width_=0;
	height_=0;
	score_=0;

}

/*
 * Map constructor, use this in most cases
 * Pass dimensions as size of minefield
 * Constructor adds 2 to each dimension to account for borders
 * Ctor takes ints for width, height, maxMines
 */
Map::Map(SDL_Renderer * renderer, int w, int h, int mines){
	// * Add 2 to account for border
	width_ = w+2;
	height_ = h+2;
	maxMines_ = mines;

  mapInit();  //killed code duplication

	renderer_ = renderer;
	loadTileSet("Resources/tiles.png");
}

void Map::restart(){
	for(int row = 0; row < height_; row++)
	{
		delete[] field_[row];
	}
	delete[] field_;
	mapInit();
}

//using this to kill code duplication -jtb
void Map::mapInit()
{
  	totalMines_ = 0;
	score_=0;

	digs_ = maxMines_ *.75;
	rockets_ = maxMines_ / 10;

	field_ = new Tile*[width_];
	for(int i = 0; i < width_; i++)
	{
		field_[i] = new Tile[height_];
	}
	seedMines();
	for(int i = 0; i < width_; i++) //sets the border
	{
		field_[0][i].setType(Tile::BORDER);
		field_[0][i].setRevealed(true);
		field_[height_-1][i].setType(Tile::BORDER);
		field_[height_-1][i].setRevealed(true);
	}
	for(int i = 0; i < height_; i++)
	{
		field_[i][0].setType(Tile::BORDER);
		field_[i][0].setRevealed(true);
		field_[i][1].setType(Tile::BORDER);
		field_[i][1].setRevealed(true);
		field_[i][width_-1].setType(Tile::BORDER);
		field_[i][width_-1].setRevealed(true);
	}

	//clears into the minefield if necessary -jtb
  // clearBorder();

	srcRects_ = vector<SDL_Rect>(28);
	loadSrcRects();
	offsetX_ = 0;
	offsetY_ = 0;
}


//* Copy ctor
Map::Map(Map &other){
	width_ = other.width_;
	height_ = other.width_;
	maxMines_ = other.maxMines_;
	score_ = other.score_;
	totalMines_ = other.totalMines_;

	field_ = new Tile*[width_];
	for(int i = 0; i < width_; i++)
	{
		field_[i] = new Tile[height_];
	}

	for(int row = 0; row < height_; row++)
	{
		for(int col = 0; col < width_; col++)
		{
			field_[row][col] = other.field_[row][col];
		}
	}
}

// * Destructor
Map::~Map(){
	width_ = 0;
	height_ = 0;
	maxMines_ = 0;
	score_ = 0;
// * Added a =0 here, otherwise row was unitialized.
	for(int row = 0; row < height_; row++)
	{
		delete[] field_[row];
	}
	delete[] field_;
}

// * Returns the width
int Map::width()
{
	return width_;
}

// * Returns the height
int Map::height()
{
	return height_;
}

// * Adds the passed int to the score
void Map::addScore(int score)
{
	score_ += score;
}

// * Subtracts the passed int from the score
void Map::subScore(int score)
{
	score_ -= score;
}

// * Sets the score to the passed int
void Map::setScore(int score)
{
	score_ = score;
}

// * Returns the score as an int
int Map::getScore()
{
	return score_;
}

// * Randomly places mines on the field
void Map::seedMines()
{
	// * Seed random to time
	srand(time(0));

	// * Int for tracking placed mines and comparing against total
	int placedMines = 0;

	// * Repeat until the required num of mines has been seeded
	while(placedMines < maxMines_)
	{
		// * Generate random ints for x and y values
		int randX = rand() % (width_-2) + 1;
		int randY = rand() % (height_-3) + 2; //Fixed bug:Was generating minds in the border.

		// * If tile at coordinates is ground (not MINE and not BORDER)
		if(field_[randX][randY].getType() == Tile::GROUND){
			// * Place a mine at coordinates
			field_[randX][randY].placeMine();
			placedMines++;
			totalMines_++;
			// * Increment the adjacentMines value of adjacent Tiles
			incrementAdjacentMines(randX,randY);
		}
	}
}

void Map::rocketExplosion(int x, int y)
{
	if(field_[x][y].getType() != Tile::MINE)
	{
		subScore(50);
	}
	for(int i = y-1; i <= y+1; i++)
	{
		for(int j = x-1; j <= x+1; j++)
		{
			if (field_[j][i].getType() != Tile::BORDER)
			{
				field_[j][i].reveal();
				if (field_[j][i].getType() == Tile::MINE)
				{
					field_[j][i].removeMine();
					field_[j][i].detonate();
					decrementAdjacentMines(j,i);
					totalMines_--;
					addScore(50);
				}
			}
		}
	}
	rockets_--;
}

void Map::incrementAdjacentMines(int x, int y)
{
	// * Map of adjacent tiles in relation to passed coordinates
	// [x-1][y+1]  [x][y+1]  [x+1][y+1]
	// [x-1][y]    [x][y]    [x+1][y]
	// [x-1][y-1]  [x][y-1]  [x+1][y-1]


	// * Increment adjacent tiles in row above passed coordinate
	field_[x-1][y+1]++;
	field_[x][y+1]++;
	field_[x+1][y+1]++;

	// * Increment adjacent tiles on left and right of passed coordinate
	field_[x-1][y]++;
	field_[x+1][y]++;

	//* Increment adjacent tiles in row below passed coordinate
	field_[x-1][y-1]++;
	field_[x][y-1]++;
	field_[x+1][y-1]++;
}

void Map::decrementAdjacentMines(int x, int y)
{
	// * Map of adjacent tiles in relation to passed coordinates
	// [x-1][y+1]  [x][y+1]  [x+1][y+1]
	// [x-1][y]    [x][y]    [x+1][y]
	// [x-1][y-1]  [x][y-1]  [x+1][y-1]


	// * Decrement adjacent tiles in row above passed coordinate
	field_[x-1][y+1]--;
	field_[x][y+1]--;
	field_[x+1][y+1]--;

	// * Decrement adjacent tiles on left and right of passed coordinate
	field_[x-1][y]--;
	field_[x+1][y]--;

	// * Decrement adjacent tiles in row below passed coordinate
	field_[x-1][y-1]--;
	field_[x][y-1]--;
	field_[x+1][y-1]--;
}

void Map::revealAdjacentTiles(int x, int y)
{
	// * Map of adjacent tiles in relation to passed coordinates
	// [x-1][y+1]  [x][y+1]  [x+1][y+1]
	// [x-1][y]    [x][y]    [x+1][y]
	// [x-1][y-1]  [x][y-1]  [x+1][y-1]


	// * Reveal adjacent tiles in row above passed coordinate
	field_[x-1][y+1].reveal();
	field_[x][y+1].reveal();
	field_[x+1][y+1].reveal();

	// * Reveal adjacent tiles on left and right of passed coordinate
	field_[x-1][y].reveal();
	field_[x+1][y].reveal();

	// * Reveal adjacent tiles in row below passed coordinate
	field_[x-1][y-1].reveal();
	field_[x][y-1].reveal();
	field_[x+1][y-1].reveal();
}

void Map::print(ostream &os)
{
	for(int i = 0; i < height_; i++)
	{
		for(int j = 0; j < width_; j++)
		{
			os << field_[i][j];
		}
		os << endl;
	}
}

void Map::clearTile(int x, int y, char t)
{
	field_[x][y].reveal();
	field_[x][y].check();

	if (t == 'r')
	{
		rockets_--;
		if (field_[x][y].getType() == Tile::MINE)
		{
			addScore(50);
			field_[x][y].removeMine();
			decrementAdjacentMines(x,y);
			totalMines_--;
		}
		else if (field_[x][y].getType() == Tile::GROUND)
		{
			subScore(50);
		}
	}
	else if (t == 'd')
	{
		digs_--;
		if(field_[x][y].getType() == Tile::MINE)
		{
			field_[x][y].removeMine();
			decrementAdjacentMines(x,y);
			totalMines_--;
			addScore(100);
		}
	}

	if(field_[x][y].getType() == Tile::MINE)
	{
		field_[x][y].removeMine();
		decrementAdjacentMines(x,y);
		totalMines_--;
	}
	else if (field_[x][y].getType() == Tile::GROUND)
	{
		if(field_[x][y].getAdjacentMines() == 0) revealAdjacentTiles(x,y);
		for(int i = y-1; i <= y+1; i++)
		{
			for(int j = x-1; j <= x+1; j++)
			{
				if(field_[j][i].checked() == false &&
					field_[j][i].getType() == Tile::GROUND &&
					field_[j][i].getAdjacentMines() == 0)
					clearTile(j,i,' ');
			}
		}
	}
	else if (field_[x][y].getType() == Tile::BORDER) //border tiles require extra checking.
  {
		for(int i = y-1; i <= y+1; i++)
		{
		  if(i >= 0 && i < height_)
      {
        for(int j = x-1; j <= x+1; j++)
        {
          if(j >= 0 && j < width_)
          {
            if(field_[j][i].checked() == false &&
              field_[j][i].getType() == Tile::GROUND &&
              field_[j][i].getAdjacentMines() == 0)
              clearTile(j,i,' ');
          }
        }
      }
		}
  }
}

int Map::getTotalMines()
{
	return totalMines_;
}

Tile* Map::operator[](int idx)
{
	return field_[idx];
}

void Map::offsetX(int x)
{
	offsetX_=x;
}

int Map::offsetX()
{
	return offsetX_;
}

void Map::offsetY(int y)
{
	offsetY_=y;
}

int Map::offsetY()
{
	return offsetY_;
}

void Map::addOffsetX(int x)
{
	offsetX_+=x;
}

void Map::addOffsetY(int y)
{
	offsetY_+=y;
}

void Map::subOffsetY(int y)
{
	offsetY_-=y;
}

void Map::subOffsetX(int x)
{
	offsetX_-=x;
}

void Map::setTileSet(SDL_Texture * texture)
{
	tileSet_ = texture;
}

void Map::loadTileSet(string filePath)
{
	tileSet_ = SDL_CreateTextureFromSurface(renderer_,IMG_Load(filePath.c_str()));
}

void Map::setSrcRects(vector<SDL_Rect> &vec)
{
	for(int i = 0; i < vec.size(); i++)
	{
		srcRects_[i].x = vec[i].x;
		srcRects_[i].y = vec[i].y;
		srcRects_[i].w = vec[i].w;
		srcRects_[i].h = vec[i].h;
	}
}

void Map::draw()
{
    int CurrentFrame = 0;
    for(int i = 0; i < height_; i++)
    {
        for(int j = 0; j < width_; j++)
        {
            SDL_Rect rectangleShowToRenderer;
            rectangleShowToRenderer.x = (j*tileSize_)- offsetX_;
            rectangleShowToRenderer.y = (i*tileSize_)- offsetY_;
            rectangleShowToRenderer.w = tileSize_;
            rectangleShowToRenderer.h = tileSize_;
            // * This is a mine
            if (field_[j][i].getTile()== 0)
            {
                SDL_RenderCopy(renderer_,tileSet_,&srcRects_[1],&rectangleShowToRenderer);

                // * If you want to see mine uncomment this *
                // SDL_RenderCopy(renderer_,tileSet_,&srcRects_[0],&rectangleShowToRenderer);
            }
            else if (field_[j][i].getTile() == 1)
            {
                // * Ground
                if(field_[j][i].getRevealed())
                {
                    if(field_[j][i].getAdjacentMines() == 0)
                    {
                        SDL_RenderCopy(renderer_,tileSet_,&srcRects_[1],&rectangleShowToRenderer);
                        SDL_RenderCopy(renderer_,tileSet_,&srcRects_[11],&rectangleShowToRenderer);
                        if(field_[j][i].detonated())
                        {
                        	SDL_RenderCopy(renderer_,tileSet_,&srcRects_[11],&rectangleShowToRenderer);
                        	SDL_RenderCopy(renderer_,tileSet_,&srcRects_[14],&rectangleShowToRenderer);
                        }

                    }
                    else
                    {
                    	SDL_RenderCopy(renderer_,tileSet_,&srcRects_[1],&rectangleShowToRenderer);
                    	SDL_RenderCopy(renderer_,tileSet_,&srcRects_[11],&rectangleShowToRenderer);
                    	if(field_[j][i].detonated())
                    	{
                        	SDL_RenderCopy(renderer_,tileSet_,&srcRects_[11],&rectangleShowToRenderer);
                        	SDL_RenderCopy(renderer_,tileSet_,&srcRects_[14],&rectangleShowToRenderer);
                        }
                        SDL_RenderCopy(renderer_,tileSet_,&srcRects_[field_[j][i].getAdjacentMines()+2],&rectangleShowToRenderer);
                    }
                }
                else
                {
                	SDL_RenderCopy(renderer_,tileSet_,&srcRects_[1],&rectangleShowToRenderer);
                }
            }
            else
            {
                // * Border
                SDL_RenderCopy(renderer_,tileSet_,&srcRects_[2],&rectangleShowToRenderer);
                SDL_RenderCopy(renderer_,tileSet_,&srcRects_[field_[j][i].getAdjacentMines()+2],&rectangleShowToRenderer);
            }

        }
    }
}

void Map::loadSrcRects()
{
    // * Mine
    srcRects_[0].x = 0;
    srcRects_[0].y = 0;
    srcRects_[0].w = 64;
    srcRects_[0].h = 64;

    // * Blank tile
    srcRects_[1].x = 64;
    srcRects_[1].y = 0;
    srcRects_[1].w = 64;
    srcRects_[1].h = 64;

    // * Blank border
    srcRects_[2].x = 128;
    srcRects_[2].y = 0;
    srcRects_[2].w = 64;
    srcRects_[2].h = 64;

    // * Transparent with '1'
    srcRects_[3].x = 192;
    srcRects_[3].y = 0;
    srcRects_[3].w = 64;
    srcRects_[3].h = 64;

    // * Transparent with '2'
    srcRects_[4].x = 256;
    srcRects_[4].y = 0;
    srcRects_[4].w = 64;
    srcRects_[4].h = 64;

    // * Transparent with '3'
    srcRects_[5].x = 320;
    srcRects_[5].y = 0;
    srcRects_[5].w = 64;
    srcRects_[5].h = 64;

    // * Transparent with '4'
    srcRects_[6].x = 384;
    srcRects_[6].y = 0;
    srcRects_[6].w = 64;
    srcRects_[6].h = 64;

    //* Transparent with '5'
    srcRects_[7].x = 0;
    srcRects_[7].y = 64;
    srcRects_[7].w = 64;
    srcRects_[7].h = 64;

    // * Transparent with '6'
    srcRects_[8].x = 64;
    srcRects_[8].y = 64;
    srcRects_[8].w = 64;
    srcRects_[8].h = 64;

    // * Transparent with '7'
    srcRects_[9].x = 128;
    srcRects_[9].y = 64;
    srcRects_[9].w = 64;
    srcRects_[9].h = 64;

    // * Transparent with '8'
    srcRects_[10].x = 192;
    srcRects_[10].y = 64;
    srcRects_[10].w = 64;
    srcRects_[10].h = 64;

    //* Including 9 for completion, but I have no idea what font you used
    srcRects_[11].x = 256;
    srcRects_[11].y = 64;
    srcRects_[11].w = 64;
    srcRects_[11].h = 64;

    //* Mouse position
    srcRects_[12].x = 320;
    srcRects_[12].y = 64;
    srcRects_[12].w = 64;
    srcRects_[12].h = 64;

    // * Cover 1
    srcRects_[13].x = 384;
    srcRects_[13].y = 64;
    srcRects_[13].w = 64;
    srcRects_[13].h = 64;

    // * Crater
    srcRects_[14].x = 0;
    srcRects_[14].y = 128;
    srcRects_[14].w = 64;
    srcRects_[14].h = 64;
}

int Map::minMapBorderX()
{
	return minX_;
}

int Map::minMapBorderY()
{
	return minY_;
}

int Map::maxMapBorderX()
{
	return maxX_;
}

int Map::maxMapBorderY()
{
	return maxY_;
}

void Map::setBounds(int minX, int minY, int maxX, int maxY)
{
	minX_ = minX;
	minY_ = minY;
	maxX_ = maxX;
	maxY_ = maxY;
}

void Map::charStepInto (int x, int y, int *mode)
{
    if (field_[x][y].getTile()== 0)
    {
    	*mode = 2;
    }
    clearTile(x,y);
}

void Map::tileSize(int tileSize){
	tileSize_ = tileSize;
}

int Map::tileSize(){
	return tileSize_;
}

void Map::clearBorder(){
	for(int i = 1; i < width_ -1; i++)
  {
    // cout << field_[width_-1][i].getAdjacentMines();
    if(field_[0][i].getAdjacentMines() == 0) //no adjacent mines
    {
      clearTile(1,i-1);  //clear left
      clearTile(1,i); //clear the tile to the right.
      clearTile(1,i+1);
    }
    if(field_[width_-1][i].getAdjacentMines() == 0) //no adjacent mines
    {
      clearTile(width_-2,i-1);
      clearTile(width_-2,i); //clear right
      clearTile(width_-2,i+1);
    }

  }
	for(int i = 2; i < height_ -1; i++)
  {
    // cout << field_[i][height_-1].getAdjacentMines();
    if(field_[i][1].getAdjacentMines() == 0) //no adjacent mines
    {
      clearTile(i-1,2); //clear the top
      clearTile(i,2); //clear the tile to the right.
      clearTile(i+1,2);
    }
    if(field_[i][height_-1].getAdjacentMines() == 0) //no adjacent mines
    {
      clearTile(i-1,height_-2);
      clearTile(i,height_-2); //clear the bottom
      clearTile(i+1,height_-2);
    }

  }
}
