#include "path.h"

SDL_Texture* path_green = NULL;
SDL_Texture* path_red = NULL;
SDL_Texture* path_grey = NULL;

const int tile_size_x = 32;
 const int tile_size_y = 32;

 const int scr_tiles_x = 15;
const int scr_tiles_y = 15;

void DrawOnMap(SDL_Renderer* renderer, int camera_x, int camera_y, SDL_Texture* texture,
      int size_x, int size_y, int pos_x, int pos_y)
{

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
                dest_rect.x = tile_size_x - size_x;
     }
     else
     {
         src_rect.x = 0;
                src_rect.w = size_x;
                dest_rect.x = (tile_size_x - fst_tile_offset_x) + (pos_x-fst_tile_x-1)*tile_size_x + (tile_size_x-size_x);
     }

     if (pos_y == fst_tile_y)
     {
       // src_rect.x = fst_tile_offset.x;
          src_rect.y = fst_tile_offset_y;
                src_rect.h = tile_size_y - fst_tile_offset_y;
                dest_rect.y = (tile_size_y - size_y);
     }
     else
     {
         src_rect.y = 0;
        src_rect.h = size_y;
        dest_rect.y = (tile_size_y - fst_tile_offset_y) + (pos_y-fst_tile_y-1)*tile_size_y + (tile_size_y-size_y);
     }

     dest_rect.w = src_rect.w;
     dest_rect.h = src_rect.h;



     SDL_RenderCopy(renderer, texture, &src_rect, &dest_rect);
}
}


Path::Path(int start_x, int start_y)
{
    PathNode st (start_x, start_y);

    nodes.push_back(st);
}

// void Path::Draw(SDL_Renderer* renderer, int screen_x, int screen_y)
 //{

 //}

bool Path::AddNode(int node_x, int node_y)
{
    PathNode node (node_x, node_y);

    nodes.push_back(node);

    return true;
}

PathNode Path::GetPathNode(unsigned int node)
{
    PathNode pn (0, 0);
    if (node < nodes.size())
    {
        pn.x = nodes[node].x;
        pn.y = nodes[node].y;
    }
    return pn;
  //  else
  //  {
   //     pn.x = 0;
   //     pn.y = 0;
   // }
}

Path::Path(Path* p)
{
    nodes.clear();
    for (int i = 0; i < p->Nodes(); i++)
    {
       // printf("okido\n");
        nodes.push_back(p->GetPathNode(i));
    }
}

bool Path::NodeExists(int node_x, int node_y)
{
    for (nodes_it = nodes.begin(); nodes_it < nodes.end(); nodes_it++)
    {
        if ((*nodes_it).x == node_x && (*nodes_it).y == node_y)
            return true;
    }
    return false;
}

int Path::Node_X(unsigned int x)
{
    if (x < nodes.size())
        return nodes[x].x;
    else return 0;
}

int Path::Node_Y(unsigned int x)
{
    if (x < nodes.size())
        return nodes[x].y;
    else return 0;
}

 void Path::PrintInfo()
 {
     printf("NewPAth\n");
      for (nodes_it = nodes.begin(); nodes_it < nodes.end(); nodes_it++)
    {
        printf("%i-%i ", (*nodes_it).x, (*nodes_it).y);
    }
  //  return false;
 }
