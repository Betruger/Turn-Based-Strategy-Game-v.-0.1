#ifndef _BATTLE_H_
#define _BATTLE_H_

#include "entity.h"
#include "control.h"
#include <cstdlib>
//#include "windows.h"
#include "timer.h"
#include <ctime>

enum BattleState {BATTLE, PLAYER_WIN, ENEMY_WIN};

extern int btl_lock;
extern int cur_dmg;
extern CreatureRec cur_target;

double _min(double x, double y);

double _max(double x, double y);


extern CreatureRec cur_turn;

extern Button* skip_btn;

extern SDL_Texture* tex_skip;

extern SDL_Texture* cur1;
extern SDL_Texture* cur2;

const int c_offset_x = 50;
const int c_offset_y = c_offset_x;
const int lab_offset = 10;

const int lab_offset_y = 10;

const int s_offset = 20; // offset between commander portraits and armies
const int bar_offset = 20;

//const int lab_length = 200;


const int mid_offset = 100;

const int button_width = 64;

const int lab_length = (mid_offset/2) + tile_size_x*(army_size_x-1) - 1.5*lab_offset;
const int lab1_pos_x = c_offset_x+tile_size_x+lab_offset;
const int lab2_pos_x = lab1_pos_x+lab_length+lab_offset;
const int port2_pos_x = lab2_pos_x + lab_length+lab_offset;

const int arm2_pos_x = c_offset_x + tile_size_x*3*army_size_x + mid_offset;

const int arm_pos_y = c_offset_y + p_st_size_y + s_offset;

const int bar_pos_y = arm_pos_y + tile_size_y*army_size_y*3 + bar_offset;
const int bar2_pos_x = c_offset_x + button_width + lab_offset;

class Battle
{
     public:
         Battle(Army* g_player, Army* g_enemy);
         bool Draw(SDL_Renderer* renderer);
         void DrawCursor(SDL_Renderer* renderer);

         bool OnMouseDown(int x, int y, int button);
         void OnMouseMove(int x, int y); // Определять щелчок по воину
         bool OnMouseUp(int x, int y, int button);

         BattleState Process();
          bool NextTurn();

          BattleState Start();

          bool GetCrets(std::vector<CreatureRec>& crets, int& init, bool player1);

        bool IsEnemyCreatureSelected(int x, int y);

        CreatureRec FindTarget(Warrior* creature) ;

        bool HasUnitsInFirstLine(bool c_player);

        Army* Enemy() {return enemy;};

         protected:
            Army* player;
            Army* enemy;

            bool detail_side;
            bool mouse_down;

            Timer* t;
            Timer* t1;

            Warrior* detail;

           // Button* skip_btn;
};




#endif // _BATTLE_H_
