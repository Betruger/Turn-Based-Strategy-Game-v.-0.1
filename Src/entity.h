#ifndef _ENTITY_H_
#define _ENTITY_H_

#define army_size_x 2
#define army_size_y 3

//#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include <string>
#include <list>
#include "path.h"
#include "control.h"

class Army;

extern SDL_Texture* tex_turn;
extern SDL_Texture* tex_buy;

class Warrior;

struct CreatureRec
{
    bool player;
    Warrior* cret;
    int slot_x;
    int slot_y;
};

const int scr_width = 640;
const int scr_height = 480;

const int map_detail_x = 500;
const int map_detail_y = 140;

//extern const int army_size_x;
//extern const int army_size_y;

std::string toStr(int t);

void _DrawText(SDL_Renderer* renderer, const char* text, int pos_x, int pos_y);

extern TTF_Font* font;

extern const int tile_size_x;
extern const int tile_size_y;

const int lifebar_y = 10;

const int p_st_size_y = tile_size_y - lifebar_y;

const int len_y = 10;

const int detail_x = 250;
const int detail_y = 150;

extern std::vector<SDL_Texture*> flag_textures;

class Entity
{
    public:
    Entity(int e_pos_x, int e_pos_y, SDL_Texture* e_tex);
    virtual void Draw(SDL_Renderer* renderer, int camera_x, int camera_y);
    int X() {return pos_x;};
    int Y() {return pos_y;};
    void SetX(int e_x) {pos_x = e_x;};
    void SetY(int e_y) {pos_y = e_y;};
    virtual bool isResource() {return false;};
    virtual int Amount() {return 0;};
    virtual bool isResourceBuilding() {return false;};
    virtual bool isCamp() {return false;};
    virtual void SetColor(int e_color) {};
    virtual int Color() {return 0;};
    virtual void DrawScreen(SDL_Renderer* renderer) {};
    virtual void OnMouseDown(int screen_x, int screen_y) {};
    virtual void SetCurArmy(Army* c_army, int c_money) {};
    virtual int Money() {};

    protected:
    int pos_x;
    int pos_y;
    SDL_Texture* tex;
};


class Obstacle : public Entity
{
    public:
    Obstacle(int e_pos_x, int e_pos_y, SDL_Texture* e_tex);
};

class Resource : public Entity
{
    public:
    Resource(int e_pos_x, int e_pos_y, SDL_Texture* e_tex, int e_amount);
    bool isResource() {return true;};
    int Amount() {return amount;};

    protected:
    int amount;
};

class Building : public Entity
{
    public:
    Building(char* e_name, int e_pos_x, int e_pos_y, SDL_Texture* e_tex, int e_color);
    int Color() {return color;};
    void Draw(SDL_Renderer* renderer, int camera_x, int camera_y);
    void SetColor(int e_color) {color=e_color;};

    protected:
    int color;
    char* name;
};

class ResourceBuilding : public Building
{
    public:
    ResourceBuilding(char* e_name, int e_pos_x, int e_pos_y, SDL_Texture* e_tex, int e_color);
    bool isResourceBuilding() {return true;};

};

struct WarriorSale
{
    Warrior* warrior;
    int cost;
};


class Warrior
{
public:
    Warrior(char* w_name, SDL_Texture* w_tex, int w_maxhp, int w_init, int w_hp,
           int w_damage, bool w_distance_att = false );
    Warrior() {};
    Warrior(Warrior* w_war);

    virtual void AddExp(int w_exp) {};

    void DrawIcon(int screen_x, int screen_y, SDL_Renderer* renderer, int w_size);

    //void DrawBig(int screen_x, int screen_y, SDL_Renderer* renderer);

    void DrawLifeBar(int screen_x, int screen_y, SDL_Renderer* renderer);

   virtual void DrawDetail(int screen_x, int screen_y, SDL_Renderer* renderer) ;

    bool HasTurnDone () {return turn_done;};
     bool TargetSelected() {if (target.cret) return true; else return false;};

    int Initiative() {return init;};
    int HP() {return hp;};
    void NextTurn() {turn_done = false;};

    bool Distance_Att() {return distance_att;};
    int Damage() {return damage;};

    CreatureRec Target () {return target;};
    void AssignTarget(CreatureRec c_target) {target = c_target;};

    bool DoneTurn() {turn_done = true;};
    void DoStrike();
     void ReceiveDamage(int damag);

     void Heal(int hp_add)
     {
         hp+=hp_add;
         if (hp > maxhp) hp = maxhp;
     };

protected:
    char* name;
    SDL_Texture* tex;
    int maxhp;
    int init;
    int hp;
    int damage;

    CreatureRec target;
    bool turn_done;
    bool distance_att;

};


class Camp : public Building
{
    public:
    Camp(char* e_name, int e_pos_x, int e_pos_y, SDL_Texture* e_tex, int e_color);
    void AddWarrior(Warrior* e_war, int cost)
    {
        WarriorSale ws;
        ws.warrior = new Warrior(e_war);
        ws.cost = cost;
        war_sales.push_back(ws);
    };
    void DrawScreen(SDL_Renderer* renderer);
    bool isCamp() {return true;};
    void OnMouseDown(int screen_x, int screen_y);
    void SetCurArmy(Army* c_army, int c_money) {cur_army = c_army; money = c_money;};
    int Money() {return money;};

    protected:
    std::vector<WarriorSale> war_sales;
    std::vector<WarriorSale>::iterator war_sales_iter;

    WarriorSale cur_war;
    Army* cur_army;
    int money;




    Button* buy_btn;
    Button* exit_btn;


};


class Heroe : public Warrior
{
    public:
    Heroe(char* w_name, SDL_Texture* w_tex, int w_maxhp, int w_init, int w_hp,
           int w_damage, int w_xp, bool w_distance_att = false);
    void DrawDetail(int screen_x, int screen_y, SDL_Renderer* renderer);
    void AddExp (int w_exp);

    protected:
    int xp;
    int max_xp;
    int level;

};


class Army : public Entity
{
    public:
    Army(int e_pos_x, int e_pos_y, char* e_name, SDL_Texture* e_tex, int e_maxturns,
         int e_turns, int e_color, SDL_Texture* e_flag_tex,
         Warrior* e_leader, int e_leader_x, int e_leader_y, int e_exp = 0);
    void DrawDetail(SDL_Renderer* renderer);
    void AddWarrior(int w_x, int w_y, Warrior* w_unit) ;
    void Draw(SDL_Renderer* renderer, int camera_x, int camera_y);
    int Color() {return color;};
    Warrior* Heroe() {return leader;};

    Warrior* Detail() {return detail;};

void DoneTurn();

     void HealChars();

      void NextTurn() {turns = maxturns; HealChars();};

    void DeleteDeadChars() ;

    bool Full();

    void AddWarrior(Warrior* w_war);

    void DrawBattle(SDL_Renderer* renderer, bool reversed, int x, int y);

    Warrior* GetUnit(int slot_x, int slot_y);

    int Turns() {return turns;};
    void Go(int g_turns) {turns-=g_turns;};

    int Exp() {return exp;};

     bool OnMouseDown (int x, int y, int button, bool reversed = false);

     void ExchangeWarrior(int slot1_x, int slot1_y, int slot2_x, int slot2_y);

     Warrior* Leader() {return leader;};


    protected:
    char* name;
    int maxturns;
    int turns;
    Warrior* warriors[army_size_x][army_size_y];
    SDL_Texture* flag_tex;
    int color;

    Warrior* detail;

    Warrior* leader;
    int exp;
    //SDL_Texture* tex;
};


/*
class Soldier : public Entity
{
public:
    Soldier(int e_pos_x, int e_pos_y, char* e_name, int e_hp, int e_maxhp);

protected:
    char* name;
    int hp;
    int maxhp;
};*/



#endif // _ENTITY_H_
