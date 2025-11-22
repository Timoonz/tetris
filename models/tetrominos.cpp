#include "tetrominos.h"

vector<glm::vec3> mino_creator(float pos_x, float pos_y, float pos_z){
    vector<glm::vec3> res = {
        glm::vec3(pos_x + 0.0f, pos_y + 0.0f, pos_z + 0.0f), // triangle 1 : begin
        glm::vec3(pos_x + 0.0f, pos_y + 0.0f, pos_z + 1.0f),
        glm::vec3(pos_x + 0.0f, pos_y + 1.0f, pos_z + 1.0f), // triangle 1 : end
        glm::vec3(pos_x + 1.0f, pos_y + 1.0f, pos_z + 0.0f), // triangle 2 : begin
        glm::vec3(pos_x + 0.0f, pos_y + 0.0f, pos_z + 0.0f),
        glm::vec3(pos_x + 0.0f, pos_y + 1.0f, pos_z + 0.0f), // triangle 2 : end
        glm::vec3(pos_x + 1.0f, pos_y + 0.0f, pos_z + 1.0f),
        glm::vec3(pos_x + 0.0f, pos_y + 0.0f, pos_z + 0.0f),
        glm::vec3(pos_x + 1.0f, pos_y + 0.0f, pos_z + 0.0f),
        glm::vec3(pos_x + 1.0f, pos_y + 1.0f, pos_z + 0.0f),
        glm::vec3(pos_x + 1.0f, pos_y + 0.0f, pos_z + 0.0f),
        glm::vec3(pos_x + 0.0f, pos_y + 0.0f, pos_z + 0.0f),
        glm::vec3(pos_x + 0.0f, pos_y + 0.0f, pos_z + 0.0f),
        glm::vec3(pos_x + 0.0f, pos_y + 1.0f, pos_z + 1.0f),
        glm::vec3(pos_x + 0.0f, pos_y + 1.0f, pos_z + 0.0f),
        glm::vec3(pos_x + 1.0f, pos_y + 0.0f, pos_z + 1.0f),
        glm::vec3(pos_x + 0.0f, pos_y + 0.0f, pos_z + 1.0f),
        glm::vec3(pos_x + 0.0f, pos_y + 0.0f, pos_z + 0.0f),
        glm::vec3(pos_x + 0.0f, pos_y + 1.0f, pos_z + 1.0f),
        glm::vec3(pos_x + 0.0f, pos_y + 0.0f, pos_z + 1.0f),
        glm::vec3(pos_x + 1.0f, pos_y + 0.0f, pos_z + 1.0f),
        glm::vec3(pos_x + 1.0f, pos_y + 1.0f, pos_z + 1.0f),
        glm::vec3(pos_x + 1.0f, pos_y + 0.0f, pos_z + 0.0f),
        glm::vec3(pos_x + 1.0f, pos_y + 1.0f, pos_z + 0.0f),
        glm::vec3(pos_x + 1.0f, pos_y + 0.0f, pos_z + 0.0f),
        glm::vec3(pos_x + 1.0f, pos_y + 1.0f, pos_z + 1.0f),
        glm::vec3(pos_x + 1.0f, pos_y + 0.0f, pos_z + 1.0f),
        glm::vec3(pos_x + 1.0f, pos_y + 1.0f, pos_z + 1.0f),
        glm::vec3(pos_x + 1.0f, pos_y + 1.0f, pos_z + 0.0f),
        glm::vec3(pos_x + 0.0f, pos_y + 1.0f, pos_z + 0.0f),
        glm::vec3(pos_x + 1.0f, pos_y + 1.0f, pos_z + 1.0f),
        glm::vec3(pos_x + 0.0f, pos_y + 1.0f, pos_z + 0.0f),
        glm::vec3(pos_x + 0.0f, pos_y + 1.0f, pos_z + 1.0f),
        glm::vec3(pos_x + 1.0f, pos_y + 1.0f, pos_z + 1.0f),
        glm::vec3(pos_x + 0.0f, pos_y + 1.0f, pos_z + 1.0f),
        glm::vec3(pos_x + 1.0f, pos_y + 0.0f, pos_z + 1.0f)
    };

    return res;
};

vector<glm::vec3> the_mino = mino_creator(0.0f, 0.0f, 0.0f);

vector<glm::vec3> line_vertex_buffer_creator(){
    vector<glm::vec3> result;
    //Premier mino
    insert_mino(result, 0.0f, 0.0f, 0.0f);
    //Insérer un mino à la droite de ce mino
    vector<glm::vec3> trans_the_mino;
    insert_mino(result, 1.0f, 0.0f, 0.0f);
    //Encore
    insert_mino(result, 2.0f, 0.0f, 0.0f);
    //Et encore...
    insert_mino(result, 3.0f, 0.0f, 0.0f);

    return result;
};

///Block : four the_minos in a 2×2 square
vector<glm::vec3> block_vertex_buffer_creator() {
    vector<glm::vec3> result;
    //Mino en bas à gauche
    insert_mino(result, 0.0f, 0.0f, 0.0f);
    //Mino en bas à droite
    insert_mino(result, 1.0f, 0.0f, 0.0f);
    //Mino en haut à droite
    insert_mino(result, 1.0f, 1.0f, 0.0f);
    //Mino en haut à gauche
    insert_mino(result, 0.0f, 1.0f, 0.0f);

    return result;
};

/// T(ee) : a row of three the_minos with one added above the center
vector<glm::vec3> tee_vertex_buffer_creator() {
    vector<glm::vec3> result;
    //Bottom left the_mino
    insert_mino(result, 0.0f, 0.0f, 0.0f);
    //Bottom middle the_mino
    insert_mino(result, 1.0f, 0.0f, 0.0f);
    //Top  the_mino
    insert_mino(result, 1.0f, 1.0f, 0.0f);
    //Bottom right the_mino
    insert_mino(result, 2.0f, 0.0f, 0.0f);

    return result;
};

/// Right snake (or S): two stacked horizontal dithe_minos with the top one offset to the right
vector<glm::vec3> right_snake_vertex_buffer_creator() {
    vector<glm::vec3> result;
    //Bottom left the_mino
    insert_mino(result, 0.0f, 0.0f, 0.0f);
    //Bottom right the_mino
    insert_mino(result, 1.0f, 0.0f, 0.0f);
    //Top left (with right offset) the_mino
    insert_mino(result, 1.0f, 1.0f, 0.0f);
    //Top right (with right offset) the_mino
    insert_mino(result, 2.0f, 1.0f, 0.0f);

    return result;
};


/// Left snake (or Z): two stacked horizontal dithe_minos with the top one offset to the left
vector<glm::vec3> left_snake_vertex_buffer_creator() {
    vector<glm::vec3> result;
    //Bottom right mino
    insert_mino(result, 2.0f, 0.0f, 0.0f);
    //Bottom left mino
    insert_mino(result, 1.0f, 0.0f, 0.0f);
    //Top right (with left offset) mino
    insert_mino(result, 1.0f, 1.0f, 0.0f);
    //Top left (with left offset) the_mino
    insert_mino(result, 0.0f, 1.0f, 0.0f);

    return result;
};


/// Left gun : a row of three the_minos with one added above the left side
vector<glm::vec3> left_gun_vertex_buffer_creator() {
    vector<glm::vec3> result;
    //Bottom left the_mino
    insert_mino(result, 0.0f, 0.0f, 0.0f);
    //Top the_mino
    insert_mino(result, 0.0f, 1.0f, 0.0f);
    //Bottom middle the_mino
    insert_mino(result, 1.0f, 0.0f, 0.0f);
    //Bottom left the_mino
    insert_mino(result, 2.0f, 0.0f, 0.0f);

    return result;
};



/// Right gun : a row of three the_minos with one added above the right side
vector<glm::vec3> right_gun_vertex_buffer_creator() {
    vector<glm::vec3> result;
    //Bottom left mino
    insert_mino(result, 0.0f, 0.0f, 0.0f);
    //Bottom middle mino
    insert_mino(result, 1.0f, 0.0f, 0.0f);
    //Bottom left mino
    insert_mino(result, 2.0f, 0.0f, 0.0f);
    //Top the_mino
    insert_mino(result, 2.0f, 1.0f, 0.0f);

    return result;
};


/// FONCTIONS UTILITAIRES

///Insère un mino (déterminé par ces positions x, y et z) à la fin de base_array
void insert_mino(vector<glm::vec3> &base_array, float pos_x, float pos_y, float pos_z){
    vector<glm::vec3> trans_the_mino = mino_creator(pos_x, pos_y, pos_z);
    base_array.insert(base_array.end(), trans_the_mino.begin(), trans_the_mino.end());
}
