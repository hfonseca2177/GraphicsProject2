
#include "GLCommon.h"
#include "globalThings.h"
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
#include <sstream>
#include <vector>
#include <fstream>

void DrawObject(
    cMesh* pCurrentMesh, 
    glm::mat4 matModel,
    GLint matModel_Location,
    GLint matModelInverseTranspose_Location,
    GLuint program,
    cVAOManager* pVAOManager);

int main(void)
{
    GLFWwindow* pWindow;

    GLuint program = 0;

    GLint mvp_location = -1;

    glfwSetErrorCallback(GLFW_error_callback);

    if ( ! glfwInit() )
    {
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

    pWindow = glfwCreateWindow(1200, 640, "Project 2", NULL, NULL);

    if (!pWindow )
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwSetKeyCallback(pWindow, GLFW_key_callback);
    glfwSetCursorEnterCallback( pWindow, GLFW_cursor_enter_callback );
    glfwSetCursorPosCallback( pWindow, GLFW_cursor_position_callback );
    glfwSetScrollCallback( pWindow, GLFW_scroll_callback );
    glfwSetMouseButtonCallback( pWindow, GLFW_mouse_button_callback );
    glfwSetWindowSizeCallback( pWindow, GLFW_window_size_callback );

    glfwMakeContextCurrent(pWindow);
    gladLoadGLLoader( (GLADloadproc) glfwGetProcAddress);
    glfwSwapInterval(1);

    GLint max_uniform_location = 0;
    GLint* p_max_uniform_location = NULL;
    p_max_uniform_location = &max_uniform_location;
    glGetIntegerv(GL_MAX_UNIFORM_LOCATIONS, p_max_uniform_location);

    // Create global things
    ::g_StartUp(pWindow);
    
    ::g_pFlyCamera->setEye( glm::vec3(0.0f, 0.0f, 0.0f) );

    //Load and map Shader scripts and variables
    ::g_pShaderLoader->LoadShaders(program, ::g_pShaderManager);

    glUseProgram(program);

    // Get "uniform locations" (aka the registers these are in)
    mvp_location = glGetUniformLocation(program, "MVP");

    GLint matModel_Location = g_pShaderLoader->GetModelLocation();
    GLint matView_Location = g_pShaderLoader->GetViewLocation();
    GLint matProjection_Location = g_pShaderLoader->GetProjectionLocation();
    GLint matModelInverseTranspose_Location = g_pShaderLoader->GetModelInverseTransposeLocation();

    //Scene manager to setup lights
    ::g_pSceneManager->SetupLights();

    // Get the uniform locations of the light shader values
    ::g_pTheLights->SetUpUniformLocations(program);

    //Set paths
    ::g_pVAOManager->setFilePath("assets/models/");
    ::g_pTextureManager->SetBasePath("assets/textures");

    //Load Scene Objects
    ::g_pSceneManager->LoadSceneModels(program);

    // Add a skybox texture
    std::string errorTextString;
    if (!::g_pTextureManager->CreateCubeTextureFromBMPFiles("Space01",
       //     "violentdays_rt.bmp",    /* posX_fileName */
       //"violentdays_lf.bmp",     /*negX_fileName */
       //"violentdays_dn.bmp",     /*posY_fileName*/
       //"violentdays_up.bmp",       /*negY_fileName*/
       //"violentdays_bk.bmp",     /*posZ_fileName*/
       //"violentdays_ft.bmp",    /*negZ_fileName*/
        //"TropicalSunnyDayRight2048.bmp",    /* posX_fileName */
        //"TropicalSunnyDayLeft2048.bmp",     /*negX_fileName */
        //"TropicalSunnyDayDown2048.bmp",     /*posY_fileName*/
        //"TropicalSunnyDayUp2048.bmp",       /*negY_fileName*/
        //"TropicalSunnyDayBack2048.bmp",     /*posZ_fileName*/
        //"TropicalSunnyDayFront2048.bmp",    /*negZ_fileName*/
        "SpaceBox_right1_posX.bmp",     /* posX_fileName */
        "SpaceBox_left2_negX.bmp",      /*negX_fileName */
        "SpaceBox_top3_posY.bmp",       /*posY_fileName*/
        "SpaceBox_bottom4_negY.bmp",    /*negY_fileName*/
        "SpaceBox_front5_posZ.bmp",     /*posZ_fileName*/
        "SpaceBox_back6_negZ.bmp",      /*negZ_fileName*/
        true, errorTextString))
    {
        std::cout << "Didn't load because: " << errorTextString << std::endl;
    }

    //
    //if (!::g_pTextureManager->CreateCubeTextureFromBMPFiles("Space01",
    //    "violentdays_rt.bmp",    /* posX_fileName */
    //    "violentdays_lf.bmp",     /*negX_fileName */
    //    "violentdays_dn.bmp",     /*posY_fileName*/
    //    "violentdays_up.bmp",       /*negY_fileName*/
    //    "violentdays_bk.bmp",     /*posZ_fileName*/
    //    "violentdays_ft.bmp",    /*negZ_fileName*/
    //    true, errorTextString))
    //{
    //    std::cout << "Didn't load because: " << errorTextString << std::endl;
    //}
   
    //{
    //    GLuint TextureNumber = ::g_pTextureManager->getTextureIDFromName("Space01");
    //    GLuint textureUnit = 40;			// Texture unit go from 0 to 79
    //    glActiveTexture(textureUnit + GL_TEXTURE0);	// GL_TEXTURE0 = 33984
    //    // ***NOTE*** Binding to a CUBE MAP not a 2D Texture
    //    glBindTexture(GL_TEXTURE_CUBE_MAP, TextureNumber);
    //    // THIS SHOULDN'T BE HERE as it's the same each time and getUniformLocation is SLOOOOOOW
    //    GLint cubeMap_00_LocID = glGetUniformLocation(program, "cubeMap_00");
    //    glUniform1i(cubeMap_00_LocID, textureUnit);

    //}
    sModelDrawInfo drawInfo;
    ::g_pVAOManager->LoadModelIntoVAO("Isosphere_Smooth_Inverted_Normals_for_SkyBox.ply", drawInfo, program);

    // Create a skybox object (a sphere with inverted normals that moves with the camera eye)
    cMesh* pSkyBox = new cMesh();
    pSkyBox->meshName = "Isosphere_Smooth_Inverted_Normals_for_SkyBox.ply";
    pSkyBox->setUniformScale(::g_pFlyCamera->nearPlane * 1000.0f);
    
    pSkyBox->bDontLight = false;
    const double MAX_DELTA_TIME = 0.1;  // 100 ms
    double previousTime = glfwGetTime();

    //Main loop
    while (!glfwWindowShouldClose(pWindow))
    {
        float ratio;
        int width, height;
        glm::mat4 matModel;             // used to be "m"; Sometimes it's called "world"
        glm::mat4 matProjection;        // used to be "p";
        glm::mat4 matView;              // used to be "v";

        double currentTime = glfwGetTime();

        double deltaTime = currentTime - previousTime;
        deltaTime = (deltaTime > MAX_DELTA_TIME ? MAX_DELTA_TIME : deltaTime);
        previousTime = currentTime;

        glfwGetFramebufferSize(pWindow, &width, &height);
        ratio = width / (float)height;

        // Turn on the depth buffer
        glEnable(GL_DEPTH);         // Turns on the depth buffer
        glEnable(GL_DEPTH_TEST);    // Check if the pixel is already closer

        glViewport(0, 0, width, height);
        glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

        // *******************************************************
        // Screen is cleared and we are ready to draw the scene...
        // *******************************************************

        // Update the title text
        glfwSetWindowTitle(pWindow, ::g_TitleText.c_str() );

        // Copy the light information into the shader to draw the scene
        ::g_pTheLights->CopyLightInfoToShader();

        matProjection = glm::perspective(
            ::g_pFlyCamera->FOV,       
            ratio,
            ::g_pFlyCamera->nearPlane,
            ::g_pFlyCamera->farPlane);

        //Update camera position
        ::g_pFlyCamera->Update(deltaTime);

        glm::vec3 cameraEye = ::g_pFlyCamera->getEye();
        glm::vec3 cameraAt = ::g_pFlyCamera->getAtInWorldSpace();
        glm::vec3 cameraUp = ::g_pFlyCamera->getUpVector();

        matView = glm::mat4(1.0f);
        matView = glm::lookAt( cameraEye,
                               cameraAt,
                               cameraUp );


        glUniformMatrix4fv(g_pShaderLoader->GetViewLocation(),
                            1, GL_FALSE, glm::value_ptr(matView));

        glUniformMatrix4fv(matProjection_Location, 1, GL_FALSE, glm::value_ptr(matProjection));

        //Skybox
        {
            //======================== Set up skybox ========================
            GLint bIsSkyBox_LocID = glGetUniformLocation(program, "bIsSkyBox");
            glUniform1f(bIsSkyBox_LocID, (GLfloat)GL_TRUE);

            glDisable(GL_DEPTH_TEST);
            // Move the "skybox object" with the camera
            pSkyBox->positionXYZ = ::g_pFlyCamera->getEye();

            DrawObject(
                pSkyBox, glm::mat4(1.0f),
                matModel_Location, matModelInverseTranspose_Location,
                program, ::g_pVAOManager);

            glUniform1f(bIsSkyBox_LocID, (GLfloat)GL_FALSE);
            glEnable(GL_DEPTH_TEST);
            glDepthMask(GL_TRUE);
        }

        //Scene loaded models
        std::vector<cModel*> models = ::g_pSceneManager->GetModels();

        //Draw each scene object
        for (unsigned int index = 0; index != models.size(); index++)
        {
            
            cMesh* pCurrentMesh = models[index]->GetMesh();
            matModel = glm::mat4(1.0f);


            DrawObject(pCurrentMesh,
                matModel,
                matModel_Location,
                matModelInverseTranspose_Location,
                program,
                ::g_pVAOManager);

        }

        // "Present" what we've drawn.
        glfwSwapBuffers(pWindow);        // Show what we've drawn

        // Process any events that have happened
        glfwPollEvents();

        // Handle OUR keyboard, mouse stuff
        handleAsyncKeyboard(pWindow, deltaTime);
        handleAsyncMouse(pWindow, deltaTime);

    }//while (!glfwWindowShouldClose(window))

    // All done, so delete things...
    ::g_ShutDown(pWindow);


    glfwDestroyWindow(pWindow);

    glfwTerminate();
    exit(EXIT_SUCCESS);
}

