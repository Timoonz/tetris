#ifndef TETROMINOS_H
#define TETROMINOS_H

#include <algorithm>
#include <vector>
#include "glm/glm.hpp"

using namespace std;

/* Descriptions for each minos are taken from the Tetris game wiki (tetris.wiki/Tetromino) */


////STANDARD CUBE (the "minos")
vector<glm::vec3> mino = {
    glm::vec3(-0.5f,-0.5f,-0.5f), // triangle 1 : begin
    glm::vec3(-0.5f,-0.5f, 0.5f),
    glm::vec3(-0.5f, 0.5f, 0.5f), // triangle 1 : end
    glm::vec3(0.5f, 0.5f,-0.5f), // triangle 2 : begin
    glm::vec3(-0.5f,-0.5f,-0.5f),
    glm::vec3(-0.5f, 0.5f,-0.5f), // triangle 2 : end
    glm::vec3(0.5f,-0.5f, 0.5f),
    glm::vec3(-0.5f,-0.5f,-0.5f),
    glm::vec3(0.5f,-0.5f,-0.5f),
    glm::vec3(0.5f, 0.5f,-0.5f),
    glm::vec3(0.5f,-0.5f,-0.5f),
    glm::vec3(-0.5f,-0.5f,-0.5f),
    glm::vec3(-0.5f,-0.5f,-0.5f),
    glm::vec3(-0.5f, 0.5f, 0.5f),
    glm::vec3(-0.5f, 0.5f,-0.5f),
    glm::vec3(0.5f,-0.5f, 0.5f),
    glm::vec3(-0.5f,-0.5f, 0.5f),
    glm::vec3(-0.5f,-0.5f,-0.5f),
    glm::vec3(-0.5f, 0.5f, 0.5f),
    glm::vec3(-0.5f,-0.5f, 0.5f),
    glm::vec3(0.5f,-0.5f, 0.5f),
    glm::vec3(0.5f, 0.5f, 0.5f),
    glm::vec3(0.5f,-0.5f,-0.5f),
    glm::vec3(0.5f, 0.5f,-0.5f),
    glm::vec3(0.5f,-0.5f,-0.5f),
    glm::vec3(0.5f, 0.5f, 0.5f),
    glm::vec3(0.5f,-0.5f, 0.5f),
    glm::vec3(0.5f, 0.5f, 0.5f),
    glm::vec3(0.5f, 0.5f,-0.5f),
    glm::vec3(-0.5f, 0.5f,-0.5f),
    glm::vec3(0.5f, 0.5f, 0.5f),
    glm::vec3(-0.5f, 0.5f,-0.5f),
    glm::vec3(-0.5f, 0.5f, 0.5f),
    glm::vec3(0.5f, 0.5f, 0.5f),
    glm::vec3(-0.5f, 0.5f, 0.5f),
    glm::vec3(0.5f,-0.5f, 0.5f)
};


/// Line: four minos in a straight line
vector<glm::vec3> line_vertex_buffer_creator(){
    vector<glm::vec3> result;
    //First mino
    result.insert(result.end(), mino.begin(), mino.end());
    //Adding a mino on the right of the first mino
    vector<glm::vec3> trans_mino;
    trans_mino.resize(mino.size());
    transform(mino.begin(), mino.end(), trans_mino.begin(),
        [](const glm::vec3& v) { return v + glm::vec3(1.0f, 0.0f, 0.0f); });
    result.insert(result.end(), trans_mino.begin(), trans_mino.end());
    //Again
    transform(trans_mino.begin(), trans_mino.end(), trans_mino.begin(),
        [](const glm::vec3& v) { return v + glm::vec3(1.0f, 0.0f, 0.0f); });
    result.insert(result.end(), trans_mino.begin(), trans_mino.end());
    //And again...
    transform(trans_mino.begin(), trans_mino.end(), trans_mino.begin(),
        [](const glm::vec3& v) { return v + glm::vec3(1.0f, 0.0f, 0.0f); });
    result.insert(result.end(), trans_mino.begin(), trans_mino.end());

    return result;
};

///Block : four Minos in a 2×2 square
vector<glm::vec3> block_vertex_buffer_creator() {
    vector<glm::vec3> result;
    vector<glm::vec3> trans_mino;
    trans_mino.resize(mino.size());
    //Bottom left mino
    result.insert(result.end(), mino.begin(), mino.end());
    //Bottom right mino
    transform(mino.begin(), mino.end(), trans_mino.begin(),
              [](const glm::vec3& v) { return v + glm::vec3(1.0f, 0.0f, 0.0f); });
    result.insert(result.end(), trans_mino.begin(), trans_mino.end());
    //Top right mino
    transform(trans_mino.begin(), trans_mino.end(), trans_mino.begin(),
              [](const glm::vec3& v) { return v + glm::vec3(0.0f, 1.0f, 0.0f); });
    result.insert(result.end(), trans_mino.begin(), trans_mino.end());
    //Top left mino
    transform(trans_mino.begin(), trans_mino.end(), trans_mino.begin(),
              [](const glm::vec3& v) { return v + glm::vec3(-1.0f, 0.0f, 0.0f); });
    result.insert(result.end(), trans_mino.begin(), trans_mino.end());

    return result;
};

/// T(ee) : a row of three Minos with one added above the center
vector<glm::vec3> tee_vertex_buffer_creator() {
    vector<glm::vec3> result;
    vector<glm::vec3> trans_mino;
    trans_mino.resize(mino.size());
    //Bottom left mino
    result.insert(result.end(), mino.begin(), mino.end());
    //Bottom middle mino
    transform(mino.begin(), mino.end(), trans_mino.begin(),
              [](const glm::vec3& v) { return v + glm::vec3(1.0f, 0.0f, 0.0f); });
    result.insert(result.end(), trans_mino.begin(), trans_mino.end());
    //Top  mino
    transform(trans_mino.begin(), trans_mino.end(), trans_mino.begin(),
              [](const glm::vec3& v) { return v + glm::vec3(0.0f, 1.0f, 0.0f); });
    result.insert(result.end(), trans_mino.begin(), trans_mino.end());
    //Bottom right mino
    transform(trans_mino.begin(), trans_mino.end(), trans_mino.begin(),
              [](const glm::vec3& v) { return v + glm::vec3(1.0f, -1.0f, 0.0f); });
    result.insert(result.end(), trans_mino.begin(), trans_mino.end());

    return result;
};

/// Right snake (or S): two stacked horizontal diminos with the top one offset to the right
vector<glm::vec3> right_snake_vertex_buffer_creator() {
    vector<glm::vec3> result;
    vector<glm::vec3> trans_mino;
    trans_mino.resize(mino.size());
    //Bottom left mino
    result.insert(result.end(), mino.begin(), mino.end());
    //Bottom right mino
    transform(mino.begin(), mino.end(), trans_mino.begin(),
              [](const glm::vec3& v) { return v + glm::vec3(1.0f, 0.0f, 0.0f); });
    result.insert(result.end(), trans_mino.begin(), trans_mino.end());
    //Top left (with right offset) mino
    transform(trans_mino.begin(), trans_mino.end(), trans_mino.begin(),
              [](const glm::vec3& v) { return v + glm::vec3(0.0f, 1.0f, 0.0f); });
    result.insert(result.end(), trans_mino.begin(), trans_mino.end());
    //Top right (with right offset) mino
    transform(trans_mino.begin(), trans_mino.end(), trans_mino.begin(),
              [](const glm::vec3& v) { return v + glm::vec3(1.0f, 0.0f, 0.0f); });
    result.insert(result.end(), trans_mino.begin(), trans_mino.end());

    return result;
};


/// Left snake (or Z): two stacked horizontal diminos with the top one offset to the left
vector<glm::vec3> left_snake_vertex_buffer_creator() {
    vector<glm::vec3> result;
    vector<glm::vec3> trans_mino;
    trans_mino.resize(mino.size());
    //Bottom right mino
    transform(mino.begin(), mino.end(), trans_mino.begin(),
              [](const glm::vec3& v) { return v + glm::vec3(2.0f, 0.0f, 0.0f); });
    result.insert(result.end(), trans_mino.begin(), trans_mino.end());
    //Bottom left mino
    transform(trans_mino.begin(), trans_mino.end(), trans_mino.begin(),
              [](const glm::vec3& v) { return v + glm::vec3(-1.0f, 0.0f, 0.0f); });
    result.insert(result.end(), trans_mino.begin(), trans_mino.end());
    //Top right (with left offset) mino
    transform(trans_mino.begin(), trans_mino.end(), trans_mino.begin(),
              [](const glm::vec3& v) { return v + glm::vec3(0.0f, 1.0f, 0.0f); });
    result.insert(result.end(), trans_mino.begin(), trans_mino.end());
    //Top left (with left offset) mino
    transform(trans_mino.begin(), trans_mino.end(), trans_mino.begin(),
              [](const glm::vec3& v) { return v + glm::vec3(-1.0f, 0.0f, 0.0f); });
    result.insert(result.end(), trans_mino.begin(), trans_mino.end());

    return result;
};


/// Left gun : a row of three Minos with one added above the left side
vector<glm::vec3> left_gun_vertex_buffer_creator() {
    vector<glm::vec3> result;
    vector<glm::vec3> trans_mino;
    trans_mino.resize(mino.size());
    //Bottom left mino
    result.insert(result.end(), mino.begin(), mino.end());
    //Top mino
    transform(mino.begin(), mino.end(), trans_mino.begin(),
              [](const glm::vec3& v) { return v + glm::vec3(0.0f, 1.0f, 0.0f); });
    result.insert(result.end(), trans_mino.begin(), trans_mino.end());
    //Bottom middle mino
    transform(trans_mino.begin(), trans_mino.end(), trans_mino.begin(),
              [](const glm::vec3& v) { return v + glm::vec3(1.0f, -1.0f, 0.0f); });
    result.insert(result.end(), trans_mino.begin(), trans_mino.end());
    //Bottom left mino
    transform(trans_mino.begin(), trans_mino.end(), trans_mino.begin(),
              [](const glm::vec3& v) { return v + glm::vec3(1.0f, 0.0f, 0.0f); });
    result.insert(result.end(), trans_mino.begin(), trans_mino.end());

    return result;
};



/// Right gun : a row of three Minos with one added above the right side
vector<glm::vec3> right_gun_vertex_buffer_creator() {
    vector<glm::vec3> result;
    vector<glm::vec3> trans_mino;
    trans_mino.resize(mino.size());
    //Bottom left mino
    result.insert(result.end(), mino.begin(), mino.end());
    //Bottom middle mino
    transform(mino.begin(), mino.end(), trans_mino.begin(),
              [](const glm::vec3& v) { return v + glm::vec3(1.0f, 0.0f, 0.0f); });
    result.insert(result.end(), trans_mino.begin(), trans_mino.end());
    //Bottom left mino
    transform(trans_mino.begin(), trans_mino.end(), trans_mino.begin(),
              [](const glm::vec3& v) { return v + glm::vec3(1.0f, 0.0f, 0.0f); });
    result.insert(result.end(), trans_mino.begin(), trans_mino.end());
    //Top mino
    transform(trans_mino.begin(), trans_mino.end(), trans_mino.begin(),
              [](const glm::vec3& v) { return v + glm::vec3(0.0f, 1.0f, 0.0f); });
    result.insert(result.end(), trans_mino.begin(), trans_mino.end());


    return result;
};

#endif // TETROMINOS_H
