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

#include "Functions.h"
#include <cstring>
SDL_Window * createWindow(const int W, const int H)
{
	// * Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "Error Initializing SDL, SDL_Error: %s\n", SDL_GetError() );
		return 0;
	}
    // * Create a window pointer
    // * Note that SDL_WINDOWPOS_UNDEFINED means that we don't need the window to appear in a specific place
	SDL_Window *win = SDL_CreateWindow("Mine Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, W, H, SDL_WINDOW_SHOWN);

  if( win == NULL )
  {
     printf( "Error Creating Window, SDL_Error: %s\n", SDL_GetError() );
     SDL_Quit();
     return 0;
 }
 return win;
}


void loadImages(vector<SDL_Rect>& imageVector,int Size,SDL_Renderer *renderer)
{
                // * Mine
                imageVector[0].x = 0;
                imageVector[0].y = 0;
                imageVector[0].w = 64;
                imageVector[0].h = 64;

                // * Blank tile
                imageVector[1].x = 64;
                imageVector[1].y = 0;
                imageVector[1].w = 64;
                imageVector[1].h = 64;

                // * Blank border
                imageVector[2].x = 128;
                imageVector[2].y = 0;
                imageVector[2].w = 64;
                imageVector[2].h = 64;

                // * Transparent with '1'
                imageVector[3].x = 192;
                imageVector[3].y = 0;
                imageVector[3].w = 64;
                imageVector[3].h = 64;

                // * Rransparent with '2'
                imageVector[4].x = 256;
                imageVector[4].y = 0;
                imageVector[4].w = 64;
                imageVector[4].h = 64;

                // * Rransparent with '3'
                imageVector[5].x = 320;
                imageVector[5].y = 0;
                imageVector[5].w = 64;
                imageVector[5].h = 64;

                // * Transparent with '4'
                imageVector[6].x = 384;
                imageVector[6].y = 0;
                imageVector[6].w = 64;
                imageVector[6].h = 64;

                // * Transparent with '5'
                imageVector[7].x = 0;
                imageVector[7].y = 64;
                imageVector[7].w = 64;
                imageVector[7].h = 64;

                // * Transparent with '6'
                imageVector[8].x = 64;
                imageVector[8].y = 64;
                imageVector[8].w = 64;
                imageVector[8].h = 64;

                // * Transparent with '7'
                imageVector[9].x = 128;
                imageVector[9].y = 64;
                imageVector[9].w = 64;
                imageVector[9].h = 64;

                // * Transparent with '8'
                imageVector[10].x = 192;
                imageVector[10].y = 64;
                imageVector[10].w = 64;
                imageVector[10].h = 64;

                // * Grass Cover 1
                imageVector[11].x = 256;
                imageVector[11].y = 64;
                imageVector[11].w = 64;
                imageVector[11].h = 64;

                // * Mouse position
                imageVector[12].x = 320;
                imageVector[12].y = 64;
                imageVector[12].w = 64;
                imageVector[12].h = 64;

                // * Cover 1
                imageVector[13].x = 384;
                imageVector[13].y = 64;
                imageVector[13].w = 64;
                imageVector[13].h = 64;
}


void displayText(SDL_Renderer * renderer, TTF_Font * font, int posX, int posY, int sizeX, int sizeY, SDL_Color textColor,string * whatSay)
{

// * Note: This will need to be refactored if it's to be compiled under microsoft visual studio
    char convertedText[whatSay->size()+1];
    strncpy(convertedText, whatSay->c_str(),whatSay->size()+1);

    SDL_Surface *text;
    text = TTF_RenderText_Solid(font,convertedText,textColor);
    SDL_Texture* messageRenderBox = SDL_CreateTextureFromSurface(renderer, text);
    SDL_Rect Message_rect;
    Message_rect.x = posX;
    Message_rect.y = posY;
    Message_rect.w = sizeX;
    Message_rect.h = sizeY;
    SDL_RenderCopy(renderer, messageRenderBox, NULL, &Message_rect);
}

void loadScanningRects(vector<SDL_Rect> &vec)
{
    vec[0].x = 0;
    vec[0].y = 0;
    vec[0].w = 105;
    vec[0].h = 124;

    vec[1].x = 105;
    vec[1].y = 0;
    vec[1].w = 103;
    vec[1].h = 124;

    vec[2].x = 210;
    vec[2].y = 0;
    vec[2].w = 105;
    vec[2].h = 124;

    vec[3].x = 315;
    vec[3].y = 0;
    vec[3].w = 105;
    vec[3].h = 124;

    vec[4].x = 420;
    vec[4].y = 0;
    vec[4].w = 105;
    vec[4].h = 124;

    vec[5].x = 525;
    vec[5].y = 0;
    vec[5].w = 105;
    vec[5].h = 124;
}

void loadWalkingRects(vector<SDL_Rect> &vec){
    vec[0].x = 0;
    vec[0].y = 0;
    vec[0].w = 103;
    vec[0].h = 111;

    vec[1].x = 103;
    vec[1].y = 0;
    vec[1].w = 103;
    vec[1].h = 111;

    vec[2].x = 206;
    vec[2].y = 0;
    vec[2].w = 103;
    vec[2].h = 111;

    vec[3].x = 309;
    vec[3].y = 0;
    vec[3].w = 103;
    vec[3].h = 111;

    vec[4].x = 412;
    vec[4].y = 0;
    vec[4].w = 103;
    vec[4].h = 111;

    vec[5].x = 515;
    vec[5].y = 0;
    vec[5].w = 103;
    vec[5].h = 111;

    vec[6].x = 618;
    vec[6].y = 0;
    vec[6].w = 103;
    vec[6].h = 111;

    vec[7].x = 721;
    vec[7].y = 0;
    vec[7].w = 103;
    vec[7].h = 111;
}

void loadSrcRects(vector<SDL_Rect> &vec, SDL_Texture *img, int frames){
    int w,h;
    SDL_QueryTexture(img,NULL,NULL,&w,&h);
    w /= vec.size();

    for(int i = 0; i < vec.size(); i++){
        vec[i].x = w*i;
        vec[i].y = 0;
        vec[i].w = w;
        vec[i].h = h;
    }
}

SDL_Rect * getTargetRect(SDL_Rect * rect,int posX, int posY){
    SDL_Rect *temp = new SDL_Rect;

    temp->x = (posX * 64)/2;
    temp->y = (posY * 64)/2;
    temp->w = rect->w;
    temp->h = rect->h;

    return temp;
}

SDL_Rect* getTargetRect(int x, int y, int w, int h){
    SDL_Rect *temp = new SDL_Rect;

    temp->x = x;
    temp->y = y;
    temp->w = w;
    temp->h = h;

    return temp;
}

void init(){
    // * Initialize SDL
    if( SDL_Init( SDL_INIT_EVERYTHING ) < 0 )
    {
        printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
    }

    // * Initialize SDL_Image
    if( !( IMG_Init( IMG_INIT_PNG ) & IMG_INIT_PNG ) )
    {
        printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
    }

    // * Initialize SDL_ttf
    if(TTF_Init()==-1) {
        printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
    }

    // * Initialize SDL_mixer
    if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
    {
        printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
    }
}

void loadPrevScores(vector<int> &scores)
{
    fstream fs;
    fs.open("scores.dat", ios::in);

    if(fs.is_open())
    {   
        cout << "loading scores" << endl;
        while(fs.good())
        {
            string name;
            int score;
            fs >> score;
            if(score != 0)
            {
                scores.push_back(score);
            }   
            if(fs.peek()==EOF)
            {
                break;
            }
        }
        fs.close();
        quicksort(scores,0,scores.size()-1);
        cout << "done loading scores" << endl;
    }
    else
    {
        cout << "score.dat doesn't exist" << endl;
    }
    

    // for(int i = 0; i < scores.size(); i++){
    //     cout << scores[i] << endl;
    // }
}

void saveScores(vector<int> &scores){
    fstream fs;
    fs.open("scores.dat", ios::out);

    if(fs.is_open())
    {
        while(!scores.empty()){
            fs << " ";
            fs << scores.back();
            scores.pop_back();
        }
    }
}

template<typename T>
void quicksort(vector<T> & vec, int bot, int top){
    // * Index placeholders
    int lo = bot;
    int hi = top;

    // * Value to pivot around
    int piv = vec[(top+bot)/2];

    // * Until the indexes pass eachother
    while(lo <= hi)
    {
        // * Search until a value is found less than lo index
        while(vec[lo] < piv) lo++;
        // * Search until a value is found higher than hi index
        while(vec[hi] > piv) hi--;
        if(lo <= hi)
        {
            // * Swap the values at the lo and hi indexes
            T temp = vec[lo];
            vec[lo] = vec[hi];
            vec[hi] = temp;
            lo++;
            hi--;
        }
    }

    // * Repeat for subsections of array until done
    if(bot < hi) quicksort(vec,bot,hi);
    if(lo < top) quicksort(vec,lo,top);
}

// * Stolen from SDL 2.0.4 library
bool SDL_PointInRect(const SDL_Point *p, const SDL_Rect *r)
{
    return ( (p->x >= r->x) && (p->x < (r->x + r->w)) &&
       (p->y >= r->y) && (p->y < (r->y + r->h)) );
}



