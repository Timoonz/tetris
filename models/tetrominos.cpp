#include "tetrominos.h"

vector<glm::vec3> mino_creator(){
    vector<glm::vec3> res = {
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

    return res;
};

vector<glm::vec3> the_mino = mino_creator();

vector<glm::vec3> line_vertex_buffer_creator(){
    vector<glm::vec3> result;
    //First the_mino
    result.insert(result.end(), the_mino.begin(), the_mino.end());
    //Adding a the_mino on the right of the first the_mino
    vector<glm::vec3> trans_the_mino;
    trans_the_mino.resize(the_mino.size());
    transform(the_mino.begin(), the_mino.end(), trans_the_mino.begin(),
              [](const glm::vec3& v) { return v + glm::vec3(1.0f, 0.0f, 0.0f); });
    result.insert(result.end(), trans_the_mino.begin(), trans_the_mino.end());
    //Again
    transform(trans_the_mino.begin(), trans_the_mino.end(), trans_the_mino.begin(),
              [](const glm::vec3& v) { return v + glm::vec3(1.0f, 0.0f, 0.0f); });
    result.insert(result.end(), trans_the_mino.begin(), trans_the_mino.end());
    //And again...
    transform(trans_the_mino.begin(), trans_the_mino.end(), trans_the_mino.begin(),
              [](const glm::vec3& v) { return v + glm::vec3(1.0f, 0.0f, 0.0f); });
    result.insert(result.end(), trans_the_mino.begin(), trans_the_mino.end());

    return result;
};

///Block : four the_minos in a 2×2 square
vector<glm::vec3> block_vertex_buffer_creator() {
    vector<glm::vec3> result;
    vector<glm::vec3> trans_the_mino;
    trans_the_mino.resize(the_mino.size());
    //Bottom left the_mino
    result.insert(result.end(), the_mino.begin(), the_mino.end());
    //Bottom right the_mino
    transform(the_mino.begin(), the_mino.end(), trans_the_mino.begin(),
              [](const glm::vec3& v) { return v + glm::vec3(1.0f, 0.0f, 0.0f); });
    result.insert(result.end(), trans_the_mino.begin(), trans_the_mino.end());
    //Top right the_mino
    transform(trans_the_mino.begin(), trans_the_mino.end(), trans_the_mino.begin(),
              [](const glm::vec3& v) { return v + glm::vec3(0.0f, 1.0f, 0.0f); });
    result.insert(result.end(), trans_the_mino.begin(), trans_the_mino.end());
    //Top left the_mino
    transform(trans_the_mino.begin(), trans_the_mino.end(), trans_the_mino.begin(),
              [](const glm::vec3& v) { return v + glm::vec3(-1.0f, 0.0f, 0.0f); });
    result.insert(result.end(), trans_the_mino.begin(), trans_the_mino.end());

    return result;
};

/// T(ee) : a row of three the_minos with one added above the center
vector<glm::vec3> tee_vertex_buffer_creator() {
    vector<glm::vec3> result;
    vector<glm::vec3> trans_the_mino;
    trans_the_mino.resize(the_mino.size());
    //Bottom left the_mino
    result.insert(result.end(), the_mino.begin(), the_mino.end());
    //Bottom middle the_mino
    transform(the_mino.begin(), the_mino.end(), trans_the_mino.begin(),
              [](const glm::vec3& v) { return v + glm::vec3(1.0f, 0.0f, 0.0f); });
    result.insert(result.end(), trans_the_mino.begin(), trans_the_mino.end());
    //Top  the_mino
    transform(trans_the_mino.begin(), trans_the_mino.end(), trans_the_mino.begin(),
              [](const glm::vec3& v) { return v + glm::vec3(0.0f, 1.0f, 0.0f); });
    result.insert(result.end(), trans_the_mino.begin(), trans_the_mino.end());
    //Bottom right the_mino
    transform(trans_the_mino.begin(), trans_the_mino.end(), trans_the_mino.begin(),
              [](const glm::vec3& v) { return v + glm::vec3(1.0f, -1.0f, 0.0f); });
    result.insert(result.end(), trans_the_mino.begin(), trans_the_mino.end());

    return result;
};

/// Right snake (or S): two stacked horizontal dithe_minos with the top one offset to the right
vector<glm::vec3> right_snake_vertex_buffer_creator() {
    vector<glm::vec3> result;
    vector<glm::vec3> trans_the_mino;
    trans_the_mino.resize(the_mino.size());
    //Bottom left the_mino
    result.insert(result.end(), the_mino.begin(), the_mino.end());
    //Bottom right the_mino
    transform(the_mino.begin(), the_mino.end(), trans_the_mino.begin(),
              [](const glm::vec3& v) { return v + glm::vec3(1.0f, 0.0f, 0.0f); });
    result.insert(result.end(), trans_the_mino.begin(), trans_the_mino.end());
    //Top left (with right offset) the_mino
    transform(trans_the_mino.begin(), trans_the_mino.end(), trans_the_mino.begin(),
              [](const glm::vec3& v) { return v + glm::vec3(0.0f, 1.0f, 0.0f); });
    result.insert(result.end(), trans_the_mino.begin(), trans_the_mino.end());
    //Top right (with right offset) the_mino
    transform(trans_the_mino.begin(), trans_the_mino.end(), trans_the_mino.begin(),
              [](const glm::vec3& v) { return v + glm::vec3(1.0f, 0.0f, 0.0f); });
    result.insert(result.end(), trans_the_mino.begin(), trans_the_mino.end());

    return result;
};


/// Left snake (or Z): two stacked horizontal dithe_minos with the top one offset to the left
vector<glm::vec3> left_snake_vertex_buffer_creator() {
    vector<glm::vec3> result;
    vector<glm::vec3> trans_the_mino;
    trans_the_mino.resize(the_mino.size());
    //Bottom right the_mino
    transform(the_mino.begin(), the_mino.end(), trans_the_mino.begin(),
              [](const glm::vec3& v) { return v + glm::vec3(2.0f, 0.0f, 0.0f); });
    result.insert(result.end(), trans_the_mino.begin(), trans_the_mino.end());
    //Bottom left the_mino
    transform(trans_the_mino.begin(), trans_the_mino.end(), trans_the_mino.begin(),
              [](const glm::vec3& v) { return v + glm::vec3(-1.0f, 0.0f, 0.0f); });
    result.insert(result.end(), trans_the_mino.begin(), trans_the_mino.end());
    //Top right (with left offset) the_mino
    transform(trans_the_mino.begin(), trans_the_mino.end(), trans_the_mino.begin(),
              [](const glm::vec3& v) { return v + glm::vec3(0.0f, 1.0f, 0.0f); });
    result.insert(result.end(), trans_the_mino.begin(), trans_the_mino.end());
    //Top left (with left offset) the_mino
    transform(trans_the_mino.begin(), trans_the_mino.end(), trans_the_mino.begin(),
              [](const glm::vec3& v) { return v + glm::vec3(-1.0f, 0.0f, 0.0f); });
    result.insert(result.end(), trans_the_mino.begin(), trans_the_mino.end());

    return result;
};


/// Left gun : a row of three the_minos with one added above the left side
vector<glm::vec3> left_gun_vertex_buffer_creator() {
    vector<glm::vec3> result;
    vector<glm::vec3> trans_the_mino;
    trans_the_mino.resize(the_mino.size());
    //Bottom left the_mino
    result.insert(result.end(), the_mino.begin(), the_mino.end());
    //Top the_mino
    transform(the_mino.begin(), the_mino.end(), trans_the_mino.begin(),
              [](const glm::vec3& v) { return v + glm::vec3(0.0f, 1.0f, 0.0f); });
    result.insert(result.end(), trans_the_mino.begin(), trans_the_mino.end());
    //Bottom middle the_mino
    transform(trans_the_mino.begin(), trans_the_mino.end(), trans_the_mino.begin(),
              [](const glm::vec3& v) { return v + glm::vec3(1.0f, -1.0f, 0.0f); });
    result.insert(result.end(), trans_the_mino.begin(), trans_the_mino.end());
    //Bottom left the_mino
    transform(trans_the_mino.begin(), trans_the_mino.end(), trans_the_mino.begin(),
              [](const glm::vec3& v) { return v + glm::vec3(1.0f, 0.0f, 0.0f); });
    result.insert(result.end(), trans_the_mino.begin(), trans_the_mino.end());

    return result;
};



/// Right gun : a row of three the_minos with one added above the right side
vector<glm::vec3> right_gun_vertex_buffer_creator() {
    vector<glm::vec3> result;
    vector<glm::vec3> trans_the_mino;
    trans_the_mino.resize(the_mino.size());
    //Bottom left the_mino
    result.insert(result.end(), the_mino.begin(), the_mino.end());
    //Bottom middle the_mino
    transform(the_mino.begin(), the_mino.end(), trans_the_mino.begin(),
              [](const glm::vec3& v) { return v + glm::vec3(1.0f, 0.0f, 0.0f); });
    result.insert(result.end(), trans_the_mino.begin(), trans_the_mino.end());
    //Bottom left the_mino
    transform(trans_the_mino.begin(), trans_the_mino.end(), trans_the_mino.begin(),
              [](const glm::vec3& v) { return v + glm::vec3(1.0f, 0.0f, 0.0f); });
    result.insert(result.end(), trans_the_mino.begin(), trans_the_mino.end());
    //Top the_mino
    transform(trans_the_mino.begin(), trans_the_mino.end(), trans_the_mino.begin(),
              [](const glm::vec3& v) { return v + glm::vec3(0.0f, 1.0f, 0.0f); });
    result.insert(result.end(), trans_the_mino.begin(), trans_the_mino.end());


    return result;
};
