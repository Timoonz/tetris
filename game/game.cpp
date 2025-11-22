#include "game.h"
#include "object.h"


/////// UNE FONCTION CHECK STATUS QUI CHECK LE STATUS A CHAQUE TOUR DE BOUCLE ?

Game::Game() {
    this->stackedPieces = {};
}

Game::~Game() {
    for (auto* piece : stackedPieces) {
        delete piece;
    }
}



void Game::spawn_piece() {
    //On génère une pièce, donc on a pas besoin d'une nouvelle pièce
    std::pair<vector<glm::vec3>, PieceType> buffer_and_type = this->getRandomTetromino();
    Object* result = new Object(buffer_and_type.first, {}, "", buffer_and_type.second);
    result->position.y = 12;
    //On stocke le résultat dans l'attribut "pieces" du jeu
    this->fallingPiece = result;
};

void Game::spawn_terrain() {}

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
    case 0: vertex_buffer = line_vertex_buffer_creator();
        type = PieceType::LINE; break;
    case 1: vertex_buffer = block_vertex_buffer_creator();
        type = PieceType::BLOCK; break;
    case 2: vertex_buffer = tee_vertex_buffer_creator();
        type = PieceType::TEE; break;
    case 3: vertex_buffer = right_snake_vertex_buffer_creator();
        type = PieceType::RIGHT_SNAKE; break;
    case 4: vertex_buffer = left_snake_vertex_buffer_creator();
        type = PieceType::LEFT_SNAKE; break;
    case 5: vertex_buffer = left_gun_vertex_buffer_creator();
        type = PieceType::LEFT_GUN; break;
    case 6: vertex_buffer = right_gun_vertex_buffer_creator();
        type = PieceType::RIGHT_GUN; break;
    }

    //On renvoie la paire du vertex_buffer et du type de pièce
    return std::make_pair(vertex_buffer, type);
};
