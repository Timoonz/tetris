#ifndef GAME_H
#define GAME_H

#include "glm/glm.hpp"
#include <vector>
#include <functional>
#include <random>

#include "models/terrain.h"
#include "models/tetrominos.h"
#include "object.h"
#include "game/forme.h"

//Une structure pour tracker tout les minos déjà posés
struct Block {
    glm::vec3 position;
    Forme* forme;
};

struct GridCoordinates {
    int x;
    int y;
    int z;
};

class Game
{
    public:
        Game();
        ~Game();
        void spawn_piece();
        void setShader(Shader* shader);
        bool needNewPiece;
        bool gameOver;

        //L'unique pièce qui tombe
        Forme* fallingPiece;

        //L'ensemble des minos déjà posés
        vector<Block> placedMinos;

        //Une fonction pour checker si une pièce (celle qui tombe)
        //rentre en collision avec celles déjà stackées et le bord du terrain
        bool checkCollision(Object* piece);

        //Une fonction pour bloquer une pièce une fois qu'elle est rentrée en collision avec une autre
        void lockPiece(Object* piece);





    private:

        Shader* shader;
        //Tableau pour tracker l'état du plateau
        //Si l'emplacement est vide, alors la case vaut 0, sinon elle vaut l'index du bloc
        int board[14][12];

        //Une fonction pour retourner les coordonnées sur la grille de chaque mino d'un tétromino
        vector<GridCoordinates> getPositionsMinos(Object* piece);

        bool detectFullLine(int y);
        void deleteFullLine(int y);
        void moveDownGame(int yDelete);
        void checkGameOver(vector<GridCoordinates> tetrominoGridCoordinates);
};

#endif // GAME_H
