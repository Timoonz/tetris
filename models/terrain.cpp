#include "terrain.h"
#include "tetrominos.h"



vector<glm::vec3> terrain_creator() {
    vector<glm::vec3> result;
    //Premier mino
    // vector<glm::vec3> mino = mino_creator(0.0f, 0.0f, 0.0f);
    // result.insert(result.end(), mino.begin(), mino.end());
    insert_mino(result, 0.0f, 0.0f, 0.0f);
    //Preparation du mino "curseur"
    //On veut 12 minos sur la base du terrain: on en met 5 à droite...
    for (int i = 1; i <= 5; i++) {
        insert_mino(result, i + 0.0f, 0.0f, 0.0f);
    };
    //On rajoute 12 minos par-dessus
    for (int i = 1; i <=12; i++){
        insert_mino(result, 5.0f, i + 0.0f, 0.0f);
    }
    //... et on en rajoute 6 sur la gauche
    for (int i = 1; i <= 6; i++) {
        insert_mino(result, 0.0f - i, 0.0f, 0.0f);
    };
    //Et enfin de nouveau 12 par-dessus
    for (int i = 1; i <=12; i++){
        insert_mino(result, -6.0f, i + 0.0f, 0.0f);
    }

    return result;
}
