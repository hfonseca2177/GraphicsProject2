#if defined(_MSC_VER) && (_MSC_VER >= 1310)
#	pragma warning(disable: 4996) // Disable the fopen, strcpy, sprintf being unsafe warning
#endif

#include "GLCommon.h"
#include <glm/glm.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <math.h>

#include "cVAOManager.h"
#include "cMesh.h"
#include "cShaderManager.h"
#include "cCameraControl.h"
#include "cShaderLoader.h"
#include "cModelCatalog.h"
#include "cGameManager.h"

#define GLT_IMPLEMENTATION
#include "gltext.h"

//Camera component control
cCameraControl camera = cCameraControl();
//Shader Loader 
cShaderLoader shaderLoader;
//Vertex Array Objects Manager
cVAOManager gVAOManager;

TrapOrTreasure::cGameManager* gameManager;


static void error_callback(int error, const char* description)
{
    fprintf(stderr, "Error: %s\n", description);
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
    else if(camera.IsResetCommand(key))
    {
        //reset camera
        camera.ResetCameraEye();
    }
    else if (key == GLFW_KEY_ENTER && action == GLFW_PRESS)
    {
        //Step the game
        gameManager->SearchForTreasure();
        std::cout << "SEEK" << std::endl;
    }
    else if(action == GLFW_PRESS)
    {
        //==============Camera Key Callback control=====================
        camera.CameraComand(key);
    }
}


int main(int argc, char* argv[])
{
    GLFWwindow* window;

    GLuint program = 0;

    GLint mvp_location = -1;
    
    //==============setting up window==================

    glfwSetErrorCallback(error_callback);

    if (!glfwInit())
    {
        return -1;
    }

    GLFWmonitor* monitor = glfwGetPrimaryMonitor();
    const GLFWvidmode* mode = glfwGetVideoMode(monitor);
    

  /*  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);*/

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

   
    glfwWindowHint(GLFW_RED_BITS, mode->redBits);
    glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
    glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
    glfwWindowHint(GLFW_ALPHA_BITS, 8);
    glfwWindowHint(GLFW_DEPTH_BITS, 24);
    glfwWindowHint(GLFW_STENCIL_BITS, 8);

    window = glfwCreateWindow(1200, 640, "Graphics Project 1", NULL, NULL);

    if (!window)
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwSetKeyCallback(window, key_callback);

    glfwShowWindow(window);
    glfwMakeContextCurrent(window);

    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

    glfwSwapInterval(1);

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    if (!gltInit())
    {
        fprintf(stderr, "Failed to initialize glText\n");
        glfwTerminate();
        return EXIT_FAILURE;
    }

    
    //==============Loading Shaders profiles===========
    
    shaderLoader.LoadShaders(program);

    //==============Instantiate Exhibition Matrices=====

    mvp_location = glGetUniformLocation(program, "MVP");

    GLint matModel_Location = glGetUniformLocation(program, "matModel");
    GLint matView_Location = glGetUniformLocation(program, "matView");
    GLint matProjection_Location = glGetUniformLocation(program, "matProjection");
    
    //==============Loading Models=====================
    
    cModelCatalog catalog = cModelCatalog();
    
    catalog.LoadModels(program, gVAOManager);
    
    std::vector<cModel*> models = catalog.GetModels();

    //==============TrapOrTreasure GameManager ========

    gameManager = TrapOrTreasure::cGameManager::GetInstance();
    gameManager->SetModels(models);
    gameManager->StartGame();

    GLTtext* heroScore = gltCreateText();
    GLTtext* heroStats = gltCreateText();
    GLTtext* currentLairItem = gltCreateText();
    GLTtext* lootsRemaining = gltCreateText();
    GLTtext* lootableFound = gltCreateText();
    GLTtext* statusResult = gltCreateText();

    //==============Window program loop================
    while (!glfwWindowShouldClose(window))
    {
        //==============Draw Models====================
        float ratio;
        int width, height;

        glfwGetFramebufferSize(window, &width, &height);

        ratio = width / (float)height;

        // Turn on the depth buffer
        glEnable(GL_DEPTH);         // Turns on the depth buffer
        glEnable(GL_DEPTH_TEST);    // Check if the pixel is already closer

        glViewport(0, 0, width, height);
        glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

        //Interact over all models in the index and load them on the scene
        glm::mat4 model;
        glm::mat4 projection;
        glm::mat4 view;
        
        for (unsigned int index = 0; index != models.size(); index++)
        {
            //Generate all transformations to the MVP
            model = models[index]->GetModelTransformation();
           
            projection = glm::perspective(0.6f,
                ratio,
                0.1f,
                1000.0f);

            view = glm::mat4(1.0f);

            // Updates camera position
            view = camera.RepositionCamera();
    
            glUseProgram(program);

            glUniformMatrix4fv(matModel_Location, 1, GL_FALSE, glm::value_ptr(model));
            glUniformMatrix4fv(matView_Location, 1, GL_FALSE, glm::value_ptr(view));
            glUniformMatrix4fv(matProjection_Location, 1, GL_FALSE, glm::value_ptr(projection));

            //Apply all Mesh color, lines and fill related options
            
            GLint bUseVertexColour_Location = glGetUniformLocation(program, "bUseVertexColour");
            GLint vertexColourOverride_Location = glGetUniformLocation(program, "vertexColourOverride");

            glUniform3f(vertexColourOverride_Location, 0.0f, 1.0f, 1.0f);
            glUniform1f(bUseVertexColour_Location, (float)GL_TRUE);
 
            cMesh* curMesh = models[index]->GetMesh();

            if (curMesh->bOverriveVertexColourHACK)
            {
                glUniform1f(bUseVertexColour_Location, (float)GL_TRUE);
                glUniform3f(vertexColourOverride_Location, 
                            curMesh->vertexColourOverrideHACK.r,
                            curMesh->vertexColourOverrideHACK.g,
                            curMesh->vertexColourOverrideHACK.b);
            }
            else
            {
                glUniform1f(bUseVertexColour_Location, (float)GL_FALSE);
            }
            
            if (camera.IsShowWireFrame())
            {
                glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            }
            else
            {
                glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            }

            sModelDrawInfo modelInfo;

            if ( gVAOManager.FindDrawInfoByModelName(models[index]->GetMesh()->meshName, modelInfo))
            {
                glBindVertexArray(modelInfo.VAO_ID);

                glDrawElements(GL_TRIANGLES,
                               modelInfo.numberOfIndices, 
                               GL_UNSIGNED_INT, 
                               (void*)0);

                glBindVertexArray(0);
            }

          
        }

        sGameStatus status = gameManager->GetStatus();

        gltSetText(heroScore, status.heroScore.c_str());
        gltSetText(heroStats, status.heroStats.c_str());
        gltSetText(currentLairItem, status.currentLairItem.c_str());
        gltSetText(lootsRemaining, status.lootsRemaining.c_str());
        gltSetText(lootableFound, status.lootableFound.c_str());
        gltSetText(statusResult, status.result.c_str());

        gltBeginDraw();

        gltColor(1.0f, 1.0f, 1.0f, 1.0f);
        gltDrawText2DAligned(heroScore, 0.0f, (GLfloat)height-20, 1.0f, GLT_LEFT, GLT_TOP);
        gltDrawText2DAligned(heroStats, 0.0f, (GLfloat)height-40, 1.0f, GLT_LEFT, GLT_TOP);
        gltColor(0.0f, 1.0f, 0.0f, 1.0f);
        gltDrawText2DAligned(currentLairItem, 0.0f, 20.0f, 1.0f, GLT_LEFT, GLT_BOTTOM);
        gltDrawText2DAligned(lootsRemaining, 0.0f, 40.0f, 1.0f, GLT_LEFT, GLT_BOTTOM);
        gltColor(1.0f, 0.0f, 1.0f, 1.0f);
        if (status.lootableFound != "")
        {
            gltDrawText2DAligned(lootableFound, (GLfloat)(width / 2), (height - 60), 1.0f, GLT_CENTER, GLT_CENTER);
        }
        gltDrawText2DAligned(statusResult, (GLfloat)(width / 2), (height -40), 1.0f, GLT_CENTER, GLT_CENTER);

        gltEndDraw();

        glfwSwapBuffers(window);
        glfwPollEvents();

    }

    gltDeleteText(heroScore);
    gltTerminate();

    //==============Exiting program====================
    glfwDestroyWindow(window);

    glfwTerminate();
    exit(EXIT_SUCCESS);
}
