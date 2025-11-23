#include "fallingpiececontrols.h"
#include "imgui/imgui.h"

FallingPieceControls::FallingPieceControls(GLFWwindow *window, Camera *camera, Game *game):
    Controls(window, camera), game(game),
    aWasPressed(false), eWasPressed(false), sWasPressed(false)
{
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}

void FallingPieceControls::update(float deltaTime, Shader * shader){
    // On test d'abord si on est sur la fenêtre imgui ou pas
    if (/*!io.WantCaptureMouse*/true){
        //On va faire en sorte qu'on peut bouger les pièces une seule fois quand la touche est pressée
        bool aPressed = glfwGetKey(m_Window, GLFW_KEY_Q) == GLFW_PRESS;
        bool ePressed = glfwGetKey(m_Window, GLFW_KEY_E) == GLFW_PRESS;
        bool sPressed = glfwGetKey(m_Window, GLFW_KEY_S) == GLFW_PRESS;

        Object *fallingPiece = game->fallingPiece->object;
        if (aPressed && !aWasPressed){
            fallingPiece->position.x -= 1.0f;
            if (game->checkCollision(fallingPiece)){
                fallingPiece->position.x += 1.0f;
            }
        }
        else if (ePressed && !eWasPressed){
            fallingPiece->position.x += 1.0f;
            if (game->checkCollision(fallingPiece)){
                fallingPiece->position.x -= 1.0f;
            }
        }
        else if (sPressed && !sWasPressed){
            fallingPiece->position.y -= 1.0f;
            if (game->checkCollision(fallingPiece)) {
                fallingPiece->position.y += 1.0f;
            }
        }

        //On met à jour l'état
        aWasPressed = aPressed;
        eWasPressed = ePressed;
        sWasPressed = sPressed;
    }
}
