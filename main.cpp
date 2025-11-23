#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "glm/glm.hpp"
#include <vector>
#include <algorithm>

#include "vertexbuffer.h"
#include "vertexarray.h"
#include "shader.h"
#include "renderer.h"
#include "camera.h"
#include "navigationcontrols.h"
#include "game/fallingpiececontrols.h"


//Les modèles
#include "models/tetrominos.h"
#include "models/terrain.h"

//Le jeu
#include "game/game.h"

using namespace std;


Game tetris;

//Pour faire du mouvement incrémental
float lastTime = glfwGetTime();
float currentTime, deltaTime;
float fallTimer = 0.0f;
const float FALL_INTERVAL = 0.7f;

int main()
{
    string path = "../..";
/////////////////////////Initialisation de GLFW/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    if(!glfwInit()){
        fprintf(stderr, "Failed to initialize GLFW\n");
        return -1;
    }


    glfwWindowHint(GLFW_SAMPLES, 4); //antialiasing
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); //version 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //version core

    // Cull triangles which normal is not towards the camera
    glEnable(GL_CULL_FACE);


/////////////////////////Ouverture de la fenêtre/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    //Définition de la taille de la fenêtre
    int width=600;
    int height=600;

    //On récupère les dimensions de l'écran pour créer la fenètre
    GLFWmonitor* primary = glfwGetPrimaryMonitor();
    glfwGetMonitorWorkarea(primary,nullptr,nullptr, &width, &height);

    //Enfin on crée la fenêtre
    GLFWwindow* window = glfwCreateWindow(width,height,"OpenGL_API",NULL,NULL);
    glfwSwapInterval(1);
    //On vérifie que l'initialisation a bien marché
    if (window==NULL){
        fprintf(stderr, "Erreur lors de la création de la fénêtre\n");
        glfwTerminate();
        return -1;
    }

    //Enfin on définit la fenêtre créée comme la fenêtre sur laquelle on va dessiner
    glfwMakeContextCurrent(window);



/////////////////////////Initialisation de GLEW/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    //Initialisation de GLEW
    glewExperimental=true;
    if (glewInit() != GLEW_OK){
        fprintf(stderr, "Erreur lors de l'initialisation de GLEW\n");
        return -1;
    }

/////////////////////////On crée un Renderer/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    Renderer renderer;


/////////////////////////On crée un Shader/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    Shader shader(path+"/shaders/SimpleVertexShader.vertexshader", path+"/shaders/SimpleFragmentShader.fragmentshader");
    shader.Bind();

/////////////////////////On crée un vertex array par cube /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    VertexArray va;
    va.Bind();


/////////////////////////On crée la camera et les contrôles/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    Camera cam(width, height);
    NavigationControls controls(window, &cam);
    FallingPieceControls pieceControls(window, &cam, &tetris);

/////////////////////////Création des formes à afficher/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    vector<glm::vec3> terrain_vertex_buffer = terrain_creator();

    // vector<glm::vec2> g_uv_buffer_data = {
    //     glm::vec2(0.000059f, 1.0f-0.000004f),
    //     glm::vec2(0.000103f, 1.0f-0.336048f),
    //     glm::vec2(0.335973f, 1.0f-0.335903f),
    //     glm::vec2(1.000023f, 1.0f-0.000013f),
    //     glm::vec2(0.667979f, 1.0f-0.335851f),
    //     glm::vec2(0.999958f, 1.0f-0.336064f),
    //     glm::vec2(0.667979f, 1.0f-0.335851f),
    //     glm::vec2(0.336024f, 1.0f-0.671877f),
    //     glm::vec2(0.667969f, 1.0f-0.671889f),
    //     glm::vec2(1.000023f, 1.0f-0.000013f),
    //     glm::vec2(0.668104f, 1.0f-0.000013f),
    //     glm::vec2(0.667979f, 1.0f-0.335851f),
    //     glm::vec2(0.000059f, 1.0f-0.000004f),
    //     glm::vec2(0.335973f, 1.0f-0.335903f),
    //     glm::vec2(0.336098f, 1.0f-0.000071f),
    //     glm::vec2(0.667979f, 1.0f-0.335851f),
    //     glm::vec2(0.335973f, 1.0f-0.335903f),
    //     glm::vec2(0.336024f, 1.0f-0.671877f),
    //     glm::vec2(1.000004f, 1.0f-0.671847f),
    //     glm::vec2(0.999958f, 1.0f-0.336064f),
    //     glm::vec2(0.667979f, 1.0f-0.335851f),
    //     glm::vec2(0.668104f, 1.0f-0.000013f),
    //     glm::vec2(0.335973f, 1.0f-0.335903f),
    //     glm::vec2(0.667979f, 1.0f-0.335851f),
    //     glm::vec2(0.335973f, 1.0f-0.335903f),
    //     glm::vec2(0.668104f, 1.0f-0.000013f),
    //     glm::vec2(0.336098f, 1.0f-0.000071f),
    //     glm::vec2(0.000103f, 1.0f-0.336048f),
    //     glm::vec2(0.000004f, 1.0f-0.671870f),
    //     glm::vec2(0.336024f, 1.0f-0.671877f),
    //     glm::vec2(0.000103f, 1.0f-0.336048f),
    //     glm::vec2(0.336024f, 1.0f-0.671877f),
    //     glm::vec2(0.335973f, 1.0f-0.335903f),
    //     glm::vec2(0.667969f, 1.0f-0.671889f),
    //     glm::vec2(1.000004f, 1.0f-0.671847f),
    //     glm::vec2(0.667979f, 1.0f-0.335851f)

    // } ;

    vector<glm::vec2> g_uv_buffer_data = {};

    //Initialisation du terrain
    Object terrain(terrain_vertex_buffer, g_uv_buffer_data, "", PieceType::TERRAIN);


    //On génère une unique pièce pour commencer
    tetris.spawn_piece();

/////////////////////////Création de la matrice MVP/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////




    cam.computeMatrices(width, height);
    glm::mat4 v = cam.getViewMatrix();
    glm::mat4 p = cam.getProjectionMatrix();

    //Pour le terrain
    glm::mat4 m_terrain = terrain.getModelMatrix();
    glm::mat4 mvp_terrain = p*v*m_terrain;
    shader.setUniformMat4f("MVP", mvp_terrain);

    //Pour la pièce qui tombe
    glm::mat4 m_falling = tetris.fallingPiece->getModelMatrix();
    glm::mat4 mvp_falling = p*v*m_falling;
    shader.setUniformMat4f("MVP", mvp_falling);



/////////////////////////Boucle de rendu/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


    // Assure que l'on peut capturer les touche de clavier
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

    //On indique la couleur de fond
    glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

    //On autorise les tests de profondeur

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);


    float lastTime = glfwGetTime();
    float currentTime, deltaTime;

    while(glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && !glfwWindowShouldClose(window)){

        currentTime = glfwGetTime();
        deltaTime = currentTime-lastTime;
        lastTime = currentTime;


        //to rotate the cube
        // o1.rotationAngles.y=currentTime;


        //pour faire tomber la pièce
        if (tetris.fallingPiece) {
            fallTimer += deltaTime;

            if (fallTimer >= FALL_INTERVAL) {
                fallTimer = 0.0f;

                // Try to move piece down
                tetris.fallingPiece->position.y -= 1.0f;

                if (tetris.checkCollision(tetris.fallingPiece)) {
                    // Move back up and lock
                    tetris.fallingPiece->position.y += 1.0f;
                    // std::cout << "AAAAAAA";
                    tetris.lockPiece(tetris.fallingPiece);
                }
            }
        }

        if (tetris.needNewPiece) {
            tetris.spawn_piece();
        }



        controls.update(deltaTime, &shader);
        pieceControls.update(deltaTime, &shader);
        cam.computeMatrices(width, height);

        v = cam.getViewMatrix();
        p = cam.getProjectionMatrix();


        ////////////////On commence par vider les buffers///////////////
        renderer.Clear();
        m_terrain = terrain.getModelMatrix();
        mvp_terrain = p*v*m_terrain;
        shader.setUniformMat4f("MVP", mvp_terrain);
        renderer.Draw(va, terrain, shader);

        for (auto* piece: tetris.stackedPieces){
            glm::mat4 m_piece = piece->getModelMatrix();
            glm::mat4 mvp = p*v* m_piece;
            shader.setUniformMat4f("MVP", mvp);
            renderer.Draw(va, *piece, shader);
        };

        if (tetris.fallingPiece) {
            m_falling = tetris.fallingPiece->getModelMatrix();
            mvp_falling = p*v*m_falling;
            shader.setUniformMat4f("MVP", mvp_falling);
            renderer.Draw(va, *tetris.fallingPiece, shader);
        }

        ////////////////Partie rafraichissement de l'image et des évènements///////////////
        //Swap buffers : frame refresh
        glfwSwapBuffers(window);
        //get the events
        glfwPollEvents();
    }
    glfwTerminate();

    return 0;
}
