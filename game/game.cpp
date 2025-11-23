#include "game.h"
#include "object.h"
#include "models/tetrominos.h"

//Pour débugger
#include <iostream>

Game::Game() {
    //À l'initialisation, il n'y a pas de pièces qui tombent et de pièces déjà stackées
    this->fallingPiece = nullptr;
    //On initialise le tableau permettant de tracker les blocs stackés
    for (int x = 0; x < 20; x++){
        for (int y = 0; y < 14; y++){
            this->board[x][y] = 0;
        }
    }
    this->needNewPiece = true;
}

Game::~Game() {
    // for (auto* piece : stackedPieces) {
    //     delete piece;
    // }
}

void Game::spawn_piece() {
    //On génère une pièce, donc on a pas besoin d'une nouvelle pièce
    std::pair<vector<glm::vec3>, PieceType> buffer_and_type = this->getRandomTetromino();
    Object* result = new Object(buffer_and_type.first, {}, "", buffer_and_type.second);
    result->position.y = 12.0f;
    result->position.x = 0.0f;
    //On stocke le résultat dans l'attribut "pieces" du jeu
    this->fallingPiece = result;
    this->needNewPiece = false;
};


std::pair<vector<glm::vec3>, PieceType> Game::getRandomTetromino() {
   //Setup du générateur aléatoire
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 6);

    //Choisir aléatoirement une fonction de création de vertex
    int randomIndex = dis(gen);
    vector<glm::vec3> vertex_buffer;
    PieceType type;

    switch(randomIndex) {
    case 0:
        vertex_buffer = line_vertex_buffer_creator();
        type = PieceType::LINE;
        break;
    case 1:
        vertex_buffer = block_vertex_buffer_creator();
        type = PieceType::BLOCK;
        break;
    case 2:
        vertex_buffer = tee_vertex_buffer_creator();
        type = PieceType::TEE;
        break;
    case 3:
        vertex_buffer = right_snake_vertex_buffer_creator();
        type = PieceType::RIGHT_SNAKE;
        break;
    case 4:
        vertex_buffer = left_snake_vertex_buffer_creator();
        type = PieceType::LEFT_SNAKE;
        break;
    case 5:
        vertex_buffer = left_gun_vertex_buffer_creator();
        type = PieceType::LEFT_GUN;
        break;
    case 6:
        vertex_buffer = right_gun_vertex_buffer_creator();
        type = PieceType::RIGHT_GUN;
        break;
    }

    //On renvoie la paire du vertex_buffer et du type de pièce
    return std::make_pair(vertex_buffer, type);
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
    fallingPiece->position.y = round(fallingPiece->position.y);
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
        fallingPiece->position.y += 1.0f;
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
            block.geometryBuffer = mino_creator(x_grid, y_grid, 0.0f);
            //block.color = piece;
            placedMinos.push_back(block);
        }
    }

    //On scan pour savoir si une ligne est pleine
    for (int rang = 12; rang > 0; rang--){
        if (detectLine(rang)){
            // std::cout << "LINE " << rang << " FULL\n";
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

bool Game::detectLine(int y){
    int count = 0;
    for (int x = 0; x <12; x++){
        if (board[y][x] != 0){
            count++;
        }
    }
    return (count == 10);
}


void Game::spawn_terrain() {}
