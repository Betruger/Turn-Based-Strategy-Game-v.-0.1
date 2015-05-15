#include "gamecore.h"


bool quit = false;
int time_current;
int time_passed;
int timer = 40;

//int gold = 1000;

SDL_Window* sdl2window = NULL;
SDL_Renderer* renderer = NULL;

SDL_Texture* tex_grass = NULL;
SDL_Texture* tex_soldier = NULL;
SDL_Texture* tex_tree = NULL;

SDL_Texture* tex_stroybat = NULL;
SDL_Texture* tex_gunner = NULL;

SDL_Texture* tex_cash = NULL;

SDL_Texture* tex_flamethr = NULL;
SDL_Texture* tex_dog = NULL;
SDL_Texture* tex_bank = NULL;

SDL_Texture* tex_tank = NULL;

SDL_Texture* tex_camp = NULL;
//int camera_x = 0;
//int camera_y = 0;

bool map_scroll = false;
ScrollDirection scroll_direction;

bool battle_mode = false;

std::vector<SDL_Texture*> textures;

Map* mapp = NULL;

SDL_Texture* LoadPNG(char *file)
{
    FILE *f;
     SDL_Surface* surface;


    // SDL_RWops *rwop = SDL_RWFromFile(file, "rb");

  //   surface = IMG_LoadPNG_RW(rwop);

    SDL_RWops *rw;
    f = fopen(file, "rb");

   // printf("11");
        if(!f) {
        //char *str;
        //RInt n;
        printf("Couldn't load %s: %s\n", file, SDL_GetError());
        //MessageBox(NULL, str, "Error", NULL);
        return NULL;
  }

 // rw = SDL_RWFromFP(f, SDL_FALSE);

 // if (!rw)
 // {
 //     printf("Problem with rw");
 //     return false;
 // }

    surface = IMG_Load(file);

     if (!surface)
    {
       // printf("11");
        //char *str = NULL;
        printf("Couldn't load image %s", file);
        return NULL;
    }

   Uint32 colorwh = SDL_MapRGB(surface->format, 255, 255, 255);

   SDL_SetColorKey (surface, SDL_TRUE, colorwh);
  //      SDL_FreeRW(rw);
    //SDL_FreeRW(rwop);
  fclose(f);

  SDL_Texture* tex = SDL_CreateTextureFromSurface(renderer, surface);
  SDL_FreeSurface(surface);
    //}
    return tex;
}

bool Initialize()
{

    std::setlocale(LC_CTYPE, "Russian");

   if(TTF_Init()<0)
        printf("Error ttf");

	  if((SDL_Init(SDL_INIT_EVERYTHING) < 0)) {
        printf("Error Initializing SDL: %s\n", SDL_GetError());
        return false;
    }

	sdl2window = SDL_CreateWindow("Age Of Stroibat", SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, scr_width, scr_height, SDL_WINDOW_SHOWN);

	 if (sdl2window == NULL)
    {
        printf("Couldn't set %d*%d video mode\n", scr_width, scr_height);
        return false;
    }

	renderer = SDL_CreateRenderer (sdl2window, -1, 0);


	font=TTF_OpenFont("arial.ttf", 16);
    if (font == NULL)
    {
        printf("Unable to load font \n");
//        return false;
}

	tex_grass = LoadPNG("grass.png");
	//tex_grass = SDL_CreateTextureFromSurface(renderer, s_grass);

	textures.push_back(tex_grass);

	SDL_Texture* flagtex1 = LoadPNG("flag1.png");

	SDL_Texture* flagtex2 = LoadPNG("flag2.png");

	flag_textures.push_back(flagtex1);
	flag_textures.push_back(flagtex2);



tex_soldier = LoadPNG("soldier.png");
	//tex_soldier = SDL_CreateTextureFromSurface(renderer, s_army);

	tex_tree = LoadPNG("tree.png");
	tex_stroybat = LoadPNG("stroybat.png");
	tex_gunner = LoadPNG("gunner.png");
	tex_cash = LoadPNG("cash.png");
	tex_skip = LoadPNG("button_skip.png");
	cur1 = LoadPNG("cur1.png");
	cur2 = LoadPNG("cur2.png");
	path_green = LoadPNG("path_green.png");
	path_red = LoadPNG("path_red.png");
	path_grey = LoadPNG("path_grey.png");
	tex_turn = LoadPNG("button_turn.png");
    tex_flamethr = LoadPNG("flamethrower.png");
    tex_dog = LoadPNG("dog.png");
    tex_bank = LoadPNG("bank.png");
    tex_tank = LoadPNG("tank.png");
    tex_camp = LoadPNG("camp.png");
    tex_buy = LoadPNG("button_buy.png");

	mapp = new Map(40, 40, textures);


	//tex_tree = SDL_CreateTextureFromSurface(renderer, s_tree);
       Heroe* w3 = new Heroe("Огнеметчик", tex_flamethr, 150, 70, 150, 50, 0);

    Army* ar1 = new Army(2, 2, "Герой 1", tex_soldier, 20, 20, 0, flagtex1, w3, 1, 1);

    Warrior* w1 = new Warrior("Стройбат", tex_stroybat, 100, 70, 100, 30);
    Warrior* w2 = new Warrior("Автоматчик", tex_gunner, 80, 50, 80, 30, true);


    ar1->AddWarrior(1, 0, w1);
    ar1->AddWarrior(0, 0, w2);
   // ar1->AddWarrior(1, 1, w3);

    mapp->AddArmy(ar1);

      Warrior* e1 = new Warrior("Стройбат", tex_stroybat, 100, 70, 100, 30);

    Army* ar2 = new Army(10, 15, "Enemy1", tex_soldier, 20, 20, 1, flagtex2, e1, 1, 0, 500);


    Warrior* e2 = new Warrior("Автоматчик", tex_gunner, 80, 50, 80, 30, true);

   // ar2->AddWarrior(1, 0, e1);
    ar2->AddWarrior(0, 0, e2);

    mapp->AddArmy(ar2);

    //Obstacle* ob1 = new Obstacle(6, 6, tex_tree);
     mapp->AddObstacle(0, 6, tex_tree);
    mapp->AddObstacle(1, 6, tex_tree);
    mapp->AddObstacle(2, 6, tex_tree);
    mapp->AddObstacle(3, 6, tex_tree);
    mapp->AddObstacle(4, 6, tex_tree);
    mapp->AddObstacle(5, 6, tex_tree);
     mapp->AddObstacle(6, 6, tex_tree);
    mapp->AddObstacle(7, 6, tex_tree);
    mapp->AddObstacle(8, 6, tex_tree);
    mapp->AddObstacle(9, 6, tex_tree);
 mapp->AddObstacle(9, 0, tex_tree);
 // mapp->AddObstacle(9, 1, tex_tree);
 // mapp->AddObstacle(9, 2, tex_tree);
//  mapp->AddObstacle(9, 3, tex_tree);
 // mapp->AddObstacle(9, 4, tex_tree);
  mapp->AddObstacle(9, 5, tex_tree);
  mapp->AddObstacle(9, 6, tex_tree);
  mapp->AddObstacle(9, 7, tex_tree);
  mapp->AddObstacle(9, 8, tex_tree);
  mapp->AddObstacle(9, 9, tex_tree);
  mapp->AddObstacle(9, 10, tex_tree);
  mapp->AddObstacle(9, 11, tex_tree);
 mapp->AddObstacle(10, 11, tex_tree);
  mapp->AddObstacle(11, 11, tex_tree);
   mapp->AddObstacle(12, 11, tex_tree);
    mapp->AddObstacle(13, 11, tex_tree);
     mapp->AddObstacle(14, 11, tex_tree);
      mapp->AddObstacle(16, 11, tex_tree);
      mapp->AddObstacle(17, 11, tex_tree);
      mapp->AddObstacle(18, 11, tex_tree);
       mapp->AddObstacle(19, 11, tex_tree);

  for (int i = 0; i < 20; i++)
    mapp->AddObstacle(20, i, tex_tree);


  Warrior* dog1 = new Warrior("Собака", tex_dog, 40, 90, 40, 30);
   Warrior* dog2 = new Warrior("Собака", tex_dog, 40, 90, 40, 30);
    Warrior* dog3 = new Warrior("Собака", tex_dog, 40, 90, 40, 30);

  Army* d1 = new Army(8, 2, "Dogs", tex_dog, 0, 0, 1, flagtex2, dog1, 0, 0, 300);
  d1->AddWarrior(1, 0, dog2);
  d1->AddWarrior(1, 1, dog3);

  mapp->AddArmy(d1);


  Warrior* dog4 = new Warrior("Собака", tex_dog, 40, 90, 40, 30);
  Warrior* dog5 = new Warrior("Собака", tex_dog, 40, 90, 40, 30);

  Army* d4 = new Army(16, 3, "Dogs", tex_dog, 0, 0, 1, flagtex2, dog4, 0, 0, 200);

  d4->AddWarrior(0, 2, dog5);
  mapp->AddArmy(d4);

  Resource* res2 = new Resource(16, 4, tex_cash, 200);
  mapp->AddResource(res2);


  Warrior* tank2 = new Warrior("Танк", tex_tank, 250, 40, 250, 60, false);
  Warrior* auto1 = new Warrior("Автоматчик", tex_gunner, 80, 50, 80, 30, true);

  Warrior* auto2 = new Warrior("Автоматчик", tex_gunner, 80, 50, 80, 30, true);

  Army* tarmy = new Army(15, 11, "HERR", tex_tank, 0, 0, 2, flagtex2, tank2, 1, 1, 1000);
  tarmy->AddWarrior(0, 0, auto1);
  tarmy->AddWarrior(0, 2, auto2);


  mapp->AddArmy(tarmy);


    Resource* res1 = new Resource(8, 1, tex_cash, 100);
    mapp->AddResource(res1);

    ResourceBuilding* rb1 = new ResourceBuilding("Bank", 12, 2, tex_bank, 1);
    mapp->AddResourceBuilding(rb1);

    Warrior* tank1 = new Warrior("Танк", tex_tank, 250, 40, 250, 60, false);
    Army* t1 = new Army(12, 3, "Танк", tex_tank, 0, 0, 2, flagtex2, tank1, 0, 1, 700);
    mapp->AddArmy(t1);

    Camp* c1 = new Camp("Лагерь", 16, 8, tex_camp, 1);
    c1->AddWarrior(w1, 300);
    c1->AddWarrior(w2, 500);

    mapp->AddCamp(c1);

	return true;
}

bool Timer()
{
    int cam_speed = 7;
    int camera_x = mapp->CameraX();
    int camera_y = mapp->CameraY();

    if (!battle_mode)
    {
        if (map_scroll)
        {
            if (scroll_direction == SCROLL_LEFT && camera_x > 0) mapp->SetCamera(camera_x-= cam_speed, camera_y);
            else if (scroll_direction == SCROLL_RIGHT && camera_x < mapp->Size_X()*tile_size_x - scr_height) mapp->SetCamera(camera_x+cam_speed, camera_y);
            else if (scroll_direction == SCROLL_UP && camera_y > 0) mapp->SetCamera(camera_x, camera_y-=cam_speed);
            else if (scroll_direction == SCROLL_DOWN && camera_y < mapp->Size_Y()*tile_size_y - scr_height) mapp->SetCamera(camera_x, camera_y+=cam_speed);
        }
        if (!(mapp->Process()))
            return false;
        //if (mapp->BattleBegins())
        //battle_mode = true;
    }
    else
    {
       // printf("okk");
       // mapp->Process();
    }

    return true;
}

bool Process()
{
    KeyBoardEvent();
	if (quit) return true;

    time_current = SDL_GetTicks();

	if (time_current - time_passed >= timer)
    {
        time_passed += timer;
        if (!Timer()) return true;
        Draw();
    }

    return false;
}


void KeyUp (SDL_Keycode key)
{
     switch (key)
                {
                    case SDLK_LEFT:
                    {
                        map_scroll = false;
                        //scroll_direction = SCROLL_LEFT;
                    }
                    break;
                    case SDLK_RIGHT:
                    {
                        map_scroll = false;
                        //scroll_direction = SCROLL_RIGHT;
                    }
                    break;
                    case SDLK_UP:
                    {
                        map_scroll = false;
                        //scroll_direction = SCROLL_UP;
                    }
                    break;
                    case SDLK_DOWN:
                    {
                        map_scroll = false;
                        //scroll_direction = SCROLL_DOWN;
                    }
                    break;
}
}

void KeyBoardEvent()
 {
     SDL_Event event;

        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                {
                    quit = true;
                }
                break;
             case SDL_MOUSEBUTTONDOWN:
                {
                    mapp->OnMouseDown(event.button.x, event.button.y, event.button.button);
                    //MouseButtonEvent(event.button.x, event.button.y);
                }
                break;
             case SDL_MOUSEBUTTONUP:
                {
                    mapp->OnMouseUp(event.button.x, event.button.y, event.button.button);
                }
             case SDL_MOUSEMOTION:
                {
                    mapp->OnMouseMove(event.button.x, event.button.y);
        //MouseMotionEvent(event.button.x, event.button.y);
                }
                break;
             case SDL_KEYUP:
             {
                KeyUp(event.key.keysym.sym);
             }
               break;
            case SDL_KEYDOWN:
            {
                switch (event.key.keysym.sym)
                {
                    case SDLK_LEFT:
                    {
                        map_scroll = true;
                        scroll_direction = SCROLL_LEFT;
                    }
                    break;
                    case SDLK_RIGHT:
                    {
                        map_scroll = true;
                        scroll_direction = SCROLL_RIGHT;
                    }
                    break;
                    case SDLK_UP:
                    {
                        map_scroll = true;
                        scroll_direction = SCROLL_UP;
                    }
                    break;
                    case SDLK_DOWN:
                    {
                        map_scroll = true;
                        scroll_direction = SCROLL_DOWN;
                    }
                    break;
                }
            }
            break;
            }
        }
 }


void Draw()
{
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    	SDL_RenderClear(renderer);

    mapp->Draw(renderer);

    	SDL_RenderPresent(renderer);
}


void Free()
{

    SDL_Quit();
}
