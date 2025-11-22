#include "game.h"
#include "object.h"


/////// UNE FONCTION CHECK STATUS QUI CHECK LE STATUS A CHAQUE TOUR DE BOUCLE ?

Game::Game() {
    //Au début du jeu, on a pas de pièce
    this->needNewPiece = true;
    this->stackedPieces = {};
}

Game::~Game() {
    for (auto* piece : stackedPieces) {
        delete piece;
    }
}



void Game::spawn_piece() {
    //On génère une pièce, donc on a pas besoin d'une nouvelle pièce
    this->needNewPiece = false;
    vector<glm::vec3> vertex_buffer = this->getRandomTetromino();
    Object* result = new Object(vertex_buffer, {}, "");
    result->position.y = 12;
    //On stocke le résultat dans l'attribut "pieces" du jeu
    this->fallingPiece = result;
};

void Game::spawn_terrain() {}

std::vector<glm::vec3> Game::getRandomTetromino() {
    std::vector<std::function<std::vector<glm::vec3>()>> pieceCreators = {
        line_vertex_buffer_creator,
        block_vertex_buffer_creator,
        tee_vertex_buffer_creator,
        right_snake_vertex_buffer_creator,
        left_snake_vertex_buffer_creator,
        left_gun_vertex_buffer_creator,
        right_gun_vertex_buffer_creator
    };

    //Setup du générateur aléatoire
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, pieceCreators.size() - 1);

    //Choisir aléatoirement une fonction de création de vertex
    std::function<std::vector<glm::vec3>()> randomCreator = pieceCreators[dis(gen)];
    return randomCreator();
};
