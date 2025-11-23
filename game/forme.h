#ifndef FORME_H
#define FORME_H

#include "object.h"
#include "shader.h"
#include <vector>

std::pair<std::vector<glm::vec3>, PieceType>  getRandomTetromino();

class Forme
{
public:
    Forme(std::vector<glm::vec3> vertex_buffer, PieceType type, glm::vec3 color);
    ~Forme();
    Object* object;
    glm::vec3 color;

};

#endif // FORME_H
