#include "slider.h"

Slider::Slider(SDL_Renderer * renderer, SDL_Window * window, SDL_Texture * back, SDL_Texture * nob){
	renderer_ = renderer;
	window_ = window; 
	back_ = back;
	nob_ = nob;

	SDL_GetWindowSize(window, &win_w_, &win_h_);

	SDL_QueryTexture(back_,NULL,NULL,&back_w_,&back_h_);
	SDL_QueryTexture(nob_,NULL,NULL,&nob_w_,&nob_h_);
}

void Slider::setNobPos(int pos){
	nobSetting_ = 128 - pos;
}

SDL_Rect & Slider::nob(){
	return nobPos_;
}

void Slider::setPos(int x, int y){
	backPos_.x = x;
	backPos_.y = y;
	backPos_.w = back_w_;
	backPos_.h = back_h_;

	nobPos_.x = x + (back_w_/2) - (nob_w_/2);
	nobPos_.y = y + 8 - (nob_h_/2) + nobSetting_;
	nobPos_.w = nob_w_;
	nobPos_.h = nob_h_;
}

void Slider::draw(){
	SDL_RenderCopy(renderer_,back_,NULL,&backPos_);
	SDL_RenderCopy(renderer_,nob_,NULL,&nobPos_);
}

void Slider::adjustVolume(SDL_Event &e, int channel){
    
  bool close = false;

  while(!close){
    while(SDL_PollEvent(&e) != 0){
      if(e.type == SDL_MOUSEMOTION){
      	SDL_Point mouse;
      	SDL_GetMouseState(&mouse.x,&mouse.y);

      	if( backPos_.y + 8 < mouse.y && mouse.y < backPos_.y + 128 + 8 )
      	{
      		nobPos_.y = mouse.y - (nob_h_/2);
        }

        nobSetting_ = 128 - ( nobPos_.y + (nobPos_.w/2) - (backPos_.y + 8) );

      	Mix_Volume(channel,nobSetting_);

      	draw();
      	SDL_RenderPresent(renderer_);
      } 
      else if ( e.type == SDL_MOUSEBUTTONUP)
      {
      	close = true;
      }
    }
  }
}