#include "animation.h"

Animation::Animation()
{
}

Animation::Animation(SDL_Renderer * renderer, SDL_Window * window, Map &map, Textbox &textbox, vector<Button> &buttons, string IMGpath, int frames, int tileSize, int timeDelay)
{
  SDL_Texture * tempImg = SDL_CreateTextureFromSurface(renderer,IMG_Load(IMGpath.c_str()));
	SDL_GetWindowSize(window, &win_w_, &win_h_);

	if(SDL_QueryTexture(tempImg,NULL,NULL,&frame_w_,&frame_h_) != 0)
  {
  	cout << "Error getting width and height in Animation constructor" << endl;
  }

  buttons_ = &buttons;
  map_ = &map;
  textbox_ = &textbox;

  imgPath_ = IMGpath;
	srcImg_ = tempImg;
	frames_ = frames;
	renderer_ = renderer;
	tileSize_ = tileSize;
	timeDelay_ = timeDelay;
	frame_w_ /= frames_;
	
  charposX_ = 0;
  charposY_ = map_->tileSize();
  mapX_ = 0; // * Set the initial position of the character in the minefield.
  mapY_ = 1;

  srcRect_ = vector<SDL_Rect>(frames);
	loadSrcRects();

  charoffsetX_ = 0;
  charoffsetY_ = 0;

 	frame_w_ = srcRect_[0].w;
 	frame_h_ = srcRect_[0].h;


}

void Animation::restart()
{
  charposX_ = 0;
  charposY_ = map_->tileSize();
  mapX_ = 0;
  mapY_ = 1;
  charoffsetX_ = 0;
  charoffsetY_ = 0;
}

Animation::~Animation()
{
}

void Animation::up()
{
    --mapY_; // * Notes the character moves up.

	for(int i = 0; i < frames_; i++)
  {
    if (charposY_>0)
    {
      charposY_-= (map_->tileSize()/frames_);
    }
    if ((charposY_-map_->offsetY())+map_->tileSize() <= (win_h_)/2)
    {
      if (map_->offsetY()>0)
        {
            map_->addOffsetY(-(map_->tileSize()/frames_));
        }
    }
	  
    map_->draw();
    SDL_RenderCopy(renderer_,srcImg_,&srcRect_[i],getTargetRect((charposX_)+(map_->tileSize()/2)-map_->offsetX(),(charposY_)+(2.5*map_->tileSize())-map_->offsetY(),frame_w_,frame_h_));
	  textbox_->draw();

    for(int i = 0; i < buttons_->size(); i++)
    {
      buttons_->at(i).draw();
    }

	  SDL_RenderPresent(renderer_);
	  SDL_Delay(timeDelay_);
	}

}

void Animation::down()
{
  ++mapY_; // * Notes the character moves down.

  for(int i = 0; i < frames_; i++)
  {
    if (((charposY_-map_->offsetY())+map_->tileSize())<win_h_)
    {
      charposY_+= (map_->tileSize()/frames_);
    }
    if ((charposY_-map_->offsetY())+map_->tileSize() >= (win_h_)/2)
    {
      if (map_->offsetY()<map_->maxMapBorderY())
        {
            map_->addOffsetY((map_->tileSize()/frames_));
        }
    }

	  SDL_RenderClear(renderer_);
    map_->draw();
    SDL_RenderCopy(renderer_,srcImg_,&srcRect_[i],getTargetRect((charposX_)+(map_->tileSize()/2)-map_->offsetX(),(charposY_)+(2.5*map_->tileSize())-map_->offsetY(),frame_w_,frame_h_));
    textbox_->draw();

    for(int i = 0; i < buttons_->size(); i++)
    {
      buttons_->at(i).draw();
    }
    SDL_RenderPresent(renderer_);
    SDL_Delay(timeDelay_);
	}
}

void Animation::left()
{
    --mapX_; // * Notes the character moves left.

	for(int i = 0; i < frames_; i++)
  {
    if (charposX_>0)
    {
      charposX_-= (map_->tileSize()/frames_);
    }
    if ((charposX_-map_->offsetX()) <= (win_w_)/2)
    {
      if (map_->offsetX()>0)
      {
        map_->addOffsetX(-(map_->tileSize()/frames_));
      }
    }
    map_->draw();
    SDL_RenderCopy(renderer_,srcImg_,&srcRect_[i],getTargetRect((charposX_)+(map_->tileSize()/2)-map_->offsetX(),(charposY_)+(2.5*map_->tileSize())-map_->offsetY(),frame_w_,frame_h_));
    textbox_->draw();

    for(int i = 0; i < buttons_->size(); i++)
    {
      buttons_->at(i).draw();
    }

    SDL_RenderPresent(renderer_);
    SDL_Delay(timeDelay_);
	}
}

void Animation::right()
{ 
  ++mapX_; // * Notes the character moves right.
	for(int i = 0; i < frames_; i++)
  {
    if (((charposX_-map_->offsetX())+map_->tileSize())<win_w_)
    {
      charposX_+= (map_->tileSize()/frames_);
    }
    if ((charposX_-map_->offsetX())+map_->tileSize() >= (win_w_)/2)
    {
      if (map_->offsetX()<map_->maxMapBorderX())
        {
            map_->addOffsetX((map_->tileSize()/frames_));
        }
    }
	  map_->draw();
    SDL_RenderCopy(renderer_,srcImg_,&srcRect_[i],getTargetRect((charposX_)+(map_->tileSize()/2)-map_->offsetX(),(charposY_)+(2.5*map_->tileSize())-map_->offsetY(),frame_w_,frame_h_));
	  textbox_->draw();

    for(int i = 0; i < buttons_->size(); i++)
    {
      buttons_->at(i).draw();
    }

	  SDL_RenderPresent(renderer_);
	  SDL_Delay(timeDelay_);
	}
}

void Animation::draw()
{
	SDL_RenderCopy(renderer_,srcImg_,&srcRect_[1],getTargetRect((charposX_)+(map_->tileSize()/2)-map_->offsetX(),(charposY_)+(2.5*map_->tileSize())-map_->offsetY(),frame_w_,frame_h_));
}

void Animation::loadSrcRects()
{
  for(int i = 0; i < frames_; i++)
  {
    srcRect_[i].x = frame_w_ * i;
    srcRect_[i].y = 0;
    srcRect_[i].w = frame_w_;
    srcRect_[i].h = frame_h_;
  }
}

SDL_Rect* Animation::getTargetRect(int x, int y, int w, int h)
{
    SDL_Rect *temp = new SDL_Rect;
    temp->x = x-rotpt_.x;
    temp->y = y-(2*rotpt_.y);
    temp->w = (map_->tileSize() * frame_w_)/64;
    temp->h = (map_->tileSize() * frame_h_)/64;

    return temp;
}

void Animation::rotpt(SDL_Point point)
{
	rotpt_ = point;
}

SDL_Point Animation::rotpt()
{
	return rotpt_;
}

void Animation::drawAtMouse(SDL_Point point)
{
	SDL_RenderCopy(renderer_,srcImg_,&srcRect_[1],getTargetRect(point.x,point.y,frame_w_,frame_h_));
}

void Animation::pathParabola(int x, int y, Animation * pc)
{
	//* Recalculate target point so rocket ends up in middle of target tile
	int tarX = (x / map_->tileSize()) * map_->tileSize() + map_->tileSize()/2;
	int tarY = (y / map_->tileSize()) * map_->tileSize() + map_->tileSize()/2;

	// * Adjust offset, set distance value
	int dist = tarX;
	int offsetY = tarY + 210;
	int offsetX = 0;

	for(int i = 0; i < dist; i+=16)
  {
		SDL_RenderClear(renderer_);
		double dx = i;
		double dy = 0;

		// * Calculate the slope
		double m = slope(dx,dy,dist);

		// * Draw map and character
		map_->draw();
		pc->draw();

		// * Get target rectangle
		SDL_Rect * tarRect = getTargetRect(offsetX + i - 79 -20 + 32,offsetY - 220 - (int)dy,frame_w_,frame_h_);

		// * Draw
		SDL_RenderCopyEx(renderer_,
										 srcImg_,
										 &srcRect_[i%frames_],
										 tarRect,
										 (-45)*atan(m),
										 &rotpt_,
										 SDL_FLIP_NONE);

		textbox_->draw();

    for(int i = 0; i < buttons_->size(); i++)
    {
      buttons_->at(i).draw();
    }

		SDL_RenderPresent(renderer_);
		SDL_Delay(timeDelay_);

		// * Keep quantity of rectangles under control
		delete tarRect;
	}
}

double Animation::slope(int x, double &y, int dist){
	// * Calculate points on parabola
	double p1y = - ((dist/5) * pow((x+4) - (dist/2),2)) / pow(dist/2,2) + (dist/5);
	double p2y = - ((dist/5) * pow(x - (dist/2),2)) / pow(dist/2,2) + (dist/5);

	// * Asign y value to the pure point
	y = p2y;

	// * Calculate slope given a x value of 4
	double slope = (p1y - p2y)/4;

	return slope;
}

void Animation::posX(int x)
{
	charposX_ = x;
}
int Animation::posX()
{
	return charposX_;
}

void Animation::poxY(int y)
{
	charposY_ = y;
}
int Animation::posY()
{
	return charposY_;
}

int Animation::offsetX()
{
	return charoffsetX_;
}
int Animation::offsetY()
{
	return charoffsetY_;
}
int Animation::mapX()
{
    return mapX_;
}
int Animation::mapY()
{
    return mapY_;
}
