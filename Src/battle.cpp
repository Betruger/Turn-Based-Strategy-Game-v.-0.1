#include "battle.h"

Button* skip_btn = NULL;
SDL_Texture* tex_skip = NULL;

SDL_Texture* cur1 = NULL;
SDL_Texture* cur2 = NULL;

CreatureRec cur_turn;

 int btl_lock = false;
int cur_dmg = 0;
CreatureRec cur_target;

double _min(double x, double y)
{
    if (x <= y) return x;
    else return y;
}

double _max(double x, double y)
{
    if (x >= y) return x;
    else return y;
}

Battle::Battle(Army* g_player, Army* g_enemy)
: player(g_player), enemy(g_enemy)
{
    srand(time(0));

     t = new Timer(20, false, false);
     t1 = new Timer(20, false, false);

       skip_btn = new Button(tex_skip, c_offset_x, bar_pos_y, button_width, 32, true);

       cur_target.cret = NULL;

       detail = NULL;

       mouse_down = false;
}

void Battle::DrawCursor(SDL_Renderer* renderer)
{

    SDL_ShowCursor(SDL_DISABLE);

     int px;
    int py;

//    POINT pt;
  //  GetCursorPos(&pt);

   // printf("%i-%i\n", pt.x, pt.y);
    //SDL_GetWMInfo();
  //  CString str;
   // RECT rect;
   //int cx = GetSystemMetrics(SM_CXFRAME);
   //int cy=GetSystemMetrics(SM_CXFRAME)+GetSystemMetrics(SM_CYCAPTION);

    //HWND hwnd;
    //hwnd = GetActiveWindow();

    //RECT rect1;
   // RECT rect2;

  //  POINT rt;
    //rt.x = rect.top;
   // rt.y = rect.bottom;
    //GetClient
    //GetClientRect(hwnd, &rect2);
    //GetWindowRect(hwnd, &rect1);

    //rect1.left += ((rect1.right-rect1.left)-(rect2.right-rect2.left)-3);
    //rect1.top += ((rect1.bottom-rect1.top)-(rect2.bottom-rect2.top)-3);

   // printf("%i-%i\n", rect1.left, rect1.top);
    //ClientToScreen(hwnd, &rt);
  //  str.Format("%d - %d",pt.x-rect.left,pt.y-rect.top);
   // AfxMessageBox(str);

    SDL_GetMouseState(&px, &py);

    SDL_Texture* cursor = NULL;

    SDL_Rect rect;

    if (IsEnemyCreatureSelected(px, py))
    {
       // printf("okk");
        cursor = cur2;

    }
    else cursor = cur1;

    rect.x = px;
    rect.y = py;
    rect.h = 24;
    rect.w = 16;

    SDL_RenderCopy(renderer, cursor, NULL, &rect);

}

bool Battle::NextTurn()
{
     for (int i = 0; i < army_size_x; i++)
    {
    for (int j = 0; j < army_size_y; j++)
    {
        Warrior* cr1 = player->GetUnit(i, j);
        Warrior* cr2 = enemy->GetUnit(i, j);
        if (cr1) cr1->NextTurn();
        if (cr2) cr2->NextTurn();
        }
    }

     return true;
}


BattleState Battle::Start()
{

    int init = 0;
    std::vector<CreatureRec> crets;

    if (!GetCrets(crets, init, true))
    {
        printf("Enemy win!\n");
        return ENEMY_WIN;
    }
    if (!GetCrets(crets, init, false))
    {
        printf("Player win!\n");
        player->DoneTurn();

        player->DeleteDeadChars();
        if (player->Leader() == NULL) return ENEMY_WIN;
        return PLAYER_WIN;
    }


    if (crets.size() > 0)
{
   // printf("okkk");
  int k = rand() % crets.size();
  //printf("Unit %i\n", k);
  cur_turn = crets[k];
}
else
{
    NextTurn();
    Start();
}

if (!cur_turn.player)
    {
    //if (!t)
    //{

  //  }
     t->Start();

   // printf("%i", t->Value());
    }

      skip_btn->Activate(false);

       if ((cur_turn.player) && (t1->State() == TIMER_STOPPED))
    {
        if (skip_btn)
        skip_btn->Activate(true);
    }


    return BATTLE;

}


CreatureRec Battle::FindTarget(Warrior* creature)    // refactoring from here
{
   // printf("ftarg");
 //  Army* arm = NULL;
 //   if (cur_turn.player) army = player;
 //   else army =

      std::vector<CreatureRec> crets;
    double danger = 0;

    //procedure only supports cells_x == 2

    bool hasunitsinfirstline = HasUnitsInFirstLine(true);
    bool hasunitsinfirstline_enemy =  HasUnitsInFirstLine(false);
 //   bool hasblockingunits = false;



  //  if (hasunitsinfirstline) printf("hasuninfirst\n");
  //  if (hasblockingunits) printf("hasblockun\n");

    int line_x = 0;
   // printf("ftarg");
   if (hasunitsinfirstline) line_x = 1;

    if (creature->Distance_Att() || cur_turn.slot_x == 1 || !hasunitsinfirstline_enemy)
    {
        int line_max_x = line_x;
        if (creature->Distance_Att())
        {
            line_x = 0;
            line_max_x = 1;// cells_x - 1;
        }

        for (int j = line_x; j <= line_max_x; j++)
        {
           for (int i = 0; i < 3; i++)
    {
          CreatureRec cr;
        cr.player = !cur_turn.player;
       // if (cr.player) cr.cret = player->GetUnit(1+cells_x*i);
         cr.cret = player->GetUnit(j, i);
       //  GetUnit(j+cells_x*i);
        cr.slot_x = j;//j+cells_x*i;
        cr.slot_y = i;

        if (cr.cret)
        {
            bool crt = false;


         //   printf("%i-%i \n", cur_turn.slot/cells_x, i);
    //    if (hasblockingunits && (((cur_turn.slot == 1) && (i==2)) || ((cur_turn.slot==5) && (i==0))) )
        if (!creature->Distance_Att() && abs((cur_turn.slot_y) - i) >= 2)
        {
          //  printf("yeee");
            //bool rev = false;
            int rev = 0;
            int rev1 = 0;
            if (cur_turn.slot_y > i) rev = 1;
            else rev1 = 1;

         //   printf ("%i-%i\n", rev, rev1);
           // rev = (cur_turn.slot/cells_x > i)
            for (int k = _min((cur_turn.slot_y), i)+rev; k <= _max((cur_turn.slot_y), i)-rev1; k++ )
            {
               // printf("%i\n", j);
               Warrior* erec = NULL;
                erec = player->GetUnit(1, k) ;
                if (erec && erec->HP() != 0)
                {
                  //  i++;
                    k = _max((cur_turn.slot_y), i);
                    crt = true;
                }
              //  else erec = player->GetUnit(1+cells_x*i);
            }
        }
      //      printf("2222");
      //  }
     //   else
     //   {
           // printf("2222");
          if (!crt && cr.cret->HP() != 0 && cr.cret->Damage() != 0)
            {
               //     printf("%f-%f\n", danger, ((double)cr.cret->Damage()/(double)cr.cret->HP()));
                    if (((double)cr.cret->Damage()/(double)cr.cret->HP()) == danger)
                    {
                        crets.push_back(cr);
                    }
                    if (((double)cr.cret->Damage()/(double)cr.cret->HP()) > danger)
                    {
                      //  printf("1111");
                        danger = ((double)cr.cret->Damage()/(double)cr.cret->HP());
                        crets.clear();
                        crets.push_back(cr);
                    }
            }
        }
    }
        }
    }
    //if (hasunitsinfirstline)
    //{
 //    for (int i = 0; i < cells_x*cells_y; i++)
 //   {

  //  }
   // }

  CreatureRec ct;
  ct.player = !cur_turn.player;
  ct.slot_x = 0;
  ct.slot_y = 0;
  ct.cret = NULL;

    if (crets.size() > 0)
 {
  int k = rand() % crets.size();
 // printf("Unit %i\n", k);

  ct.cret = crets[k].cret;
  ct.slot_x = crets[k].slot_x;
  ct.slot_y = crets[k].slot_y;
 }
 //else
 //{
    // printf("Error selecting creature to attack!\n");
 //    return ct;
 //}

  return ct;
}


BattleState Battle::Process()
{
   // printf("okk");

    t1->Process();

if (t->State() != TIMER_STARTED && t1->State() == TIMER_STOPPED && !btl_lock)
{
  BattleState st = Start();

if (st != BATTLE)
{
    SDL_ShowCursor(SDL_ENABLE);
    return st;
}
btl_lock = true;
  }

  t->Process();

    if (t1->State() != TIMER_STARTED && t->State() == TIMER_STOPPED && cur_turn.player == false)
    {
    // printf("okk");
     //   printf("111");
        if (!cur_turn.cret->TargetSelected() ||
            cur_turn.cret->Target().cret->HP() == 0)
        {
            cur_turn.cret->AssignTarget( FindTarget(cur_turn.cret) );
          //  cur_turn.cret->DoStrike();
        }
       // else if (cur_turn.cret->Target().cret->HP() == 0)
       // {
       //     cur_turn.cret->AssignTarget( FindTarget() );
       // }
        cur_turn.cret->DoneTurn();

       if (cur_turn.cret->TargetSelected())
       {
            cur_turn.cret->DoStrike();
                    cur_dmg = cur_turn.cret->Damage();
        cur_target = cur_turn.cret->Target();
                btl_lock = false;
                     t1->Start();
       }
        else
        {
             BattleState st = Start();

            if (st != BATTLE) return st;
             btl_lock = true;
        }

       //  if (!t1)
   // {
   //     t1 = new Timer(100, true, false);
   // printf("111");
   // }

      //  Start();
    }
    return BATTLE;
    }


bool Battle::IsEnemyCreatureSelected(int x, int y)
{


    if (cur_turn.player && x >= arm2_pos_x && y >= arm_pos_y)
    {
        CreatureRec cr;
        cr.slot_x = (x - arm2_pos_x)/(tile_size_x*3);
        cr.slot_y = (y - arm_pos_y)/(tile_size_y*3);

      //  printf("%i\n", x - arm2_pos_x);

        cr.cret = enemy->GetUnit( 1-cr.slot_x, cr.slot_y);
        cr.player = true;


 if (cr.cret)
        {
             // printf("%i-%i \n", cr.slot_x, cr.slot_y);
        //    printf("okk");
            bool hasunitsinfirstline = HasUnitsInFirstLine(true);
            bool hasunitsinfirstline_enemy = HasUnitsInFirstLine(false);

  int line_x = 0;
   // printf("ftarg");
   if (hasunitsinfirstline) line_x = 1;

               if (cr.cret->HP() == 0)
      //      printf("yee");
            return false;

            if (cur_turn.cret->Distance_Att())
            {
            return true;
            }

            //if (cr.cret->HP() != 0)
      //      printf("yee");
          //  return true;

         if (hasunitsinfirstline_enemy && ((cr.slot_x)==1))
                        return false;

         //   printf ("%i-%i\n", rev, rev1);
           // rev = (cur_turn.slot/cells_x > i)
          //  for (int j = _min((cur_turn.slot / cells_x), i)+rev; j <= _max((cur_turn.slot / cells_x), i)-rev1; j++ )
  //  printf("%i-%i\n", cur_turn.slot, cr.slot);
            if (cur_turn.slot_x == line_x) /*|| !hasunitsinfirstline)*/
            {

              if (abs((cur_turn.slot_y) - (cr.slot_y)) >= 2)
                {


                           int rev = 0;
                    int rev1 = 0;


                        if (cur_turn.slot_y > cr.slot_y) rev = 1;
                        else rev1 = 1;

            for (int j = _min((cur_turn.slot_y), (cr.slot_y))+rev; j <= _max((cur_turn.slot_y),
                                                (cr.slot_y))-rev1; j++ )
            {
                    if (enemy->GetUnit(1-cr.slot_x, j) &&
                        enemy->GetUnit(1-cr.slot_x, j)->HP() !=0)
                    return false;

            }
            }
                return true;

                }
         //   return true;
        }
    }
    return false;
}


bool Battle::GetCrets(std::vector<CreatureRec>& crets, int& init, bool player1)
{
    bool crets_exist = false;

     for (int i = 0; i < army_size_x; i++)
    {
    for (int j = 0; j < army_size_y; j++)
    {
       // printf("okk");
        CreatureRec cr;
        cr.player = player1;
        if (player1) cr.cret = player->GetUnit(i, j);
        else cr.cret = enemy->GetUnit(i, j);
        cr.slot_x = i;
        cr.slot_y = j;

        if (cr.cret)
        {
            if (cr.cret->HP() > 0)
            {
                crets_exist = true;
            if (!cr.cret->HasTurnDone())
            {
                if (cr.cret->Initiative() == init)
                {
                crets.push_back(cr);
                }
                if (cr.cret->Initiative() > init)
                {
                //printf("Unit added");
                crets.clear();
                init = cr.cret->Initiative();
                crets.push_back(cr);
                }
            }
        }
        }
     //   if (player[i])
     //   {
      //      if (player[i]->)
       // }
    }
    }

    return crets_exist;
}



bool Battle::Draw(SDL_Renderer* renderer)
{

    if (skip_btn)
    {
   // printf("11111");
    skip_btn->Draw(renderer);
    }

    player->DrawBattle(renderer, false, c_offset_x, arm_pos_y);

    enemy->DrawBattle(renderer, true, arm2_pos_x, arm_pos_y);

    int x1, y1;

    if (cur_turn.cret)
    {
        if (cur_turn.player)
        {
       //     printf("%i\n", cur_turn.slot);
            x1 = c_offset_x + tile_size_x * 3 * (cur_turn.slot_x) + 3;
            y1 = arm_pos_y + tile_size_y * 3 * (cur_turn.slot_y) + 3;

        }
         else
        {
              // printf("okidoki\n");
          //  printf("1rrr1");
            x1 = arm2_pos_x + tile_size_x * 3 * (1-cur_turn.slot_x) + 3;
                   y1 = arm_pos_y + tile_size_y * 3* (cur_turn.slot_y) + 3;
        }

    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 0);

        SDL_Rect rect {x1, y1, tile_size_x*3 - 6, tile_size_y*3 - 6};

       // DrawRect(surf, x1,
       //             y1,
       //             p_size_x - 6,
       //             p_st_size_y - 6,
       //              NULL, rcolor, 10 );
   //SDL_RenderDrawRect()
    SDL_RenderDrawRect(renderer, &rect);

    rect.x += 1;
    rect.y += 1;
    rect.h -= 2;
    rect.w -= 2;
    SDL_RenderDrawRect(renderer, &rect);

    int px, py;
    SDL_GetMouseState(&px, &py);

    if (detail && mouse_down)
        detail->DrawDetail(px, py, renderer);

    }

    DrawCursor(renderer);
}

void Battle::OnMouseMove(int x, int y)
{
     if (x >= c_offset_x && x < c_offset_x + tile_size_x*army_size_x*3 &&
          y >= arm_pos_y && y < arm_pos_y + tile_size_y*army_size_y*3 )
        {
                player->OnMouseDown(x - c_offset_x, y - arm_pos_y, SDL_BUTTON_RIGHT);
                detail=player->Detail();
                detail_side = true;
        }
    else if (x >= arm2_pos_x && x < arm2_pos_x + tile_size_x*army_size_x*3 &&
           y >= arm_pos_y && y < arm_pos_y + tile_size_y*army_size_y*3)
           {
               enemy->OnMouseDown(x - arm2_pos_x, y - arm_pos_y, SDL_BUTTON_RIGHT, true);
               detail=enemy->Detail();
               detail_side = false;
           }
    else
        detail = NULL;
}


bool Battle::OnMouseDown(int x, int y, int button)
{
    if (button == SDL_BUTTON_RIGHT)
        {
            mouse_down = true;
            OnMouseMove(x, y);
        }
    if (button == SDL_BUTTON_LEFT)
        {
            detail = NULL;

            if (cur_turn.player && (t1->State() == TIMER_STOPPED))
            {
                 if( IsEnemyCreatureSelected(x, y) && x >= arm2_pos_x && y >= arm_pos_y)
                 {
                 //    printf("kkk");
            CreatureRec cr;
            cr.slot_x = (x - arm2_pos_x)/(tile_size_x*3);
            cr.slot_y = (y - arm_pos_y)/(tile_size_y*3);

      //  printf("%i\n", x - arm2_pos_x);

            cr.cret = enemy->GetUnit( 1-cr.slot_x, cr.slot_y);
            cr.player = true;

          //  cr.cret = enemy->GetUnit(cr.slot_x, cr.slot_y);

               if (cr.cret)
               {
                   if (cr.cret->HP() != 0)
                   {
                     //  printf("kkk");
                       cur_target = cr;
                       cr.cret->ReceiveDamage( cur_turn.cret->Damage() );
                       cur_turn.cret->DoneTurn();
                       cur_dmg = cur_turn.cret->Damage();
                       t1->Start();
                       btl_lock = false;

                   }
               }
                 }

                  if (skip_btn && skip_btn->Hit(x, y))
              {
                  cur_turn.cret->DoneTurn();
                  if (!Start()) return false;
                  btl_lock = true;
              }

            }
        }
}

bool Battle::OnMouseUp(int x, int y, int button)
 {
     //printf("det");
     if (button == SDL_BUTTON_RIGHT)
     {
     detail = NULL;
     //detail_item = NULL;
  //  player->ResetDetail();
   // enemy->ResetDetail();
   // inv->ResetDetail();

mouse_down = false;
     }

     return true;
 }

bool Battle::HasUnitsInFirstLine(bool c_player)
{
      for (int i = 0; i<3; i++)
    {
        Warrior* trec = NULL;
     //   Creature* trec_en = NULL;
       // if (cur_turn.player) trec = player->GetUnit(1+cells_x*i) ;
        if (c_player)  trec = player->GetUnit(1, i);
        else trec = enemy->GetUnit(1, i);
        if (trec && trec->HP() != 0) return true;
    }

    return false;
       //    trec_en = enemy->GetUnit(1+cells_x*i);
       // if (trec_en && trec_en->HP() != 0) hasunitsinfirstline_enemy = true;
}

