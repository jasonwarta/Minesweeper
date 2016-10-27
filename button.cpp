#include "button.h"
#include "Functions.h"

Button::Button(){
	text_ = "";
	posX_ = 0;
	posY_ = 0;
	width_ = 0;
	height_ = 0;
}

Button::Button(SDL_Renderer * renderer, SDL_Window * window, TTF_Font * font){
	renderer_ = renderer;
	window_ = window;
	font_ = font;
}

Button::Button(SDL_Renderer * renderer, SDL_Window * window, TTF_Font * font, int x, int y, int w, int h)
{
	renderer_ = renderer;
	textureRenderer_ = SDL_CreateRenderer(window,-1,SDL_RENDERER_TARGETTEXTURE);
	SDL_GetWindowSize(window, &win_w_, &win_h_);
	window_ = window;
	posX_ = x;
	posY_ = y;
	width_ = w;
	height_ = h;
	font_ = font;

	border_ = new SDL_Rect;
	fill_ = new SDL_Rect;
	textPos_ = new SDL_Rect;
	getTargetRects();

	SDL_Color textcolor = {0,0,0};
	textColor_ = textcolor;
	txtTexture_ = SDL_CreateTextureFromSurface(renderer_,TTF_RenderText_Solid(font_,text_.c_str(),textColor_));

	int width;
	int height;
	SDL_QueryTexture(txtTexture_,NULL,NULL,&width,&height);

	textWidth_ = width;
	textHeight_ = TTF_FontHeight(font_)+1;

	background_ = SDL_CreateTextureFromSurface(renderer_,IMG_Load("Resources/transparent_black.png"));
}

Button::Button(const Button &other){
	posX_ = other.posX_;
	posY_ = other.posY_;
	width_ = other.width_;
	height_ = other.height_;
	textWidth_ = other.textWidth_;
	textHeight_ = other.textHeight_;
	win_h_ = other.win_h_;
	win_w_ = other.win_w_;
	text_ = other.text_;
	textureRenderer_ = other.textureRenderer_;
	renderer_ = other.renderer_;
	window_ = other.window_;
	border_ = other.border_;
	fill_ = other.fill_;
	textPos_ = other.textPos_;
	txtTexture_ = other.txtTexture_;
	button_ = other.button_;
	font_ = other.font_;
	textColor_ = other.textColor_;
}

void Button::operator=(const Button &other){
	posX_ = other.posX_;
	posY_ = other.posY_;
	width_ = other.width_;
	height_ = other.height_;
	textWidth_ = other.textWidth_;
	textHeight_ = other.textHeight_;
	win_h_ = other.win_h_;
	win_w_ = other.win_w_;
	text_ = other.text_;
	textureRenderer_ = other.textureRenderer_;
	renderer_ = other.renderer_;
	window_ = other.window_;
	border_ = other.border_;
	fill_ = other.fill_;
	textPos_ = other.textPos_;
	txtTexture_ = other.txtTexture_;
	button_ = other.button_;
	font_ = other.font_;
	textColor_ = other.textColor_;
}

void Button::getTargetRects()
{
  // border_ = new SDL_Rect;
  // fill_ = new SDL_Rect;
  // textPos_ = new SDL_Rect;

  border_->x = posX_;
  border_->y = posY_;
  border_->w = width_;
  border_->h = height_;

  fill_->x = posX_ + 2;
  fill_->y = posY_ + 2;
  fill_->w = width_ - 4;
  fill_->h = height_ - 4;

  textPos_->x = (posX_+4) + ((width_/2) - (textWidth_/2));
  textPos_->y = (posY_+4) + ((height_/2) - (textHeight_/2));
	textPos_->w = textWidth_;
	textPos_->h = textHeight_;
}

void Button::draw(string text)	
{
  text_ = text;
  SDL_SetRenderDrawColor(renderer_,0,0,0,255);
  SDL_RenderFillRect(renderer_,border_);
  SDL_SetRenderDrawColor(renderer_,200,200,200,255);
  SDL_RenderFillRect(renderer_,fill_);
  SDL_Color tcolor = {0,0,0};
  txtTexture_ = SDL_CreateTextureFromSurface(renderer_,TTF_RenderText_Solid(font_,text_.c_str(),tcolor));
  // SDL_Texture * temp = SDL_CreateTextureFromSurface(renderer_,TTF_RenderText_Solid(font_,text_.c_str(),tcolor));
  // txtTexture_ = temp;
  SDL_QueryTexture(txtTexture_,NULL,NULL,&textWidth_,&textHeight_);
  textPos_->x = (posX_) + ((width_/2) - (textWidth_/2));
  textPos_->y = (posY_) + ((height_/2) - (textHeight_/2));
  textPos_->w = textWidth_;
  textPos_->h = textHeight_;
  SDL_RenderCopy(renderer_,txtTexture_,NULL,textPos_);
}

void Button::draw()
{
  SDL_SetRenderDrawColor(renderer_,0,0,0,255);
  SDL_RenderFillRect(renderer_,border_);
  SDL_SetRenderDrawColor(renderer_,200,200,200,255);
  SDL_RenderFillRect(renderer_,fill_);
  SDL_RenderCopy(renderer_,txtTexture_,NULL,textPos_);
}

SDL_Rect * Button::rect()
{
	return border_;
}

void Button::setTextColor(Uint8 r, Uint8 g, Uint8 b)
{
	SDL_Color c = {r,g,b};
	textColor_ = c;
}

bool Button::SDL_PointInRect(const SDL_Point *p, const SDL_Rect *r)
{
    return ( (p->x >= r->x) && (p->x < (r->x + r->w)) &&
             (p->y >= r->y) && (p->y < (r->y + r->h)) );
}

void Button::position(int x, int y, int w, int h){
	border_->x = x;
	border_->y = y;
	border_->w = w;
	border_->h = h;

	posX_ = x;
	posY_ = y;
	width_ = w;
	height_ = h;
}

SDL_Point Button::position(){
	SDL_Point temp = {posX_,posY_};
	return temp;
}

void Button::animateRect(int final_X, int final_Y, int final_W, int final_H){
	int frames = 16;

	SDL_Rect backdrop;
	backdrop.x = final_X + (final_W /2);
	backdrop.y = final_Y;
	backdrop.w = 20;
	backdrop.h = 0;

	SDL_SetRenderDrawColor(renderer_,50,50,50,255);

	SDL_RenderFillRect(renderer_,&backdrop);
	SDL_Delay(15);

	for(int i = 0; i < frames; i++){

		backdrop.h = (1+i) * (final_H/frames);

		SDL_RenderFillRect(renderer_,&backdrop);
		SDL_Delay(15);
		SDL_RenderPresent(renderer_);
	}

	for(int i = 1; i < frames; i++){
		backdrop.x = final_X + (final_W /2) - ( (i * (final_W / frames) ) /2);
		backdrop.w = (i * final_W / frames);

		SDL_RenderFillRect(renderer_,&backdrop);
		SDL_Delay(15);
		SDL_RenderPresent(renderer_);
	}

	SDL_RenderFillRect(renderer_,&backdrop);
}

void Button::animateRect(SDL_Texture * texture, int final_X, int final_Y, int final_W, int final_H){
	int frames = 16;

	SDL_Rect backdrop;
	backdrop.x = final_X + (final_W /2);
	backdrop.y = final_Y;
	backdrop.w = 20;
	backdrop.h = 0;

	SDL_Rect source;
	source.x = (final_W /2);
	source.y = 0;
	source.w = 20;
	source.h = 0;

	SDL_RenderCopy(renderer_,texture,&source,&backdrop);
	SDL_Delay(15);

	for(int i = 0; i < frames; i++){

		backdrop.h = (1+i) * (final_H/frames);
		source.h = (1+i) * (final_H/frames);

		SDL_RenderCopy(renderer_,texture,&source,&backdrop);
		SDL_Delay(15);
		SDL_RenderPresent(renderer_);
	}

	for(int i = 1; i < frames; i++){
		backdrop.x = final_X + (final_W /2) - ( (i * (final_W / frames) ) /2);
		backdrop.w = (i * final_W / frames);

		source.x = (final_W /2) - ( (i * (final_W / frames) ) /2);
		source.w = (i * final_W / frames);

		SDL_RenderCopy(renderer_,texture,&source,&backdrop);
		SDL_Delay(15);
		SDL_RenderPresent(renderer_);
	}

	SDL_RenderCopy(renderer_,texture,NULL,&backdrop);
}

int Button::showScoresheet(SDL_Event &e, vector<int> &scores){
	animateRect((win_w_/2)-75,200,150,(scores.size() * textHeight_) + 80);
  
  vector<SDL_Rect> textSpots(scores.size());

  for(int i = 0; i < textSpots.size(); i++){
		textSpots[i].x = (win_w_/2) - 30;
		textSpots[i].y = 200 + 12 + (textHeight_ * i);
		textSpots[i].w = textWidth_;
		textSpots[i].h = textHeight_;
	}

	SDL_Color tcolor = {255,255,255,255};

	int w,h;

	for(int i = 0; i < textSpots.size(); i++){
		SDL_Texture *temp = SDL_CreateTextureFromSurface(renderer_,TTF_RenderText_Solid(font_,toString(scores[i]).c_str(),tcolor));
		SDL_QueryTexture(temp,NULL,NULL,&w,&h);
		textSpots[i].w = w;
		SDL_RenderCopy(renderer_,temp,NULL,&textSpots[i]);
	}

	Button btnClose(renderer_,window_,font_,(win_w_/2)-40,200+(scores.size() * textHeight_) + 20,80,40);
	btnClose.setTextColor(255,255,255);
	btnClose.draw("Close");
	SDL_RenderPresent(renderer_);
 
  bool close = false;

  while(!close){
  	while(SDL_PollEvent( &e ) != 0)
  	{
  		if(e.type == SDL_QUIT)
  		{
  			return 0;
  		} 
  		else if (e.key.keysym.sym == SDLK_ESCAPE) {
  			close = true;
  		} 
  		else if (e.type == SDL_MOUSEBUTTONDOWN)
  		{
  			SDL_Point mouse = {0,0};
  			SDL_GetMouseState(&mouse.x,&mouse.y);

  			if(SDL_PointInRect(&mouse,btnClose.rect()))
  			{
  				close = true;
  			} 
  		}
  	}
  }
  return -1;
}

int Button::mainMenu(SDL_Event &e, SDL_Texture * background, Slider &musicVol, Slider &effectsVol, vector<int> &scores){
	int w,h;
	SDL_QueryTexture(background,NULL,NULL,&w,&h);
	int x = (win_w_/2) - (w/2);
	int y = 60;

	animateRect(background,x,y,w,h);
	SDL_Rect menuTarget;
	menuTarget.x = x;
	menuTarget.y = y;
	menuTarget.w = w;
	menuTarget.h = h;

	SDL_RenderCopy(renderer_,background,NULL,&menuTarget);

	Button btnNewMap(renderer_,window_,font_,x+(w/2)-40, y+150, 80, 40);
	btnNewMap.draw("New Map");
	Button btnScores(renderer_,window_,font_,x+(w/2)-40, y+200, 80, 40);
	btnScores.draw("Scores");
	Button btnQuit(renderer_,window_,font_,x+(w/2)-40, y+250, 80, 40);
	btnQuit.draw("Quit");
	
	Button lblMusicVol(renderer_,window_,font_,x+w-80-75,y+(h/2)-(144/2)-45,70,40);
	lblMusicVol.draw("Music");
	Button lblEffectsVol(renderer_,window_,font_,x+w-80,y+(h/2)-(144/2)-45,70,40);
	lblEffectsVol.draw("Effects");

	musicVol.setPos(x+w-10-25-20-25-5-25-20,y+(h/2)-(144/2));
	musicVol.draw();
	effectsVol.setPos(x+w-10-25-20,y+(h/2)-(144/2));
	effectsVol.draw();

	SDL_RenderPresent(renderer_);

	bool close = false;
	while(!close){

		while(SDL_PollEvent(&e) != 0){

			SDL_RenderCopy(renderer_,background,NULL,&menuTarget);
			musicVol.draw();
			effectsVol.draw();
			btnNewMap.draw();
			btnScores.draw();
			btnQuit.draw();
			lblMusicVol.draw();
			lblEffectsVol.draw();

			if(e.type == SDL_QUIT){
				return 0;
			} 
			else if (e.key.keysym.sym == SDLK_ESCAPE){
				close = true;
			} 
			else if (e.type == SDL_MOUSEMOTION){
				SDL_RenderCopy(renderer_,background,NULL,&menuTarget);
				musicVol.draw();
				effectsVol.draw();
			}
			else if (e.type == SDL_MOUSEBUTTONDOWN) 
			{
				SDL_Point mouse;
				SDL_GetMouseState(&mouse.x,&mouse.y);

				if(SDL_PointInRect(&mouse,&effectsVol.nob()))
				{
					effectsVol.adjustVolume(e,0);
				} 
				else if (SDL_PointInRect(&mouse,&musicVol.nob()))
				{
					musicVol.adjustVolume(e,1);
				} 
				else if (SDL_PointInRect(&mouse,btnNewMap.rect()))
				{
					return 1; //reset map
				} 
				else if (SDL_PointInRect(&mouse,btnScores.rect()))
				{
					int code = btnScores.showScoresheet(e,scores); //show scores
					if(code == 0){
						return 0;
					}

					SDL_RenderCopy(renderer_,background,NULL,&menuTarget);
					musicVol.draw();
					effectsVol.draw();
					btnNewMap.draw();
					btnScores.draw();
					btnQuit.draw();
					lblMusicVol.draw();
					lblEffectsVol.draw();
					SDL_RenderPresent(renderer_);
				} 
				else if (SDL_PointInRect(&mouse,btnQuit.rect()))
				{
					return 0; //quit
				}
			}
		}
	}
	return -1;
}

int Button::pauseMenu(SDL_Event &e, Slider &musicVol, Slider &effectsVol){
	animateRect(win_w_/2 - 150,125,300,250);

	Button btnResume(renderer_,window_,font_,(win_w_/2)-150+30,100+50,100,40);
	btnResume.draw("Resume");
	Button btnRestart(renderer_,window_,font_,(win_w_/2)-150+30,100+50+50,100,40);
	btnRestart.draw("Restart");
	Button btnMainMenu(renderer_,window_,font_,(win_w_/2)-150+30,100+50+50+50,100,40);
	btnMainMenu.draw("Main Menu");
	Button btnQuit(renderer_,window_,font_,(win_w_/2)-150+30,100+50+50+50+50,100,40);
	btnQuit.draw("Quit");

	Button lblMusicVol(renderer_,window_,font_,(win_w_/2)+150-165,100+50,70,35);
	lblMusicVol.draw("Music");
	Button lblEffectsVol(renderer_,window_,font_,(win_w_/2)+150-90,100+50,70,35);
	lblEffectsVol.draw("Effects");

	musicVol.setPos((win_w_/2)+150-165+25,100+50+38);
	musicVol.draw();
	effectsVol.setPos((win_w_/2)+150-90+25,100+50+38);
	effectsVol.draw();

	SDL_RenderPresent(renderer_);

	bool close = false;
	while(!close)
	{
		while(SDL_PollEvent(&e) != 0)
		{	
			btnResume.draw();
			btnRestart.draw();
			btnMainMenu.draw();
			btnQuit.draw();
			lblMusicVol.draw();
			lblEffectsVol.draw();
			musicVol.draw();
			effectsVol.draw();

			if(e.type == SDL_QUIT)
			{
				return 0;
			}
			else if(e.key.keysym.sym == SDLK_ESCAPE)
			{
				close = true;
			}
			else if(e.type == SDL_MOUSEBUTTONDOWN){
				SDL_Point mouse;
				SDL_GetMouseState(&mouse.x,&mouse.y);

				if(SDL_PointInRect(&mouse,btnResume.rect())){
					close = true;
				}
				else if(SDL_PointInRect(&mouse,btnRestart.rect())){
					return 1;
				}
				else if (SDL_PointInRect(&mouse,btnMainMenu.rect())){
					return 3;
				}
				else if (SDL_PointInRect(&mouse,btnQuit.rect())){
					return 0;
				}
				else if(SDL_PointInRect(&mouse,&effectsVol.nob()))
				{
					effectsVol.adjustVolume(e,0);
				} 
				else if (SDL_PointInRect(&mouse,&musicVol.nob()))
				{
					musicVol.adjustVolume(e,1);
				} 
			}
		}
	}
	return -1;
}

void Button::setScoreVec(vector<int> &vec){
	scores_ = &vec;
}








