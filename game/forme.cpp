#include <random>
#include <string>

#include "forme.h"
#include "models/tetrominos.h"

Forme::Forme(std::vector<glm::vec3> vertex_buffer, PieceType type, glm::vec3 color):
    color(color){
    object = new Object(vertex_buffer, {}, "", type);
    std::string path = "/home/timoonz/Documents/tsi/tp_tetris/tp_tetris/shaders/";
}

Forme::~Forme(){
    delete object;}

std::pair<std::vector<glm::vec3>, PieceType> getRandomTetromino() {
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
