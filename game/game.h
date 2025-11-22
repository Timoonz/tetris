#ifndef GAME_H
#define GAME_H

#include "glm/glm.hpp"
#include <vector>
#include <functional>
#include <random>

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

        //L'unique pièce qui tombe
        Object* fallingPiece;

        //Toutes les pièces qui sont déjà tombées dans le jeu
        vector<Object*> stackedPieces;

    private:
        vector<glm::vec3> getRandomTetromino();
};

#endif // GAME_H
