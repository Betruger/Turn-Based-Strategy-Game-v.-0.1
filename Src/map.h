#ifndef _MAP_H_
#define _MAP_H_

//#include <vector>
#include "entity.h"
#include "control.h"
#include "battle.h"


extern int gold;
//#include "math.h"

//int abs (int val);

extern int absl (int val);

enum Tile {TILE_NONE = 0, TILE_GRASS};

extern Army* cur_army;

extern Button* btn_turn;

extern Path* c_path;

extern Entity* cur_camp;

extern int start_x;
extern int start_y;
extern int end_x;
extern int end_y;

extern bool drag;
extern Warrior* drag_war;

class Map
{
    public:
    Map(int m_size_x, int m_size_y, std::vector<SDL_Texture*> m_textures);
    void Draw(SDL_Renderer* renderer);
    void AddArmy(Army* m_ar) {armies.push_back(m_ar);};
    void AddObstacle( int pos_x, int pos_y, SDL_Texture* p_tex) {
        Obstacle* m_ob = new Obstacle(pos_x, pos_y, p_tex);
        entities.push_back(m_ob);
        tiles_obstacl[m_ob->X()][m_ob->Y()] = true;
        };
    void AddResource(Resource* m_res)
    {
        entities.push_back(m_res);
        tiles_obstacl[m_res->X()][m_res->Y()] = true;
    }
    void AddResourceBuilding(ResourceBuilding* m_res)
    {
        entities.push_back(m_res);
        tiles_obstacl[m_res->X()][m_res->Y()] = true;
    }
    void AddCamp(Camp* cmp)
    {
        entities.push_back(cmp);
        tiles_obstacl[cmp->X()][cmp->Y()] = true;
    }

    int CameraX() {return cam_x;};
    int CameraY() {return cam_y;};
    //bool BattleBegins() {return battle_begins;};

    void OnMouseDown(int m_x, int m_y, int button);
     void OnMouseUp(int m_x, int m_y, int button);
      void OnMouseMove(int m_x, int m_y);

    void SetCamera(int c_x, int c_y) {cam_x = c_x; cam_y = c_y;};

     Path* NextNode(Path* p, PathDirection p_d, int end_x, int end_y);
     Path* FindPath();

     bool Process();

     int Size_X() {return size_x;};
     int Size_Y() {return size_y;};

    protected:
    int size_x;
    int size_y;
    int cam_x;
    int cam_y;

    Tile** tiles;

    bool** tiles_opened;
    bool** tiles_obstacl;

    std::vector<SDL_Texture*> textures;
    int tex_number;

    std::vector<Army*> armies;
    std::vector<Army*>::iterator armies_it;

    std::vector<Entity*> entities;
    std::vector<Entity*>::iterator entities_it;

    Battle* battle;

    //bool battle_begins;

};


#endif // _MAP_H_
