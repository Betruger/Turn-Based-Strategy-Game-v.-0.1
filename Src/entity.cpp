#include "entity.h"

std::vector<SDL_Texture*> flag_textures;

 SDL_Texture* tex_turn = NULL;
 SDL_Texture* tex_buy = NULL;

//const int army_size_x = 2;
//const int army_size_y = 3;

TTF_Font* font = NULL;

std::string toStr(int t)
{
    std::string nstr;

    if (t < 0)
    nstr.push_back('-');
    else if (t == 0)
    nstr.push_back('0');

    int t1 = t;
    while (t1 != 0)
    {
        nstr.insert(nstr.begin(), 0x30 + (t1 % 10));
        t1/=10;
    }

    return nstr;
    //append(nstr);
}





std::string UintToStr(uint16_t t)
{
    std::string nstr;

   // if (t < 0)
   // nstr.push_back('-');

    int t1 = t;
    while (t1 != 0)
    {
        nstr.insert(nstr.begin(), 0x30 + (t1 % 10));
        t1/=10;
    }

    return nstr;
    //append(nstr);
}
//const char& RString::operator[] ( size_t pos ) const
//{
//    return str[pos];
//}



void _DrawText(SDL_Renderer* renderer, const char* text, int pos_x, int pos_y)
{
    SDL_Color color={0, 0, 0};

SDL_Surface *surface=NULL;

//char t[] = "Текст";
//CharToOem(t,t);

surface = TTF_RenderUTF8_Solid (font, text, color);
//surface = TTF_RenderUTF8_Solid (font, text, color);

SDL_Rect position = {pos_x,pos_y,surface->w,surface->h};

SDL_Texture* tex = SDL_CreateTextureFromSurface(renderer, surface);

SDL_FreeSurface(surface);


	//DrawText32(fnt, renderer, "Деньги:", 32, 10, 10, 10, 0, TEXT_CENTERED, 1);

	//DrawText32(10, 30, "Дата: %i %s %i", day, months[month], year);

	//DrawText32(50, 10, "Выбор города: ");

 SDL_RenderCopy(renderer, tex, NULL, &position);
}




Entity::Entity(int e_pos_x, int e_pos_y, SDL_Texture* e_tex)
: pos_x (e_pos_x), pos_y(e_pos_y), tex(e_tex)
{

}

void Entity::Draw(SDL_Renderer* renderer, int camera_x, int camera_y)
{

DrawOnMap(renderer, camera_x, camera_y, tex, 32, 32, pos_x, pos_y);
/*
	 SDL_Rect src_rect{0, 0, 32, 32};

     SDL_Rect dest_rect{pos_x*tile_size_x, pos_y*tile_size_y, 32, 32};

     int fst_tile_x = camera_x / tile_size_x;
     int fst_tile_y = camera_y / tile_size_y;

     int fst_tile_offset_x = camera_x % tile_size_x;
     int fst_tile_offset_y = camera_y % tile_size_y;

     if (pos_x >= fst_tile_x && pos_x < fst_tile_x + scr_tiles_x &&
      pos_y >= fst_tile_y && pos_y < fst_tile_y + scr_tiles_y)
{
//printf("ok");
     if (pos_x == fst_tile_x)
     {
       // src_rect.x = fst_tile_offset.x;
          src_rect.x = fst_tile_offset_x;
                src_rect.w = tile_size_x - fst_tile_offset_x;
                dest_rect.x = 0;
     }
     else
     {
         src_rect.x = 0;
                src_rect.w = 32;
                dest_rect.x = (tile_size_x - fst_tile_offset_x) + (pos_x-fst_tile_x-1)*tile_size_x;
     }

     if (pos_y == fst_tile_y)
     {
       // src_rect.x = fst_tile_offset.x;
          src_rect.y = fst_tile_offset_y;
                src_rect.h = tile_size_y - fst_tile_offset_y;
                dest_rect.y = 0;
     }
     else
     {
         src_rect.y = 0;
        src_rect.h = 32;
        dest_rect.y = (tile_size_y - fst_tile_offset_y) + (pos_y-fst_tile_y-1)*tile_size_y;
     }

     dest_rect.w = src_rect.w;
     dest_rect.h = src_rect.h;

     SDL_RenderCopy(renderer, tex, &src_rect, &dest_rect);
     }*/

}

Obstacle::Obstacle(int e_pos_x, int e_pos_y, SDL_Texture* e_tex)
: Entity(e_pos_x, e_pos_y, e_tex)
{

}

Resource::Resource(int e_pos_x, int e_pos_y, SDL_Texture* e_tex, int e_amount)
: Entity(e_pos_x, e_pos_y, e_tex), amount(e_amount)
{

}


Army::Army(int e_pos_x, int e_pos_y, char* e_name, SDL_Texture* e_tex, int e_maxturns,
         int e_turns, int e_color, SDL_Texture* e_flag_tex,
          Warrior* e_leader, int e_leader_x, int e_leader_y, int e_exp)
: Entity(e_pos_x, e_pos_y, e_tex), name(e_name), maxturns(e_maxturns), turns(e_turns), color(e_color),
flag_tex(e_flag_tex), detail(NULL), exp(e_exp), leader(e_leader)
{
    for (int i = 0; i < army_size_x; i++)
    {
        for (int j = 0; j < army_size_y; j++)
        {
            warriors[i][j] = NULL;
        }
    }

    warriors[e_leader_x][e_leader_y] = e_leader;
}


void Army::AddWarrior(Warrior* w_war)
{
     for (int i = 0; i < army_size_x; i++)
    {
        for (int j = 0; j < army_size_y; j++)
        {
            if (!warriors[i][j])
            {
            warriors[i][j] = w_war;
            return;
            }
        }
        }
}

bool Army::Full()
{
    for (int i = 0; i < army_size_x; i++)
    {
        for (int j = 0; j < army_size_y; j++)
        {
            if (!warriors[i][j]) return false;
        }


    }

}

 void Army::DeleteDeadChars()
 {
      for (int i = 0; i < army_size_x; i++)
    {
        for (int j = 0; j < army_size_y; j++)
        {
            if (warriors[i][j] && (warriors[i][j]->HP() == 0))
                {
                    if (warriors[i][j] == leader)
                        leader = NULL;
                    delete warriors[i][j];
                    warriors[i][j] = NULL;
                }
        }


    }
 }

 void Army::HealChars()
 {
      for (int i = 0; i < army_size_x; i++)
    {
        for (int j = 0; j < army_size_y; j++)
        {
            if (warriors[i][j])
                warriors[i][j]->Heal(20);
        }


    }
 }

 void Army::DoneTurn()
 {
       for (int i = 0; i < army_size_x; i++)
    {
        for (int j = 0; j < army_size_y; j++)
        {
            if (warriors[i][j])
                warriors[i][j]->NextTurn();
        }
    }
 }


void Army::Draw(SDL_Renderer* renderer, int camera_x, int camera_y)
{
    Entity::Draw(renderer, camera_x, camera_y);

     //SDL_Rect src_rect{0, 0, 8, 8};

     //SDL_Rect dest_rect{pos_x*tile_size_x+24, pos_y*tile_size_y+24, 8, 8};

DrawOnMap(renderer, camera_x, camera_y, flag_tex, 8, 8, pos_x, pos_y);

/*



     SDL_Rect src_rect{0, 0, 8, 8};

     SDL_Rect dest_rect{pos_x*tile_size_x + 24, pos_y*tile_size_y + 24, 8, 8};

     int fst_tile_x = camera_x / tile_size_x;
     int fst_tile_y = camera_y / tile_size_y;

     int fst_tile_offset_x = camera_x % tile_size_x;
     int fst_tile_offset_y = camera_y % tile_size_y;

     if (pos_x >= fst_tile_x && pos_x < fst_tile_x + scr_tiles_x &&
      pos_y >= fst_tile_y && pos_y < fst_tile_y + scr_tiles_y)
{
//printf("ok");
     if (pos_x == fst_tile_x)
     {
       // src_rect.x = fst_tile_offset.x;
          src_rect.x = fst_tile_offset_x;
                src_rect.w = tile_size_x - fst_tile_offset_x;
                dest_rect.x = 24;
     }
     else
     {
         src_rect.x = 0;
                src_rect.w = 8;
                dest_rect.x = (tile_size_x - fst_tile_offset_x) + (pos_x-fst_tile_x-1)*tile_size_x + 24;
     }

     if (pos_y == fst_tile_y)
     {
       // src_rect.x = fst_tile_offset.x;
          src_rect.y = fst_tile_offset_y;
                src_rect.h = tile_size_y - fst_tile_offset_y;
                dest_rect.y = 24;
     }
     else
     {
         src_rect.y = 0;
        src_rect.h = 8;
        dest_rect.y = (tile_size_y - fst_tile_offset_y) + (pos_y-fst_tile_y-1)*tile_size_y + 24;
     }

     dest_rect.w = src_rect.w;
     dest_rect.h = src_rect.h;



     SDL_RenderCopy(renderer, flag_tex, &src_rect, &dest_rect);*/

}


void Army::ExchangeWarrior(int slot1_x, int slot1_y, int slot2_x, int slot2_y)
{
    Warrior* temp = warriors[slot1_x][slot1_y];

    warriors[slot1_x][slot1_y] = warriors[slot2_x][slot2_y];
    warriors[slot2_x][slot2_y] = temp;

}

bool Army::OnMouseDown(int x, int y, int button, bool reversed)
{
   // printf("%i-%i \n", x, y);

    if (button == SDL_BUTTON_RIGHT)
    {
    int cell_x;
    if (reversed) cell_x = army_size_x - 1 - x/(tile_size_x*3);
        else cell_x = x/(tile_size_x*3);
    int cell_y = y/(tile_size_y*3);

  //  printf ("%i - %i\n", cell_x, cell_y);

    if (cell_x >= 0 && cell_y >= 0 && cell_x < army_size_x && cell_y < army_size_y && warriors[cell_x][cell_y] )
    {
        detail = warriors[cell_x][cell_y];
       // crt[cell_x+cell_y*cells_x]->ToggleDetailed(true);
    }
    else
    detail = NULL;
    }
}


 void Army::DrawDetail(SDL_Renderer* renderer)
 {
         if (font)
         {
         _DrawText(renderer, name, map_detail_x, 80);

         std::string str = "";
         str.append("Ходов: ");
        str.append(toStr(turns));
        str.append("/");
        str.append(toStr(maxturns));

        _DrawText(renderer, str.c_str(), map_detail_x, 100);

}
        for (int i = 0; i < army_size_x; i++)
        {
            for (int j = 0; j < army_size_y; j++)
            {
               if (warriors[i][j]) warriors[i][j]->DrawIcon(map_detail_x+i*tile_size_x, map_detail_y+j*tile_size_y, renderer, 1);
            }
        }

 }

 void Army::DrawBattle(SDL_Renderer* renderer, bool reversed, int x, int y)
 {
    for (int i = 0; i < army_size_y; i++)
    {
        for (int j = 0; j < army_size_x; j++)
        {
             int k;

            if (!reversed) k = j; else k = army_size_x -1 - j;

            if (warriors[j][i])
            {
            warriors[j][i]->DrawIcon(x+tile_size_x*k*3, y+tile_size_y*i*3, renderer, 3);
            warriors[j][i]->DrawLifeBar(x+tile_size_x*k*3, y+tile_size_y*i*3+p_st_size_y*3, renderer);
            }
        }
    }
 }

 void Army::AddWarrior(int w_x, int w_y, Warrior* w_unit)
 {
     if (w_x < army_size_x && w_y < army_size_y)
     {
         warriors[w_x][w_y] = w_unit;
     }
 }

 Warrior* Army::GetUnit(int slot_x, int slot_y)
 {
    if (slot_x > 1 || slot_y > 2 || slot_x < 0 || slot_y < 0) return NULL;
   // printf("okill");
    if (warriors[slot_x][slot_y]) return (warriors[slot_x][slot_y]);
    return NULL;
 }


 Warrior::Warrior(Warrior* w_war)
: name(w_war->name), tex(w_war->tex), maxhp(w_war->maxhp), init(w_war->init), hp(w_war->hp),
distance_att(w_war->distance_att), damage(w_war->damage), turn_done(false)
{

}


 Warrior::Warrior(char* w_name, SDL_Texture* w_tex, int w_maxhp, int w_init, int w_hp,
                 int w_damage,   bool w_distance_att )
 : name(w_name), tex(w_tex), maxhp(w_maxhp), init(w_init), hp(w_hp), turn_done(false),
 distance_att(w_distance_att), damage(w_damage)
 {
     //printf("%i \n", hp);
     target.cret = NULL;
 }

 void Warrior::DoStrike()
{
    if (target.cret) target.cret->ReceiveDamage(damage);
}

void Warrior::ReceiveDamage(int damag)
{
    hp-=damag;
    if (hp < 0) hp = 0;
}

 void Warrior::DrawDetail(int screen_x, int screen_y, SDL_Renderer* renderer)
 {
   //  printf("%i-%i \n", screen_x, screen_y);
   // printf("%i \n", hp);

    SDL_Rect rect;

    if (screen_x + detail_x < scr_width) rect.x = screen_x; else rect.x = screen_x - detail_x;
    if (screen_y + detail_y < scr_height) rect.y = screen_y; else rect.y = screen_y - detail_y;
    if (rect.x < 0) rect.x = 0;
    if (rect.y < 0) rect.y = 0;

    rect.w = detail_x;
    rect.h = detail_y;

   //  Uint32 color;

//color = SDL_MapRGB(screen->format, 200, 200, 200);

   //  Uint32 bcolor = SDL_MapRGB()
SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);

SDL_RenderDrawRect(renderer, &rect);

rect.x += 1;
rect.y += 1;
rect.w -= 2;
rect.h -= 2;

SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);

SDL_RenderFillRect(renderer, &rect);

   Warrior::DrawIcon(rect.x, rect.y, renderer, 3);
   // SDL_FillRect(screen, &rect, color);

   if (font)
   {
   _DrawText(renderer, name, rect.x + 100, rect.y);

     std::string str = "";
    str.append("Здоровье: ");
    str.append(toStr(hp));
    str.append("/");
    str.append(toStr(maxhp));

    _DrawText(renderer, str.c_str(), rect.x + 100, rect.y + 20);

    std::string str1 = "";
    str1.append("Урон: ");
    str1.append(toStr(damage));

    _DrawText(renderer, str1.c_str(), rect.x + 100, rect.y + 40);

    std::string str2 = "";
    str2.append("Инициатива: ");
    str2.append(toStr(init));

    _DrawText(renderer, str2.c_str(), rect.x + 100, rect.y + 60);

}
 }


 void Warrior::DrawIcon(int screen_x, int screen_y, SDL_Renderer* renderer, int w_size)
 {
 //int k_size = 1;
   // if (w_size) k_size = 3;

  //  printf("%i %i\n", screen_x, screen_y);
   if (hp == 0) SDL_SetTextureColorMod(tex, 0, 0, 0);
   else SDL_SetTextureColorMod(tex, 255, 255, 255);

      SDL_Rect src_rect{0, 0, tile_size_x*w_size, tile_size_y*w_size};

     SDL_Rect dest_rect{screen_x, screen_y, tile_size_x*w_size, tile_size_y*w_size};

    SDL_RenderCopy(renderer, tex, &src_rect, &dest_rect);

 }

 void Warrior::DrawLifeBar(int screen_x, int screen_y, SDL_Renderer* renderer)
 {
    Uint8 r, g, b, a;

    SDL_Rect rect2;

    if (hp > 2*maxhp/3)
    {
    a = 0;
    r = 0;
    g = 198;
    b = 0;
   //     color = SDL_MapRGB()0, 0, 198, 0);
    }
    else if (hp > 1*maxhp/3)
    {
    a = 0;
    r = 255;
    g = 255;
    b = 113;
        //color = SDL_MapRGB(0, 255, 255, 113);
    }
    else
    {
    a = 0;
    r = 255;
    g = 0;
    b = 0;
        //color = SDL_MapRGB(0, 255, 0, 0);
    }

    rect2.x = screen_x;
    rect2.y = screen_y;
     rect2.w = hp*tile_size_x*3/maxhp;
    rect2.h = len_y;

   // SDL_Render

    SDL_SetRenderDrawColor(renderer, r, g, b, a);

    SDL_RenderFillRect(renderer, &rect2);



   //     SDL_FillRect(screen, &rect2, color);

 }

 Heroe::Heroe( char* w_name, SDL_Texture* w_tex, int w_maxhp, int w_init, int w_hp,
           int w_damage, int w_xp, bool w_distance_att)
           : Warrior(w_name, w_tex, w_maxhp, w_init, w_hp, w_damage, w_distance_att), xp(w_xp),
           max_xp(1000), level(1)
 {

 }


 void Heroe::AddExp (int w_exp)
 {
    xp+= w_exp;
    if (xp >= max_xp)
    {
        level+= 1;
        max_xp += level*1000;
        maxhp += 20;
        hp = maxhp;
    }

 }

 void Heroe::DrawDetail(int screen_x, int screen_y, SDL_Renderer* renderer)
 {
     Warrior::DrawDetail(screen_x, screen_y, renderer);

 SDL_Rect rect;

    if (screen_x + detail_x < scr_width) rect.x = screen_x; else rect.x = screen_x - detail_x;
    if (screen_y + detail_y < scr_height) rect.y = screen_y; else rect.y = screen_y - detail_y;
    if (rect.x < 0) rect.x = 0;
    if (rect.y < 0) rect.y = 0;

    rect.w = detail_x;
    rect.h = detail_y;

if (font)
{
      std::string str = "";
    str.append("Уровень: ");
    str.append(toStr(level));
   // str.append("/");
   // str.append(toStr(maxhp));

    _DrawText(renderer, str.c_str(), rect.x + 100, rect.y + 80);

    std::string str1 = "";
    str1.append("Эксп: ");
    str1.append(toStr(xp));
    str1.append("/");
    str1.append(toStr(max_xp));

    _DrawText(renderer, str1.c_str(), rect.x + 100, rect.y + 100);

    //std::string str2 = "";
   // str2.append("Initiative: ");
   // str2.append(toStr(init));

   // _DrawText(renderer, str2.c_str(), rect.x + 100, rect.y + 60);

}
 }


Building::Building(char* e_name, int e_pos_x, int e_pos_y, SDL_Texture* e_tex, int e_color)
: Entity(e_pos_x, e_pos_y, e_tex), color(e_color), name(e_name)
{

}


void Building::Draw(SDL_Renderer* renderer, int camera_x, int camera_y)
{
    Entity::Draw(renderer, camera_x, camera_y);
    DrawOnMap(renderer, camera_x, camera_y, flag_textures[color], 8, 8, pos_x, pos_y);
}

ResourceBuilding::ResourceBuilding(char* e_name, int e_pos_x, int e_pos_y, SDL_Texture* e_tex, int e_color)
: Building(e_name, e_pos_x, e_pos_y, e_tex, e_color)
{

}

void Camp::DrawScreen(SDL_Renderer* renderer)
{
SDL_SetRenderDrawColor(renderer, 255, 0, 0, 0);

        SDL_Rect rect {0, 0, 250, 480};

       // DrawRect(surf, x1,
       //             y1,
       //             p_size_x - 6,
       //             p_st_size_y - 6,
       //              NULL, rcolor, 10 );
   //SDL_RenderDrawRect()
    SDL_RenderFillRect(renderer, &rect);


int i = 0;
    for (war_sales_iter = war_sales.begin(); war_sales_iter < war_sales.end(); war_sales_iter++)
    {
        (*war_sales_iter).warrior->DrawIcon(50, 50+i*100, renderer, 2);

        std::string str;

        str.append("Стоимость: ");
        str.append(toStr((*war_sales_iter).cost));
        _DrawText(renderer, str.c_str(), 150, 50+i*100);

        if (cur_war.warrior == (*war_sales_iter).warrior)
        {
       // printf("%i \n", i);
        SDL_Rect rect1;
        rect1.x = 50;
        rect1.y = 50+i*100;
        rect1.w = tile_size_x*2;
        rect1.h = tile_size_y*2;

            SDL_SetRenderDrawColor(renderer, 0, 255, 0, 0);

            SDL_RenderDrawRect(renderer, &rect1);
        }
        i++;
    }

    buy_btn->Draw(renderer);

}


Camp::Camp(char* e_name, int e_pos_x, int e_pos_y, SDL_Texture* e_tex, int e_color)
: Building(e_name, e_pos_x, e_pos_y, e_tex, e_color), cur_army(NULL)
{
    cur_war.warrior = NULL;
    buy_btn = new Button(tex_buy, 50, 300, 64, 32, false);
   // exit_btn = new Button(tex_turn, 150, 300, 64, 32, false);
}

void Camp::OnMouseDown(int screen_x, int screen_y)
{
   int i = 0;

   if (buy_btn->Hit(screen_x, screen_y))
   {
        if (cur_army && cur_war.warrior && !cur_army->Full() && money >= cur_war.cost)
        {
            Warrior* w = new Warrior (cur_war.warrior);
            cur_army->AddWarrior(w);
            money -= cur_war.cost;
          //  printf("%i \n", cur_war.cost);
        }


   }
   //printf("hhhh");
    for (war_sales_iter = war_sales.begin(); war_sales_iter < war_sales.end(); war_sales_iter++) {
  //  printf("ok");
    if (screen_x > 50 && screen_x < 50+2*tile_size_x && screen_y > 50 + i*100 && screen_y < 50 + i*100 + tile_size_y*2)
    {
   // printf("ok");
        cur_war.warrior = (*war_sales_iter).warrior;
        cur_war.cost = (*war_sales_iter).cost;
    }
    i++;
}

}
