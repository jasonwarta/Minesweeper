#include "textbox.h"

Textbox::Textbox(SDL_Renderer * renderer, TTF_Font * font, SDL_Window * window)
{
	font_ = font;
	width_ = 384;
	height_ = 196;

	int winW;
	int winH;
	SDL_GetWindowSize(window,&winW,&winH);

	fheight_ = TTF_FontHeight(font_)+2;
	lines_ = 172 / fheight_;

	boxDestRect_ = new SDL_Rect;
	boxDestRect_->x = 0;
	boxDestRect_->y = winH - height_;
	boxDestRect_->w = width_;
	boxDestRect_->h = height_;

	renderer_ = renderer;

	textSpots_ = vector<SDL_Rect>(lines_);
	assignTextRects();

	input_ = vector<string>(lines_);

	posY_ = winH - height_;

	background_ = SDL_CreateTextureFromSurface(renderer_,IMG_Load("Resources/chatbox.png"));
}

Textbox::~Textbox()
{

}

void Textbox::assignTextRects()
{
	for(int i = 0; i < textSpots_.size(); i++)
	{
		textSpots_[i].x = posX_ + 12;
		textSpots_[i].y = boxDestRect_->y + 12 + (fheight_ * i);
		textSpots_[i].w = 360;
		textSpots_[i].h = fheight_;
	}
}

void Textbox::draw()
{
	SDL_Color textColor = {0,0,0};
	SDL_RenderCopy(renderer_,background_,NULL,boxDestRect_);
	int w, h;
	for(int i = 0; i < lines_; i++)
	{
		SDL_Texture * temp = SDL_CreateTextureFromSurface(renderer_,TTF_RenderText_Solid(font_,input_[input_.size()-lines_+i].c_str(),textColor));
		SDL_QueryTexture(temp,NULL,NULL,&w,&h);
		textSpots_[i].w = w;
		SDL_RenderCopy(renderer_,temp,NULL,&textSpots_[i]);
	}
}

void Textbox::add(string s)
{
	input_.push_back(s);
}

void Textbox::write(string s)
{
	SDL_Color textColor = {0,0,0};
	SDL_RenderCopy(renderer_,background_,NULL,boxDestRect_);
	input_.push_back(s);
	int w, h;
	for(int i = 0; i < lines_; i++)
	{
		SDL_Texture * temp = SDL_CreateTextureFromSurface(renderer_,TTF_RenderText_Solid(font_,input_[input_.size()-lines_+i].c_str(),textColor));
		SDL_QueryTexture(temp,NULL,NULL,&w,&h);
		textSpots_[i].w = w;
		SDL_RenderCopy(renderer_,temp,NULL,&textSpots_[i]);
	}
}
