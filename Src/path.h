#ifndef _PATH_H_
#define _PATH_H_

#include <stdio.h>
#include <vector>
#include "SDL.h"

extern SDL_Texture* path_green;
extern SDL_Texture* path_red;
extern SDL_Texture* path_grey;

extern const int scr_tiles_x;
extern const int scr_tiles_y;

extern const int tile_size_x;
extern const int tile_size_y;

enum PathDirection {PATH_DOWN, PATH_UP, PATH_LEFT, PATH_RIGHT};

struct PathNode
{
    PathNode(int p_x, int p_y) {x = p_x; y = p_y;};
    int x;
    int y;
};

void DrawOnMap(SDL_Renderer* renderer, int camera_x, int camera_y, SDL_Texture* texture,
      int size_x, int size_y, int pos_x, int pos_y);

class Path
{
      public:
      Path(int start_x, int start_y);
      Path(Path* p);
      bool AddNode(int node_x, int node_y);
      bool NodeExists(int node_x, int node_y);
      int End_X() {
        //  printf("%i", nodes.size());
          return (*(nodes.end()-1)).x;
          //printf("end");
          };
      int End_Y() {return (*(nodes.end()-1)).y;};
      int Nodes() {return nodes.size();};
      int Node_X(unsigned int x);
      int Node_Y(unsigned int x);
      PathNode GetPathNode(unsigned int node);
    //  void Draw(SDL_Renderer* renderer, int screen_x, int screen_y);


      void PrintInfo();

      protected:
      std::vector<PathNode> nodes;
      std::vector<PathNode>::iterator nodes_it;
};

#endif // _PATH_H_
