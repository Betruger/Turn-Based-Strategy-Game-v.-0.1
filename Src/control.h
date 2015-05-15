#ifndef _CONTROL_H_
#define _CONTROL_H_

#include "SDL.h"

class Control
{
    public:
    Control(int s_x, int s_y, int s_width, int s_height, bool s_activated = true);
    virtual void Draw (SDL_Renderer* renderer) {};
    bool Hit(int s_x, int s_y);
    void Activate(bool act) {activated = act;};
     bool IsActivated() {return activated;};


    protected:
    //SDL_Surface* srf;
    int x;
    int y;
    int width;
    int height;
    bool activated;
};

class Button : public Control
{
    public:
    Button(SDL_Texture* s_srf, int s_x, int s_y, int s_width, int s_height,
           bool s_activated = true);
    virtual void Draw (SDL_Renderer* renderer);

    protected:
    SDL_Texture* srf;
};




#endif // _CONTROL_H_
