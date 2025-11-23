#ifndef OBJECT_H
#define OBJECT_H

#include <string>

#include <glm/glm.hpp>

#include "vertexbuffer.h"
#include "vertexarray.h"
#include "texture.h"
#include "uvbuffer.h"

/// On crée une énumération de nos types de tétrominos pour mieux gérer la génération, la suppression et les collisions
/// Basé sur l'hypothèse qu'on ne créera désormais plus de que des blocs de jeu (et le terrain)!

enum class PieceType {
    //Le mino de base
    MINO,
    //Nos différents tétrominos
    LINE,
    BLOCK,
    TEE,
    RIGHT_SNAKE,
    LEFT_SNAKE,
    LEFT_GUN,
    RIGHT_GUN,
    //Le terrain (nécessaire, car on va demander dans object le type de pièce
    TERRAIN
};

class Object
{
public:
    Object(std::vector< glm::vec3 > vertices, std::vector< glm::vec2 > uvs, std::string texturePath, PieceType type);
    ~Object();
    void Bind() const;
    void Unbind() const;
    void Draw() const;
    glm::vec3 position;
    glm::vec3 rotationAngles;
    glm::mat4 getModelMatrix();
    PieceType pieceType;

private:
    VertexBuffer *m_vb;
    UVBuffer *m_uvsb;
    Texture *m_texture;


};

#endif // OBJECT_H
