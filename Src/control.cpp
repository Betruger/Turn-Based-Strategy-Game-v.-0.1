#include "control.h"


Control::Control (int s_x, int s_y, int s_width, int s_height, bool s_activated)
: x(s_x), y(s_y), width(s_width), height(s_height), activated(s_activated)
{

}

void Button::Draw(SDL_Renderer* renderer)
{
    if (activated)
    {
   // printf("ok");
         SDL_Rect rect;
     rect.x = x;
     rect.y = y;
     rect.w = width;
     rect.h = height;

     SDL_RenderCopy(renderer, srf, NULL, &rect);
       // SDL_BlitSurface(srf, NULL, screen, &rect);
    }
}


bool Control::Hit(int s_x, int s_y)
{
    if (activated && s_x > x && s_x < x + width && s_y > y && s_y < y+height)
    return true;
    else return false;
}

Button::Button(SDL_Texture* s_srf, int s_x, int s_y, int s_width, int s_height,
               bool s_activated)
: Control(s_x, s_y, s_width, s_height), srf(s_srf)
{

}
