#ifndef TETROMINOS_H
#define TETROMINOS_H

#include <algorithm>
#include <vector>
#include "glm/glm.hpp"

using namespace std;

/* Descriptions for each minos are taken from the Tetris game wiki (tetris.wiki/Tetromino) */


////STANDARD CUBE (the "minos")
vector<glm::vec3> mino_creator(float pos_x, float pos_y, float pos_z);

/// Line: four minos in a straight line
vector<glm::vec3> line_vertex_buffer_creator();

///Block : four Minos in a 2×2 square
vector<glm::vec3> block_vertex_buffer_creator();

/// T(ee) : a row of three Minos with one added above the center
vector<glm::vec3> tee_vertex_buffer_creator();

/// Right snake (or S): two stacked horizontal diminos with the top one offset to the right
vector<glm::vec3> right_snake_vertex_buffer_creator();

/// Left snake (or Z): two stacked horizontal diminos with the top one offset to the left
vector<glm::vec3> left_snake_vertex_buffer_creator();

/// Left gun : a row of three Minos with one added above the left side
vector<glm::vec3> left_gun_vertex_buffer_creator();

/// Right gun : a row of three Minos with one added above the right side
vector<glm::vec3> right_gun_vertex_buffer_creator();

/////////FONCTIONS UTILITAIRES

void insert_mino(vector<glm::vec3> &base_array, float pos_x, float pos_y, float pos_z);


#endif // TETROMINOS_H
