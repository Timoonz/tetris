#ifndef GAME_H
#define GAME_H

#include "glm/glm.hpp"
#include <vector>

#include "models/terrain.h"
#include "models/tetrominos.h"
#include "object.h"


class Game
{
    public:
        Game();
        ~Game();

        void spawn_piece();
        void spawn_terrain();

        bool needNewPiece;


        vector<Object*> pieces;

};

#endif // GAME_H
