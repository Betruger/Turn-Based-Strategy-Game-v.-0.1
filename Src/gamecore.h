#ifndef _GAMECORE_H_
#define _GAMECORE_H_

#include "map.h"
#include <locale>
//#include "battle.h"
//#include "SDL_ttf.h"

//extern int scr_width;
//extern int scr_height;

extern bool quit;
extern int time_current;
extern int time_passed;
extern int timer;

extern SDL_Window* sdl2window;
extern SDL_Renderer* renderer;

extern SDL_Texture* tex_grass;
extern SDL_Texture* tex_soldier;
extern SDL_Texture* tex_tree;

extern SDL_Texture* tex_stroybat;
extern SDL_Texture* tex_gunner;

extern SDL_Texture* tex_cash;
extern SDL_Texture* tex_flamethr;

extern SDL_Texture* tex_dog;
extern SDL_Texture* tex_bank;

extern SDL_Texture* tex_tank;
extern SDL_Texture* tex_camp;
//extern int camera_x;
//extern int camera_y;

enum ScrollDirection {SCROLL_LEFT, SCROLL_RIGHT, SCROLL_UP, SCROLL_DOWN};

extern bool map_scroll;
extern ScrollDirection scroll_direction;

void KeyUp (SDL_Keycode key);



//extern SDL_Texture* tex_flag;

extern std::vector<SDL_Texture*> textures;

extern Map* mapp;

extern bool battle_mode;




SDL_Texture* LoadPNG(char *file);

bool Initialize();
bool Process();
void Free();

bool Timer();
void Draw();

void KeyBoardEvent();


#endif // _GAMECORE_H_
