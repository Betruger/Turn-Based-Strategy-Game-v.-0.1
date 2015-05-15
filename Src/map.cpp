#include "map.h"

int gold = 1000;

 Army* cur_army = NULL;

 Path* c_path = NULL;

 Entity* cur_camp = NULL;

 Button* btn_turn = NULL;

 int start_x = 0;
 int start_y = 0;

 int end_x = 0;
 int end_y = 0;

 bool drag = false;
 Warrior* drag_war = NULL;
 int drag_slot_x = 0;
 int drag_slot_y = 0;

 int absl (int val) {if (val > 0) return val;
                   else return -val;};

 Path* Map::NextNode(Path* p, PathDirection p_d, int end_x, int end_y)
 {
     int xd;
     int yd;
     if (p_d == PATH_DOWN)
        yd = 1;
     else if (p_d == PATH_UP)
        yd = -1;
     else yd = 0;

     if (p_d == PATH_RIGHT)
        xd = 1;
     else if (p_d == PATH_LEFT)
        xd = -1;
     else xd = 0;

   //  if (p->End_X() == end_x && p->End_Y() == end_y)
   //  {
   //      return p;
   //  }
 // printf("oughta");
  //printf("%i", p->End_X());
 // printf ("man");


  //printf("%i-%i, %i-%i", p->End_X() + xd, c_x, p->End_Y() + yd, c_y);

  //if(cells[(p->End_Y() + yd)*c_x + p->End_X() + xd] == CELL_NONE)
 //   printf("1");

  // if (p_d == PATH_DOWN)
      //if ( (p->End_X() + xd >= 0) && (p->End_X() + xd < c_x) && (p->End_Y() + yd >= 0) && (p->End_Y() + yd < c_y) &&
    //      cells[(p->End_Y() + yd)*c_x + p->End_X() + xd] == CELL_NONE && (!p->NodeExists(p->End_X()+xd, p->End_Y()+yd)))
    if ( (p->End_X() + xd >= 0) &&
        (p->End_X() + xd < size_x) &&
        (p->End_Y() + yd >= 0) &&
        (p->End_Y() + yd < size_y))
    {

         // tiles[p->End_X() + xd][(p->End_Y() + yd)*c_x + ] == CELL_NONE &&

       // (!(cells_opened[(p->End_Y() + yd)*c_x + p->End_X() + xd])))
       if
       ((!(tiles_opened[p->End_X()+xd][p->End_Y()+yd])) &&
       !(tiles_obstacl[p->End_X()+xd][p->End_Y()+yd]))
     {
       //  printf("1");
    //   printf("%i-%i \n", p->End_X() + xd, p->End_Y() + yd);
    // cells_opened[(p->End_Y() + yd)*c_x + p->End_X() + xd] = true;
    tiles_opened[p->End_X()+xd][p->End_Y()+yd] = true;

         p->AddNode(p->End_X() + xd, p->End_Y() + yd);
     //    printf("2");
       //  p = NextNode(p);
       return p;
     }
     else if (p->End_X() +xd  == end_x && p->End_Y() + yd == end_y)
      {
          for (entities_it = entities.begin(); entities_it < entities.end();
          entities_it++)
          {
           //  if ((*entities_it)->isResource())
           //    printf("%i-%i \n", (*entities_it)->X(), p->End_X() + xd);

              if (((*entities_it)->isResource() || (*entities_it)->isResourceBuilding() ||
              (*entities_it)->isCamp()) &&
                  (*entities_it)->X() == p->End_X() + xd &&
                (*entities_it)->Y() == p->End_Y() + yd  )
              {
                    //printf("truetrue");
                   tiles_opened[p->End_X()+xd][p->End_Y()+yd] = true;
                    p->AddNode(p->End_X() + xd, p->End_Y() + yd);
              return p;
              }
          }
      }

    }
    //  printf("3");

     return NULL;
 }



Path* Map::FindPath()
{


   // tiles = new Tile*[m_size_x];
   //   tiles_opened = new bool*[size_x];

      for (int i = 0; i < size_x; i++)
      {
        //  tiles[i] = new Tile[m_size_y];
    //      tiles_opened[i] = new bool[size_y];
          for (int j = 0; j < size_y; j++)
          {
         //     tiles[i][j] = TILE_NONE;
              tiles_opened[i][j] = false;
          }
      }


      Path* p = new Path(start_x, start_y);
     std::list<Path*> paths_p;
     std::list<Path*>::iterator paths_iter;

     tiles_opened[start_x][start_y] = true;

    // printf ("ok");

     paths_p.push_back(p);
     for (paths_iter = paths_p.begin(); paths_iter != paths_p.end();
               /*paths_iter++*/)
               {
              //    printf("ups %i-%i\n", (*paths_iter)->End_X(), (*paths_iter)->End_Y());

                   if ((*paths_iter) != NULL)
                   {
                    //   printf("ok");
                       if ((*paths_iter)->End_X() == end_x && (*paths_iter)->End_Y() == end_y)
                       {
                           return (*paths_iter);
                       }
                    //   printf("ok");

                       Path* p1 = new Path(*paths_iter);
                       p1 = NextNode(p1, PATH_LEFT, end_x, end_y);

                 //      if ()

                       //if (p1)
                   //    printf("ok")

                       Path* p2 = new Path(*paths_iter);
                       p2 = NextNode(p2, PATH_RIGHT, end_x, end_y);

                      // printf("ppo");

                     //  printf("ppo");

                       Path* p3 = new Path(*paths_iter);
                       p3 = NextNode(p3, PATH_DOWN, end_x, end_y);

                       Path* p4 = new Path(*paths_iter);
                       p4 = NextNode(p4, PATH_UP, end_x, end_y);

                     //  (*paths_iter) = NextNode(*paths_iter, PATH_UP);
                       // printf("ok");


                        if (p1)
                        {
                            paths_p.push_back (p1);
                         //   paths_iter = paths_p.begin();
                        }

                        if (p2)
                        {
                     //       p2->PrintInfo();
                            paths_p.push_back (p2);
                        //    paths_iter = paths_p.begin();

                        }
                         if (p3)
                         {
                             paths_p.push_back (p3);
                          //   paths_iter = paths_p.begin();
                         }

                         if (p4)
                            paths_p.push_back (p4);

                     //         if ((*paths_iter) == NULL)
          //             {
                            delete (*paths_iter);
                            paths_p.erase(paths_iter);


                            paths_iter = paths_p.begin();
                       //    paths_iter--;
                      // }

                       //  printf("%i\n", paths_p.size());

                   // Path* p1 = new Path(p);
                  //  p1 = NextNode();
                   }
                   else paths_iter++;
               }
    return NULL;
    // p = NextNode(p);
}




Map::Map(int m_size_x, int m_size_y, std::vector<SDL_Texture*> m_textures)
: size_x(m_size_x), size_y(m_size_y), textures(m_textures), battle(NULL),
cam_x(0), cam_y(0)//, battle_begins(false)
{
      tiles = new Tile*[m_size_x];
      tiles_opened = new bool*[m_size_x];
      tiles_obstacl = new bool*[m_size_x];

      for (int i = 0; i < m_size_x; i++)
      {
          tiles[i] = new Tile[m_size_y];
          tiles_opened[i] = new bool[m_size_y];
           tiles_obstacl[i] = new bool[m_size_y];

          for (int j = 0; j < m_size_y; j++)
          {
              tiles[i][j] = TILE_NONE;
              tiles_opened[i][j] = false;
              tiles_obstacl[i][j] = false;
          }
      }
    if (tex_turn) btn_turn = new Button(tex_turn, 500, 400, 64, 32, true);

}


void Map::Draw(SDL_Renderer* renderer)
{
    if (battle)
    {
    battle->Draw(renderer);


    return;
    }

if (font)
{
    std::string str = "";

     str.append( "Деньги: " );
     str.append( toStr(gold) );

     _DrawText(renderer, str.c_str(), 500, 10);
}
    // if (!battle_mode)

//}


    int fst_tile_x = cam_x/tile_size_x;
    int fst_tile_y = cam_y/tile_size_y;

    int fst_tile_offset_x = cam_x%tile_size_x;
    int fst_tile_offset_y = cam_y%tile_size_y;

     SDL_Rect src_rect{0, 0, 32, 32};

     SDL_Rect dest_rect{0, 0, 32, 32};

     for (int i = 0; i < scr_tiles_x; i++)
     {
         for (int j = 0; j < scr_tiles_y; j++)
         {
            if (i == 0)
            {
                src_rect.x = fst_tile_offset_x;
                src_rect.w = tile_size_x - fst_tile_offset_x;
                dest_rect.x = 0;
                //dest_rect.w =
                //src_rect.y = fst_tile_offset_y;
            }
            else
            {
                src_rect.x = 0;
                src_rect.w = 32;
                dest_rect.x = (tile_size_x - fst_tile_offset_x) + (i-1)*tile_size_x;
            }

             if (j == 0)
            {
                src_rect.y = fst_tile_offset_y;
                src_rect.h = tile_size_y - fst_tile_offset_y;
                dest_rect.y = 0;
                //dest_rect.w =
                //src_rect.y = fst_tile_offset_y;
            }
            else
            {
                src_rect.y = 0;
                src_rect.h = 32;
                dest_rect.y = (tile_size_y - fst_tile_offset_y) + (j-1)*tile_size_y;
            }

            dest_rect.w = src_rect.w;
            dest_rect.h = src_rect.h;
            // dest_rect.x = i*tile_size_x;
            // dest_rect.y = j*tile_size_y;
             SDL_RenderCopy(renderer, textures[tiles[fst_tile_x+i][fst_tile_y+j]], &src_rect, &dest_rect);
         }
     }

     for (entities_it = entities.begin(); entities_it < entities.end(); entities_it++)
     {
         (*entities_it)->Draw(renderer, cam_x, cam_y);
     }

      for (armies_it = armies.begin(); armies_it < armies.end(); armies_it++)
     {
         (*armies_it)->Draw(renderer, cam_x, cam_y);
     }

     btn_turn->Draw(renderer);



     //c_path->Draw(renderer, cam_x, cam_y);

     if (cur_army)
     {
           cur_army->DrawDetail(renderer);

         if (drag_war)
         {
             if (drag)
             {
             int px, py;
    SDL_GetMouseState(&px, &py);
             drag_war->DrawIcon(px, py, renderer, 1);
             }
             else
             {
                  int px, py;
    SDL_GetMouseState(&px, &py);
    drag_war->DrawDetail(px, py, renderer);
             }
         }

            if (c_path )
     {
        for (int i = 1; i < c_path->Nodes(); i++)
        {
            PathNode pn = c_path->GetPathNode(i);


            bool red_color = false;
            for (armies_it = armies.begin(); armies_it < armies.end(); armies_it++)
            {

                     //       printf("%i \n", (*armies_it)->Color());
              //  if ((*armies_it)->Color() != 0 )
               //     printf("%i-%i %i-%i \n", pn.x, (*armies_it)->X(), pn.y, (*armies_it)->Y());

                if ( ((*armies_it)->Color() != 0 ) && (( pn.x == (*armies_it)->X() &&
                    ( (pn.y == (*armies_it)->Y() - 1) || (pn.y == (*armies_it)->Y() + 1))) ||
                    ( pn.y == (*armies_it)->Y() &&
                    ( (pn.x == (*armies_it)->X() - 1) || (pn.x == (*armies_it)->X() + 1))))


                     )
                       {
                      //     printf("redd");
                           red_color = true;
                       } //red_color = true;

            }


            if (i <= cur_army->Turns())
            {
                if (red_color) DrawOnMap(renderer, cam_x, cam_y, path_red, 32, 32, pn.x, pn.y);
                else DrawOnMap(renderer, cam_x, cam_y, path_green, 32, 32, pn.x, pn.y);
            }
            else DrawOnMap(renderer, cam_x, cam_y, path_grey, 32, 32, pn.x, pn.y);


        }
     }



     }

     if (cur_camp)
        cur_camp->DrawScreen(renderer);
}


bool Map::Process()
{
    if (battle)
    {
        if (battle->Process() != BATTLE)
        {
            if (battle->Process() == PLAYER_WIN)
            {
                for (armies_it = armies.begin(); armies_it < armies.end(); armies_it++)
                {
                    if (*armies_it == battle->Enemy())
                    {
                        cur_army->Heroe() -> AddExp ( battle->Enemy()->Exp() );
                            delete (*armies_it);
                            armies.erase(armies_it);
                    }
                }
            }
            else
            {
                return false;
            }
            battle = NULL;
        }
       // if (battle->Process())
    }

    return true;
}

void Map::OnMouseUp(int m_x, int m_y, int button)
{
    if (battle)
        battle->OnMouseUp(m_x, m_y, button);

          if (cur_army && m_x < map_detail_x + tile_size_x*army_size_x &&
        m_y > map_detail_y && m_y < map_detail_y + tile_size_y*army_size_y && drag)
    {
        int slot_x = (m_x-map_detail_x)/tile_size_x;
        int slot_y = (m_y-map_detail_y)/tile_size_y;

        cur_army->ExchangeWarrior(slot_x, slot_y, drag_slot_x, drag_slot_y);

    //    drag = false;

     // Warrior* war_temp = cur_army->GetUnit(slot_x, slot_y);
       // drag_slot_x = slot_x;
      //  drag_slot_y = slot_y;
       // if (drag_war) drag = true;
    }

    drag = false;
    drag_war = NULL;

    return;
}

void Map::OnMouseMove(int m_x, int m_y)
{
    if (battle)
        battle->OnMouseMove(m_x, m_y);
   // else if (cur_army)

}

void Map::OnMouseDown(int m_x, int m_y, int button)
{

    if (cur_camp)
    {
  //  printf("okkk");
       if (button == 1)
       {
        cur_camp->OnMouseDown(m_x, m_y);
        gold = cur_camp->Money();
       }
       else cur_camp = NULL;
    }


    if (m_x > map_detail_x - 20)
    {

        if (btn_turn->Hit(m_x, m_y) && button == 1)
    {
        for (armies_it = armies.begin(); armies_it < armies.end(); armies_it++)
        {
            if ((*armies_it)->Color() == 0)
            (*armies_it)->NextTurn();

        }
        for (entities_it = entities.begin(); entities_it < entities.end(); entities_it++)
        {
            if ((*entities_it)->isResourceBuilding() && (*entities_it)->Color() == 0)
            {
              //  printf("okok\n");
                gold += 100;
            }
        }
    }

    if (cur_army && m_x < map_detail_x + tile_size_x*army_size_x &&
        m_y > map_detail_y && m_y < map_detail_y + tile_size_y*army_size_y)
    {
        int slot_x = (m_x-map_detail_x)/tile_size_x;
        int slot_y = (m_y-map_detail_y)/tile_size_y;

        drag_war = cur_army->GetUnit(slot_x, slot_y);
        drag_slot_x = slot_x;
        drag_slot_y = slot_y;
        if (drag_war && button == 1) drag = true;
    }
    }
    else
    {

 int fst_tile_x = (m_x+cam_x)/tile_size_x;
    int fst_tile_y = (m_y+cam_y)/tile_size_y;

  //  printf("%i-%i \n", fst_tile_x, fst_tile_y);

    int fst_tile_offset_x = (m_x+cam_x)%tile_size_x;
    int fst_tile_offset_y = (m_y+cam_y)%tile_size_y;

    //int cell_x = m_x / tile_size_x;
    //int cell_y = m_y / tile_size_y;

    if (battle)
    {
        battle->OnMouseDown(m_x, m_y, button);
        return;
    }
//printf("%i \n", button);
    //printf("%i-%i \n", cell_x, cell_y);
    if (button == 3)
    {
        cur_army = NULL;
        if (c_path)
        {
            delete c_path;
            c_path = NULL;
        }
    }
    else if (!cur_camp)
    {

    for (armies_it = armies.begin(); armies_it < armies.end(); armies_it++)
    {
        if ((*armies_it)->X() == fst_tile_x && (*armies_it)->Y() == fst_tile_y && (*armies_it)->Color() == 0)
            {
                cur_army = (*armies_it);
                return;
              //  printf("ok");
            }
    }
        if (cur_army && fst_tile_x < size_x && fst_tile_y < size_y && c_path == NULL)
        {
          //  printf("ok");
            start_x = cur_army->X();
            start_y = cur_army->Y();
            end_x = fst_tile_x;
            end_y = fst_tile_y;
            c_path = FindPath();

            //if (c_path)
           // c_path->Draw();

            }
            else if (c_path)
            {
            if (c_path->End_X() == fst_tile_x && c_path->End_Y() == fst_tile_y)
            {
                bool enf_turns = false;
                int turns = 0;
                if (c_path->Nodes() <= cur_army->Turns())
                {
                    enf_turns = true;
                    turns = c_path->Nodes() - 1;
                }
                else
                {
                    enf_turns = false;
                    turns = cur_army->Turns();
                }
               // bool intersect = false;

                for (int i =0; i < turns; i++)
                {
                  //  printf("%i \n", turns);
                    PathNode pn = c_path->GetPathNode(i);

                     for (armies_it = armies.begin(); armies_it < armies.end(); armies_it++)
            {

                     //       printf("%i \n", (*armies_it)->Color());
              //  if ((*armies_it)->Color() != 0 )
               //     printf("%i-%i %i-%i \n", pn.x, (*armies_it)->X(), pn.y, (*armies_it)->Y());

                if ( ((*armies_it)->Color() != 0 ) && (( pn.x == (*armies_it)->X() &&
                    ( (pn.y == (*armies_it)->Y() - 1) || (pn.y == (*armies_it)->Y() + 1))) ||
                    ( pn.y == (*armies_it)->Y() &&
                    ( (pn.x == (*armies_it)->X() - 1) || (pn.x == (*armies_it)->X() + 1)))))
                    {
                        cur_army->SetX(pn.x);
                        cur_army->SetY(pn.y);
                        cur_army->Go(i);
                        delete c_path;
                        c_path = NULL;
                        i = turns;
                    }
                }
                }

                if (c_path)
                {
                if (enf_turns)
                {
                cur_army->SetX(c_path->End_X());
                cur_army->SetY(c_path->End_Y());
               // cur_army->Go(c_path->Nodes());
                }
                else
                {
                cur_army->SetX(c_path->GetPathNode(cur_army->Turns()).x);
                cur_army->SetY(c_path->GetPathNode(cur_army->Turns()).y);
               // cur_army->Go(cur_army->Turns());
                }
                cur_army->Go(turns);

            delete c_path;
            c_path=NULL;
                }

                 for (entities_it = entities.begin(); entities_it < entities.end();
          entities_it++)
          {
              if (cur_army->X() == (*entities_it)->X() &&
                  cur_army->Y() == (*entities_it)->Y())
              {
                    if ((*entities_it)->isResource())
                    {
                        gold+= (*entities_it)->Amount();
                        delete (*entities_it);
                        entities.erase(entities_it);
                    }
                    else if ((*entities_it)->isResourceBuilding() || (*entities_it)->isCamp())
                    {
                  //  printf("%i-%i \n", (cur_army->X()), (*entities_it)->X());
                        (*entities_it)->SetColor(0);
                        if ((*entities_it)->isCamp())
                        {
                    //    printf("okkkk");
                            cur_camp = (*entities_it);
                            cur_camp->SetCurArmy(cur_army, gold);
                        }
                    }
              }
          }


             for (armies_it = armies.begin(); armies_it < armies.end(); armies_it++)
    {
        if (*armies_it != cur_army && (( cur_army->X() == (*armies_it)->X() &&
                    ( (cur_army->Y() == (*armies_it)->Y() - 1) || (cur_army->Y() == (*armies_it)->Y() + 1))) ||
                    ( cur_army->Y() == (*armies_it)->Y() &&
                    ( (cur_army->X() == (*armies_it)->X() - 1) || (cur_army->X() == (*armies_it)->X() + 1)))  ))
        {
            battle = new Battle(cur_army, *armies_it);
            battle->Start();
       // battle_begins = true;
          //  printf("hooya!");
        }
    }
            }


        }

    }
    }
}
