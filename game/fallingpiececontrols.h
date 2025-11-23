#ifndef FALLINGPIECECONTROLS_H
#define FALLINGPIECECONTROLS_H

#include "controls.h"
#include "game/game.h"

class FallingPieceControls : public Controls
{
public:
    FallingPieceControls(GLFWwindow* window, Camera *camera, Game *Game);
    void update(float deltaTime, Shader *shader);
private:
    Game *game;
    bool aWasPressed;
    bool eWasPressed;
    bool sWasPressed;
};

#endif // FALLINGPIECECONTROLS_H
