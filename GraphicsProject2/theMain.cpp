
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


// Function signature for DrawObject()
void DrawObject(
    cMesh* pCurrentMesh, 
    glm::mat4 matModel,
    GLint matModel_Location,
    GLint matModelInverseTranspose_Location,
    GLuint program,
    cVAOManager* pVAOManager);


void DrawDebugObjects(
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
    
    g_bShowDebugShere = false;

    ::g_pFlyCamera->setEye( glm::vec3(0.0f, 0.0f, 0.0f) );

    cShaderManager::cShader vertShader;
    vertShader.fileName = "assets/shaders/vertShader_01.glsl";
        
    cShaderManager::cShader fragShader;
    fragShader.fileName = "assets/shaders/fragShader_01.glsl";

    if (::g_pShaderManager->createProgramFromFile("Shader#1", vertShader, fragShader))
    {
        std::cout << "Shader compiled OK" << std::endl;
        program = ::g_pShaderManager->getIDFromFriendlyName("Shader#1");
    }
    else
    {
        std::cout << "Error making shader program: " << std::endl;
        std::cout << ::g_pShaderManager->getLastError() << std::endl;
    }

    glUseProgram(program);

    cShaderManager::cShaderProgram* pShaderProc = ::g_pShaderManager->pGetShaderProgramFromFriendlyName("Shader#1");

    int theUniformIDLoc = -1;
    theUniformIDLoc = glGetUniformLocation(program, "matModel");
    pShaderProc->mapUniformName_to_UniformLocation["matModel"] = theUniformIDLoc;
    
    // Or...
    pShaderProc->mapUniformName_to_UniformLocation["matModel"] = glGetUniformLocation(program, "matModel");
    pShaderProc->mapUniformName_to_UniformLocation["matView"] = glGetUniformLocation(program, "matView");
    pShaderProc->mapUniformName_to_UniformLocation["matProjection"] = glGetUniformLocation(program, "matProjection");
    pShaderProc->mapUniformName_to_UniformLocation["matModelInverseTranspose"] = glGetUniformLocation(program, "matModelInverseTranspose");

    pShaderProc->mapUniformName_to_UniformLocation["wholeObjectSpecularColour"] = glGetUniformLocation(program, "wholeObjectSpecularColour");
    // .. and so on...
    pShaderProc->mapUniformName_to_UniformLocation["theLights[0].position"] = glGetUniformLocation(program, "wholeObjectSpecularColour");
    // ... and so on..
    // ************************************************

    //GLint mvp_location = -1;
    mvp_location = glGetUniformLocation(program, "MVP");

    // Get "uniform locations" (aka the registers these are in)
    GLint matModel_Location = glGetUniformLocation(program, "matModel");
    GLint matView_Location = glGetUniformLocation(program, "matView");
    GLint matProjection_Location = glGetUniformLocation(program, "matProjection");
    GLint matModelInverseTranspose_Location = glGetUniformLocation(program, "matModelInverseTranspose");

    ::g_pTheLights->theLights[0].position = glm::vec4(20.0f, -35.0f, 50.0f, 1.0f);
    ::g_pTheLights->theLights[0].diffuse *= 0.001f;
    ::g_pTheLights->theLights[0].param1.x = 2.0f;
    ::g_pTheLights->theLights[0].direction = glm::vec4(20.0f, -15.0f, 380.0f, 1.0f);
    ::g_pTheLights->theLights[0].param1.y = 5.0f;
    ::g_pTheLights->theLights[0].param1.z = 5.0f;
    ::g_pTheLights->theLights[0].atten.y = 0.0001f;
    ::g_pTheLights->theLights[0].atten.z = 0.00001f;
    ::g_pTheLights->theLights[0].param2.x = 1.0f;
      

    //::g_pTheLights->theLights[0].position = glm::vec4(0.0f, 10.0f,35.0f, 1.f);
    //::g_pTheLights->theLights[0].diffuse *= 0.001f;
    ////::g_pTheLights->theLights[0].diffuse = glm::vec4(0.9922f, 0.9843f, 0.8275f, 1.0f);
    //::g_pTheLights->theLights[0].param1.x = 2.0f;
    //::g_pTheLights->theLights[0].direction = glm::vec4(0.0f, 55.0f, 0.0f, 1.f);
    //::g_pTheLights->theLights[0].param1.y = 5.0f;
    //::g_pTheLights->theLights[0].param1.z = 5.0f;
    //::g_pTheLights->theLights[0].atten.y = 0.0001f;
    //::g_pTheLights->theLights[0].atten.z = 0.00001f;
    //::g_pTheLights->theLights[0].param2.x = 1.0f;
    
    ::g_pTheLights->theLights[1].position = glm::vec4(0.0f, 45.0f, 0.0f, 1.f);
    //::g_pTheLights->theLights[1].diffuse *= 0.81f;
    ::g_pTheLights->theLights[1].diffuse = glm::vec4(0.9922f, 0.9843f, 0.8275f, 1.0f);
    ::g_pTheLights->theLights[1].param1.x = 2.0f;
    ::g_pTheLights->theLights[1].direction = glm::vec4(-0.0f, -15.0f, 0.0f, 1.f);
    ::g_pTheLights->theLights[1].param1.y = 5.0f;
    ::g_pTheLights->theLights[1].param1.z = 5.0f;
    ::g_pTheLights->theLights[1].atten.y = 0.0001f;
    ::g_pTheLights->theLights[1].atten.z = 0.00001f;
    ::g_pTheLights->theLights[1].param2.x = 1.0f;

 /*   ::g_pTheLights->theLights[1].position = glm::vec4(-30.0f, -25.0f, 380.0f, 1.f);
    ::g_pTheLights->theLights[1].atten.y = 0.0001f;
    ::g_pTheLights->theLights[1].atten.z = 0.00001f;
    ::g_pTheLights->theLights[1].param1.x = 1.0f;
    ::g_pTheLights->theLights[1].direction = glm::vec4(-20.0f, -15.0f, 380.0f, 1.f);
    ::g_pTheLights->theLights[1].diffuse = glm::vec4(0.9922f, 0.9843f, 0.8275f, 1.0f);
    ::g_pTheLights->theLights[1].param2.x = 1.0f;*/

   // ::g_pTheLights->theLights[3].position = glm::vec4( 0.0f, 500.0f, 0.0f, 1.0f);
   //::g_pTheLights->theLights[3].diffuse = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
   //::g_pTheLights->theLights[3].param1.x = 0.0f;   
   //::g_pTheLights->theLights[3].atten.x = 0.0f;
   //::g_pTheLights->theLights[3].atten.y = 0.001f;
   //::g_pTheLights->theLights[3].atten.z = 0.0001f;
   //::g_pTheLights->theLights[3].param2.x = 1.0f;

    // Get the uniform locations of the light shader values
    ::g_pTheLights->SetUpUniformLocations(program);
        
    // Set up the debug sphere object
    ::g_pDebugSphere = new cMesh();
    ::g_pDebugSphere->meshName = "Sphere_xyz_n_rgba.ply";
    ::g_pDebugSphere->bIsWireframe = true;
    ::g_pDebugSphere->bUseObjectDebugColour = true;
    ::g_pDebugSphere->objectDebugColourRGBA = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
    ::g_pDebugSphere->bDontLight = false;
    ::g_pDebugSphere->scale = 1.0f;
    ::g_pDebugSphere->positionXYZ = ::g_pTheLights->theLights[2].position;
    // Give this a friendly name
    ::g_pDebugSphere->friendlyName = "Debug Sphere";
    //// Then I could make a small function that searches for that name

    ::g_pVAOManager->setFilePath("assets/models/");

    std::vector<std::string> vecModelsToLoad;

    //Scene models
    vecModelsToLoad.push_back("Sphere_xyz_n_rgba.ply");
    vecModelsToLoad.push_back("copernicus_crater.ply");
    vecModelsToLoad.push_back("space_exploration_vehicle.ply");
    vecModelsToLoad.push_back("SM_props_inspect.ply");
    vecModelsToLoad.push_back("z2_spacesuit.ply");
    vecModelsToLoad.push_back("VOG25M.ply");
    vecModelsToLoad.push_back("ScifiBox.ply");
    vecModelsToLoad.push_back("Isosphere_Smooth_Inverted_Normals_for_SkyBox.ply");
    vecModelsToLoad.push_back("carrier01.ply");

    
    unsigned int totalVerticesLoaded = 0;
    unsigned int totalTrianglesLoaded = 0;
    for (std::vector<std::string>::iterator itModel = vecModelsToLoad.begin(); itModel != vecModelsToLoad.end(); itModel++)
    {
        sModelDrawInfo theModel;
        std::string modelName = *itModel;
        std::cout << "Loading " << modelName << "...";
        if ( !::g_pVAOManager->LoadModelIntoVAO(modelName, theModel, program) )
        {
            std::cout << "didn't work because: " << std::endl;
            std::cout << ::g_pVAOManager->getLastError(true) << std::endl;
        }
        else
        {
            std::cout << "OK." << std::endl;
            std::cout << "\t" << theModel.numberOfVertices << " vertices and " << theModel.numberOfTriangles << " triangles loaded." << std::endl;
            totalTrianglesLoaded += theModel.numberOfTriangles;
            totalVerticesLoaded += theModel.numberOfVertices;
        }
    }

    bool bDontLight = false;

    cMesh* crater = new cMesh();
    crater->meshName = "copernicus_crater.ply";
    crater->positionXYZ = glm::vec3(0.0f, -15.0f, 0.0f);
    crater->textureNames[0] = "copernicus_crater_copernicus_crater_mat_BaseColor.bmp";
    crater->textureRatios[0] = 0.7f;
    crater->friendlyName = "crater";
    crater->bDontLight = bDontLight;
    //crater->wholeObjectSpecularRGB = glm::vec3(0.128f, 0.128f, 0.255f);
    ::g_selectedObject = 1;
    ::g_vec_pMeshes.push_back(crater);

    cMesh* vehicle = new cMesh();
    vehicle->meshName = "space_exploration_vehicle.ply";
    vehicle->positionXYZ = glm::vec3(-20.0f, -5.0f, 380.0f);
    vehicle->scale = 0.5f;
    vehicle->orientationXYZ.y = 3.14;
    vehicle->textureNames[0] = "vehicle_baseColor.bmp";
    vehicle->textureRatios[0] = 1.0f;
    vehicle->friendlyName = "vehicle";
    vehicle->bDontLight = bDontLight;
    

    ::g_vec_pMeshes.push_back(vehicle);

    {
        cMesh* newModel = new cMesh();
        newModel->meshName = "SM_props_inspect.ply";
        newModel->positionXYZ = glm::vec3(-140.0f, -5.0f, 230.0f);
        newModel->scale = 0.2f;
        //newModel->orientationXYZ.y = 3.14;
        newModel->textureNames[0] = "T_T_props_B.bmp";
        newModel->textureRatios[0] = 1.0f;
 /*       newModel->textureNames[1] = "details_BaseColor.bmp";
        newModel->textureRatios[1] = 1.0f;*/
        newModel->friendlyName = "props";
        newModel->bDontLight = bDontLight;

        ::g_vec_pMeshes.push_back(newModel);
    }

    {
        cMesh* newModel = new cMesh();
        newModel->meshName = "z2_spacesuit.ply";
        newModel->positionXYZ = glm::vec3(0.0f, -5.0f, 50.0f);
        newModel->scale = 0.2f;
        //newModel->orientationXYZ.y = 3.14;
        newModel->textureNames[0] = "suit_baseColor.bmp";
        newModel->textureRatios[0] = 1.0f;
        /*       newModel->textureNames[1] = "details_BaseColor.bmp";
               newModel->textureRatios[1] = 1.0f;*/
        newModel->friendlyName = "suit";
        newModel->bDontLight = bDontLight;

        ::g_vec_pMeshes.push_back(newModel);
    }

    {
        cMesh* newModel = new cMesh();
        newModel->meshName = "VOG25M.ply";
        newModel->positionXYZ = glm::vec3(-20.0f, -5.0f, 10.0f);
        newModel->scale = 0.2f;
        //newModel->orientationXYZ.y = 3.14;
        newModel->textureNames[0] = "paper.bmp";
        newModel->textureRatios[0] = 1.0f;
   
        newModel->friendlyName = "vog";
        newModel->bDontLight = bDontLight;

        ::g_vec_pMeshes.push_back(newModel);
    }

    {
        cMesh* newModel = new cMesh();
        newModel->meshName = "ScifiBox.ply";
        newModel->positionXYZ = glm::vec3(30.0f, -5.0f, 188.0f);
        newModel->scale = 10.0f;
        //newModel->orientationXYZ.y = 3.14;
        newModel->textureNames[0] = "DefaultMaterial_Roughness.bmp";
        newModel->textureRatios[0] = 1.0f;

        newModel->friendlyName = "box";
        newModel->bDontLight = bDontLight;

        ::g_vec_pMeshes.push_back(newModel);
    }

    {
        cMesh* newModel = new cMesh();
        newModel->meshName = "ScifiBox.ply";
        newModel->positionXYZ = glm::vec3(70.0f, -5.0f, 188.0f);
        newModel->scale = 10.0f;
        newModel->orientationXYZ.y = 0.74;
        newModel->textureNames[0] = "DefaultMaterial_Roughness.bmp";
        newModel->textureRatios[0] = 1.0f;
        newModel->friendlyName = "box2";
        newModel->bDontLight = bDontLight;
        ::g_vec_pMeshes.push_back(newModel);
    }

    {
        cMesh* newModel = new cMesh();
        newModel->meshName = "carrier01.ply";
        newModel->positionXYZ = glm::vec3(-420.0f, 185.0f, 1380.0f);
        newModel->scale = 110.0f;
        newModel->orientationXYZ.y = 0.34;
        newModel->textureNames[0] = "carrier01_diffuse.bmp";
        newModel->textureRatios[0] = 1.0f;
        newModel->friendlyName = "carrier";
        newModel->bDontLight = bDontLight;
        ::g_vec_pMeshes.push_back(newModel);
    }
    
           
    
    // Load the textures
    ::g_pTextureManager->SetBasePath("assets/textures");
    ::g_pTextureManager->Create2DTextureFromBMPFile("copernicus_crater_copernicus_crater_mat_BaseColor.bmp", true);
    ::g_pTextureManager->Create2DTextureFromBMPFile("vehicle_baseColor.bmp", true);
    ::g_pTextureManager->Create2DTextureFromBMPFile("T_T_props_B.bmp", true);
    ::g_pTextureManager->Create2DTextureFromBMPFile("suit_baseColor.bmp", true);
    ::g_pTextureManager->Create2DTextureFromBMPFile("main_baseColor.bmp", true);
    ::g_pTextureManager->Create2DTextureFromBMPFile("paper.bmp", true);
    ::g_pTextureManager->Create2DTextureFromBMPFile("DefaultMaterial_Roughness.bmp", true);
    ::g_pTextureManager->Create2DTextureFromBMPFile("carrier01_diffuse.bmp", true);
    

    // Add a skybox texture
    std::string errorTextString;
    
    if (!::g_pTextureManager->CreateCubeTextureFromBMPFiles("violentdays",
        "violentdays_rt.bmp",    /* posX_fileName */
        "violentdays_lf.bmp",     /*negX_fileName */
        "violentdays_dn.bmp",     /*posY_fileName*/
        "violentdays_up.bmp",       /*negY_fileName*/
        "violentdays_bk.bmp",     /*posZ_fileName*/
        "violentdays_ft.bmp",    /*negZ_fileName*/
        true, errorTextString))
    {
        std::cout << "Didn't load because: " << errorTextString << std::endl;
    }
   
    {
        //GLuint TextureNumber = ::g_pTextureManager->getTextureIDFromName(pCurrentMesh->textureNames[3]);
        GLuint TextureNumber = ::g_pTextureManager->getTextureIDFromName("violentdays");

        // Be careful that you don't mix up the 2D and the cube assignments for the texture units
        //
        // Here, I'll say that the cube maps start at texture unit 40
        //
        GLuint textureUnit = 40;			// Texture unit go from 0 to 79
        glActiveTexture(textureUnit + GL_TEXTURE0);	// GL_TEXTURE0 = 33984

        // ***NOTE*** Binding to a CUBE MAP not a 2D Texture
        glBindTexture(GL_TEXTURE_CUBE_MAP, TextureNumber);

        // THIS SHOULDN'T BE HERE as it's the same each time and getUniformLocation is SLOOOOOOW
        GLint cubeMap_00_LocID = glGetUniformLocation(program, "cubeMap_00");
        glUniform1i(cubeMap_00_LocID, textureUnit);

    }
    

    // Create a skybox object (a sphere with inverted normals that moves with the camera eye)
    cMesh* pSkyBox = new cMesh();
    pSkyBox->meshName = "Isosphere_Smooth_Inverted_Normals_for_SkyBox.ply";
    pSkyBox->scale = 5'000.0f;
    pSkyBox->positionXYZ = ::g_pFlyCamera->getEye();

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

        // Place the "debug sphere" at the same location as the selected light (again)
        ::g_pDebugSphere->positionXYZ = ::g_pTheLights->theLights[0].position;
        

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


        cShaderManager::cShaderProgram* pShaderProc = ::g_pShaderManager->pGetShaderProgramFromFriendlyName("Shader#1");

        glUniformMatrix4fv( pShaderProc->getUniformID_From_Name("matView"),
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
        }

        //Draw each scene object
        for (unsigned int index = 0; index != ::g_vec_pMeshes.size(); index++)
        {
            
            cMesh* pCurrentMesh = ::g_vec_pMeshes[index];
            matModel = glm::mat4(1.0f);
            //trasparence
            {
                GLint bDiscardTransparencyWindowsOn_LodID = glGetUniformLocation(program, "bDiscardTransparencyWindowsOn");
                // Turn discard transparency off
                glUniform1f(bDiscardTransparencyWindowsOn_LodID, (GLfloat)GL_FALSE);
                               
                if (pCurrentMesh->friendlyName == "vog")
                {
                    
                    GLuint discardTextureNumber = ::g_pTextureManager->getTextureIDFromName("paper.bmp");
                    // I'm picking texture unit 30 since it's not in use.
                    GLuint discardTextureUnit = 30;			// Texture unit go from 0 to 79
                    glActiveTexture(discardTextureUnit + GL_TEXTURE0);	// GL_TEXTURE0 = 33984
                    glBindTexture(GL_TEXTURE_2D, discardTextureNumber);
                    GLint discardTexture_LocID = glGetUniformLocation(program, "discardTexture");
                    glUniform1i(discardTexture_LocID, discardTextureUnit);

                    // Turn discard function on
                    glUniform1f(bDiscardTransparencyWindowsOn_LodID, (GLfloat)GL_TRUE);
                }
            }



            DrawObject(pCurrentMesh,
                matModel,
                matModel_Location,
                matModelInverseTranspose_Location,
                program,
                ::g_pVAOManager);

        }

        DrawDebugObjects(matModel_Location, matModelInverseTranspose_Location, program, ::g_pVAOManager);

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





void DrawDebugObjects(
        GLint matModel_Location,
        GLint matModelInverseTranspose_Location,
        GLuint program,
        cVAOManager* pVAOManager)
{

    if (::g_bShowDebugShere)
    {
        {   // Draw a sphere where the camera is looking.
            // Take the at - eye --> vector 
            glm::vec3 eye = ::g_pFlyCamera->getEye();
            glm::vec3 at = ::g_pFlyCamera->getAtInWorldSpace();

            glm::vec3 deltaDirection = at - eye;
            // Normalize to make this vector 1.0 units in length
            deltaDirection = glm::normalize(deltaDirection);

            float SphereDistanceFromCamera = 300.0f;
            glm::vec3 sphereLocation =
                eye + (deltaDirection * SphereDistanceFromCamera);

            // Draw the sphere

            ::g_pDebugSphere->positionXYZ = sphereLocation;
            ::g_pDebugSphere->scale = 5.0f;
            ::g_pDebugSphere->objectDebugColourRGBA = glm::vec4(1.0f, 0.0f, 1.0f, 1.0f);

            DrawObject(::g_pDebugSphere,
                glm::mat4(1.0f),
                matModel_Location,
                matModelInverseTranspose_Location,
                program,
                ::g_pVAOManager);

        }//Draw a sphere where the camera is looking.

    }

    if ( ::g_bShowDebugShere )
    {
        // Draw other things, like debug objects, UI, whatever
        glm::mat4 matModelDS = glm::mat4(1.0f);  // "Identity" ("do nothing", like x1)

        // Draw a small white shere at the location of the light
        sLight& currentLight = ::g_pTheLights->theLights[::g_selectedLight];

        ::g_pDebugSphere->positionXYZ = currentLight.position;

        ::g_pDebugSphere->scale = 1.0f;
        ::g_pDebugSphere->objectDebugColourRGBA = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
        DrawObject(::g_pDebugSphere,
                   matModelDS,
                   matModel_Location,
                   matModelInverseTranspose_Location,
                   program,
                   ::g_pVAOManager);

        // Save old debug sphere model name
        std::string oldDebugSphereModel = ::g_pDebugSphere->meshName;

        const float LOW_RES_SPHERE_DISTANCE = 50.0f;
        const std::string LOW_RES_SPHERE_MODEL = "ISO_Shphere_flat_3div_xyz_n_rgba.ply";
        const std::string HIGH_RES_SPHERE_MODEL = "ISO_Shphere_flat_4div_xyz_n_rgba.ply";

        //float calcApproxDistFromAtten( 
        //      float targetLightLevel, 
        //      float accuracy, 
        //      float infiniteDistance, 
        //      float constAttenuation, 
        //      float linearAttenuation,  
        //      float quadraticAttenuation, 
        //	    unsigned int maxIterations = DEFAULTMAXITERATIONS /*= 50*/ );

                // How far away is 95% brightness?
        float distTo95Percent = ::g_pTheLights->lightHelper.calcApproxDistFromAtten(0.95f,    /* the target light level I want*/
                                                                          0.01f,    /*accuracy - how close to 0.25f*/
                                                                          10000.0f, /*infinity away*/
                                                                          currentLight.atten.x, /*const atten*/
                                                                          currentLight.atten.y, /*linear atten*/
                                                                          currentLight.atten.z, /*quadratic atten*/
                                                                          cLightHelper::DEFAULTMAXITERATIONS);
        // Draw a red sphere at 95%
        ::g_pDebugSphere->scale = distTo95Percent;
        ::g_pDebugSphere->objectDebugColourRGBA = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);

        ::g_pDebugSphere->meshName = (::g_pDebugSphere->scale < LOW_RES_SPHERE_DISTANCE ? LOW_RES_SPHERE_MODEL : HIGH_RES_SPHERE_MODEL);

        DrawObject(::g_pDebugSphere,
                   matModelDS,
                   matModel_Location,
                   matModelInverseTranspose_Location,
                   program,
                   ::g_pVAOManager);

        // How far away is 50% brightness?
        float distTo50Percent = ::g_pTheLights->lightHelper.calcApproxDistFromAtten(0.50f,    /* the target light level I want*/
                                                                          0.01f,    /*accuracy - how close to 0.25f*/
                                                                          10000.0f, /*infinity away*/
                                                                          currentLight.atten.x, /*const atten*/
                                                                          currentLight.atten.y, /*linear atten*/
                                                                          currentLight.atten.z, /*quadratic atten*/
                                                                          cLightHelper::DEFAULTMAXITERATIONS);
        // Draw a red sphere at 50%
        ::g_pDebugSphere->scale = distTo50Percent;
        ::g_pDebugSphere->objectDebugColourRGBA = glm::vec4(1.0f, 1.0f, 0.0f, 1.0f);
        ::g_pDebugSphere->meshName = (::g_pDebugSphere->scale < LOW_RES_SPHERE_DISTANCE ? LOW_RES_SPHERE_MODEL : HIGH_RES_SPHERE_MODEL);
        DrawObject(::g_pDebugSphere,
                   matModelDS,
                   matModel_Location,
                   matModelInverseTranspose_Location,
                   program,
                   ::g_pVAOManager);

        // How far away is 25% brightness?
        float distTo25Percent = ::g_pTheLights->lightHelper.calcApproxDistFromAtten(0.25f,    /* the target light level I want*/
                                                                          0.01f,    /*accuracy - how close to 0.25f*/
                                                                          10000.0f, /*infinity away*/
                                                                          currentLight.atten.x, /*const atten*/
                                                                          currentLight.atten.y, /*linear atten*/
                                                                          currentLight.atten.z, /*quadratic atten*/
                                                                          cLightHelper::DEFAULTMAXITERATIONS);
        // Draw a red sphere at 25%
        ::g_pDebugSphere->scale = distTo25Percent;
        ::g_pDebugSphere->objectDebugColourRGBA = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);
        ::g_pDebugSphere->meshName = (::g_pDebugSphere->scale < LOW_RES_SPHERE_DISTANCE ? LOW_RES_SPHERE_MODEL : HIGH_RES_SPHERE_MODEL);
        DrawObject(::g_pDebugSphere,
                   matModelDS,
                   matModel_Location,
                   matModelInverseTranspose_Location,
                   program,
                   ::g_pVAOManager);

        // How far away is 5% brightness?
        float distTo5Percent = ::g_pTheLights->lightHelper.calcApproxDistFromAtten(0.05f,    /* the target light level I want*/
                                                                         0.01f,    /*accuracy - how close to 0.25f*/
                                                                         10000.0f, /*infinity away*/
                                                                         currentLight.atten.x, /*const atten*/
                                                                         currentLight.atten.y, /*linear atten*/
                                                                         currentLight.atten.z, /*quadratic atten*/
                                                                         cLightHelper::DEFAULTMAXITERATIONS);
        // Draw a red sphere at 5%
        ::g_pDebugSphere->scale = distTo5Percent;
        ::g_pDebugSphere->objectDebugColourRGBA = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f);
        ::g_pDebugSphere->meshName = (::g_pDebugSphere->scale < LOW_RES_SPHERE_DISTANCE ? LOW_RES_SPHERE_MODEL : HIGH_RES_SPHERE_MODEL);
        DrawObject(::g_pDebugSphere,
                   matModelDS,
                   matModel_Location,
                   matModelInverseTranspose_Location,
                   program,
                   ::g_pVAOManager);


        ::g_pDebugSphere->meshName = oldDebugSphereModel;

    }//if ( ::g_bShowDebugShere )

    return;
}

