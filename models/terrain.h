#ifndef TERRAIN_H
#define TERRAIN_H

#include <vector>
#include <algorithm>
#include "glm/glm.hpp"

#include "tetrominos.h"

using namespace std;


vector<glm::vec3> terrain_creator() {
    vector<glm::vec3> result;
    //Premier mino
    result.insert(result.end(), mino.begin(), mino.end());
    //Preparation du mino "curseur"
    vector<glm::vec3> trans_mino = mino;
    //On veut 12 minos sur la base du terrain: on en met 5 à droite...
    for (int i = 1; i <= 5; i++) {
        transform(trans_mino.begin(), trans_mino.end(), trans_mino.begin(),
                  [](const glm::vec3& v) { return v + glm::vec3(1.0f, 0.0f, 0.0f); });
        result.insert(result.end(), trans_mino.begin(), trans_mino.end());
    };
    //On rajoute 12 minos par-dessus
    for (int i = 1; i <=12; i++){
        transform(trans_mino.begin(), trans_mino.end(), trans_mino.begin(),
                  [](const glm::vec3& v) { return v + glm::vec3(0.0f, 1.0f, 0.0f); });
        result.insert(result.end(), trans_mino.begin(), trans_mino.end());
    }
    //On revient à la base
    transform(mino.begin(), mino.end(), trans_mino.begin(),
              [](const glm::vec3& v) { return v ;});
    //... et on en rajoute 6 sur la gauche
    for (int i = 1; i <= 5; i++) {
        transform(trans_mino.begin(), trans_mino.end(), trans_mino.begin(),
                  [](const glm::vec3& v) { return v + glm::vec3(-1.0f, 0.0f, 0.0f); });
        result.insert(result.end(), trans_mino.begin(), trans_mino.end());
    };
    //Et enfin de nouveau 12 par-dessus
    for (int i = 1; i <=12; i++){
        transform(trans_mino.begin(), trans_mino.end(), trans_mino.begin(),
                  [](const glm::vec3& v) { return v + glm::vec3(0.0f, 1.0f, 0.0f); });
        result.insert(result.end(), trans_mino.begin(), trans_mino.end());
    }

    return result;
}

#endif // TERRAIN_H
