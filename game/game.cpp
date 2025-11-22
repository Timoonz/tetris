
#include "game.h"
#include "object.h"

/////// UNE FONCTION CHECK STATUS QUI CHECK LE STATUS A CHAQUE TOUR DE BOUCLE ?

Game::Game() {
    //Au début du jeu, on a pas de pièce
    this->needNewPiece = true;
    this->pieces = {};
}

Game::~Game() {
    for (auto* piece : pieces) {
        delete piece;
    }
}

void Game::spawn_piece() {
    //On génère une pièce, donc on a pas besoin d'une nouvelle pièce
    this->needNewPiece = false;
    vector<glm::vec3> vertex_buffer = block_vertex_buffer_creator();
    Object* result = new Object(vertex_buffer, {}, "");
    //On stocke le résultat dans l'attribut "pieces" du jeu
    this->pieces.push_back(result);
}

void Game::spawn_terrain() {}
