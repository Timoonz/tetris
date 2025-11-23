#include "game.h"
#include "object.h"
#include "models/tetrominos.h"
#include "game/forme.h"

//Pour débugger
#include <iostream>

Game::Game() {
    //À l'initialisation, il n'y a pas de pièces qui tombent et de pièces déjà stackées
    fallingPiece = nullptr;
    //On initialise le tableau permettant de tracker les blocs stackés
    for (int x = 0; x < 12; x++){
        for (int y = 0; y < 14; y++){
            board[x][y] = 0;
        }
    }
    needNewPiece = true;
    gameOver = false;
}

Game::~Game() {
    delete fallingPiece;
}

void Game::spawn_piece() {
    std::pair<vector<glm::vec3>, PieceType> buffer_and_type = getRandomTetromino();
    glm::vec3 color = glm::vec3(
        (float)rand() / float(RAND_MAX),
        (float)rand() / float(RAND_MAX),
        (float)rand() / float(RAND_MAX));
    Forme* result = new Forme(buffer_and_type.first, buffer_and_type.second, color);
    result->object->position.y = 12.0f;
    result->object->position.x = 0.0f;
    //On stocke le résultat dans l'attribut "pieces" du jeu
    this->fallingPiece = result;
    this->needNewPiece = false;
};





bool Game::checkCollision(Object* piece){
    vector<GridCoordinates> tetrominoGridCoordinates = this->getPositionsMinos(piece);

    for(const GridCoordinates& coordinate : tetrominoGridCoordinates){
        int x_grid = coordinate.x;
        int y_grid = coordinate.y;
        int x_board = x_grid + 6;

        //On teste si la pièce touche le bas de la grille
        if (y_grid <= 0){
            return true;
        }

        //On teste si la pièce touche les bords
        if (x_board < 1 || x_board >= 11){
            return true;
        }

        //On check la collision avec les pièces déjà stackées
        //Seulement si on est dans les clous
        if (y_grid >= 0 && y_grid < 12) {
            if (x_board >= 0 && x_board < 12) {
                int cellValue = board[y_grid][x_board];
                if (cellValue != 0){
                    return true;
                }
            }
        }
    }

    return false;
}

void Game::lockPiece(Object* piece){
    vector<GridCoordinates> tetrominoGridCoordinates = getPositionsMinos(piece);

    //On met la pièce sur une coordonée y entière
    fallingPiece->object->position.y = round(fallingPiece->object->position.y);
    //En revanche si la pièce rentre en collision avec le bas du plateau, on la remet un cran au-dessus
    bool onFloor = false;
    for(const GridCoordinates& coordinate : tetrominoGridCoordinates){
        int y_grid = coordinate.y;
        if (y_grid == 0){
            onFloor = true;
            break;
        }
    }
    if (onFloor){
        for(GridCoordinates& coordinate : tetrominoGridCoordinates){
            coordinate.y += 1;
        }
        fallingPiece->object->position.y += 1.0f;
    }

    //On check pour savoir la piece provoque un game over
    checkGameOver(tetrominoGridCoordinates);
    //Le cas échéant, on arrête tout
    if (gameOver){
        return;
    }

    for(const GridCoordinates& coordinate : tetrominoGridCoordinates){

        int x_grid = coordinate.x;
        int y_grid = coordinate.y;
        int x_board = x_grid + 6;

        //On check les bords et on crée un nouveau block, que l'on met dans la liste des blocks placés
        if (y_grid >= 0 && y_grid < 12 && x_board >= 0 && x_board < 12){
            board[y_grid][x_board] = placedMinos.size() + 1;

            Block block;
            block.position = glm::vec3(x_grid, y_grid, 0);
            std::vector<glm::vec3> vertexBuffer = mino_creator(x_grid, y_grid, 0.0f);
            PieceType type = PieceType::MINO;
            glm::vec3 color = fallingPiece->color;
            Forme* forme = new Forme(vertexBuffer, type, color);

            block.forme = forme;
            placedMinos.push_back(block);
        }
    }

    //On scan pour savoir si une ligne est pleine
    for (int rang = 0; rang < 12; rang++){
        if (detectFullLine(rang)){
            // std::cout << "LINE " << rang << " FULL\n";
            deleteFullLine(rang);
            moveDownGame(rang);
            rang --; //On désincremente au cas où la ligne du dessus était pleine
        }
    }


    //On supprime la pièce qui tombe
    delete(fallingPiece);
    //Il n'y a plus de pièce qui tombe
    fallingPiece = nullptr;
    //On a beesoin d'une nouvelle pièce
    needNewPiece = true;
}


vector<GridCoordinates> Game::getPositionsMinos(Object* piece){
    int piece_x = (int)round(piece->position.x);
    int piece_y = (int)round(piece->position.y);

    vector<GridCoordinates> result;

    switch(piece->pieceType){
    case PieceType::LINE:
        result.push_back({piece_x,   piece_y, 0});
        result.push_back({piece_x+1, piece_y, 0});
        result.push_back({piece_x+2, piece_y, 0});
        result.push_back({piece_x+3, piece_y, 0});
        break;
    case PieceType::BLOCK:
        result.push_back({piece_x,   piece_y,   0});
        result.push_back({piece_x+1, piece_y,   0});
        result.push_back({piece_x+1, piece_y+1, 0});
        result.push_back({piece_x,   piece_y+1, 0});
        break;
    case PieceType::TEE:
        result.push_back({piece_x,   piece_y,   0});
        result.push_back({piece_x+1, piece_y,   0});
        result.push_back({piece_x+1, piece_y+1, 0});
        result.push_back({piece_x+2, piece_y,   0});
        break;
    case PieceType::RIGHT_SNAKE:
        result.push_back({piece_x,   piece_y,   0});
        result.push_back({piece_x+1, piece_y,   0});
        result.push_back({piece_x+1, piece_y+1, 0});
        result.push_back({piece_x+2, piece_y+1, 0});
        break;
    case PieceType::LEFT_SNAKE:
        result.push_back({piece_x+2, piece_y,   0});
        result.push_back({piece_x+1, piece_y,   0});
        result.push_back({piece_x+1, piece_y+1, 0});
        result.push_back({piece_x,   piece_y+1, 0});
        break;
    case PieceType::LEFT_GUN:
        result.push_back({piece_x,   piece_y,   0});
        result.push_back({piece_x,   piece_y+1, 0});
        result.push_back({piece_x+1, piece_y,   0});
        result.push_back({piece_x+2, piece_y,   0});
        break;
    case PieceType::RIGHT_GUN:
        result.push_back({piece_x,   piece_y,   0});
        result.push_back({piece_x+1, piece_y,   0});
        result.push_back({piece_x+2, piece_y,   0});
        result.push_back({piece_x+2, piece_y+1, 0});
        break;
    default:
        break;
    }

    return result;
}

bool Game::detectFullLine(int y){
    int count = 0;
    for (int x = 0; x <12; x++){
        if (board[y][x] != 0){
            count++;
        }
    }
    return (count == 10);
}

void Game::deleteFullLine(int y){
    //On supprime les minos de la liste des blocks placés
    //Dans l'ordre inverse pour ne pas sauter des éléments
    for (int i = placedMinos.size() - 1; i >= 0; i--){
        Block currentMino = placedMinos[i];
        if ((int)round(currentMino.position.y) == y){
            delete currentMino.forme;
            placedMinos.erase(placedMinos.begin() + i);
            std::cout << currentMino.position.x + 6;
        }
    }
    //On indique au board que les places sont maintenant vides
    for (int x = 0; x <12; x++){
        board[y][x] = 0;
        }
}

void Game::moveDownGame(int yDelete){
    //Pour tout les rangs au-dessus du rang ) supprimer, on baisse le rang d'un
    for (int y = yDelete; y < 11; y++){
        for (int x = 0; x < 12; x++){
            board[y][x] = board[y + 1][x];
        }
    }

    //Le rang du haut est maintenant vide
    for (int x = 0; x < 12; x++){
        board[11][x] = 0;
    }

    //Puis on descend tout les minos déjà placés de 1
    for (int i = 0; i < placedMinos.size(); i++){
        //Si le mino est au-dessus de la ligne supprimée, on le descend de 1
        if ((int)round(placedMinos[i].position.y) > yDelete){
            placedMinos[i].position.y -= 1.0f;

            //On reconstruit sa géométrie un rang plus bas
            placedMinos[i].forme->object->position.y -= 1.0f;
        }
    }
}

void Game::setShader(Shader* shader){
    this->shader = shader;
}

void Game::checkGameOver(vector<GridCoordinates> tetrominoGridCoordinates){
    for(const GridCoordinates& coordinate : tetrominoGridCoordinates){
        if (coordinate.y >= 12){
            this->gameOver = true;
            delete(fallingPiece);
            fallingPiece = nullptr;
            needNewPiece = false;
        }
    }
}
