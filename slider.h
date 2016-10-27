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

class Slider{
public:
	Slider();

	Slider(SDL_Renderer * renderer, SDL_Window * window, SDL_Texture * back, SDL_Texture * nob);

	void setNobPos(int pos);

	SDL_Rect & nob();

	void setPos(int x, int y);

	void draw();

	void adjustVolume(SDL_Event &e, int channel);

private:
	SDL_Renderer * renderer_;
	SDL_Window * window_;

	SDL_Texture * back_;
	SDL_Texture * nob_;

	SDL_Rect backPos_;
	SDL_Rect nobPos_;

	int win_w_;
	int win_h_;

	int nob_w_;
	int nob_h_;

	int back_w_;
	int back_h_;

	int nobSetting_;
};