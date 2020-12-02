#include "Window.h"
using namespace std;

// Window Properties
int Window::width;
int Window::height;
const char* Window::windowTitle = "GLFW Starter Project";

// Objects to Render
Cube * Window::cube;
Object* currObj;
Sphere* Window::discoBall;
PointLight * Window::pointLight;

//Scene graph components
Transform * Window::world;
Transform * Window::astrnt_rd2world;
/*
Transform * Window::leg2world;
Transform * Window::support2world;
Transform * Window::wheel2support;
Transform * Window::astrnt_rd2world;
 */

Geometry * Window::lobby;
Geometry * Window::astrnt_rd;
/*
Geometry * Window::leg;
Geometry * Window::support;
Geometry * Window::seat;
 */

float Window::eyePosX = 0;
float Window::eyePosY = 0;
float Window::eyePosZ = 20;

float Window::lookAtX = 0;
float Window::lookAtY = 0;
float Window::lookAtZ = 0;

// Animation switch
bool Window::supportSwitch = false;
bool Window::wheelSwitch= false;
bool Window::seatSwitch = false;

// Camera Matrices
// Projection matrix:
glm::mat4 Window::projection;

// Mouse position for track ball
bool Window::mousePressed;
double Window::startPosX;
double Window::startPosY;

// View Matrix:
glm::vec3 Window::eyePos(eyePosX, eyePosY, eyePosZ);            // Camera position.
glm::vec3 Window::lookAtPoint(lookAtX, lookAtY, lookAtZ);        // The point we are looking at.
glm::vec3 Window::upVector(0, 1, 0);        // The up direction of the camera.
glm::mat4 Window::view = glm::lookAt(Window::eyePos, Window::lookAtPoint, Window::upVector);

// Shader Program ID
GLuint Window::discoBallShader;
GLuint Window::skyboxShader;
GLuint Window::geometryShader;

float Window::nob = 0;

bool Window::initializeProgram() {
    // Create a shader program with a vertex shader and a fragment shader.
    skyboxShader = LoadShaders("shaders/skybox.vert", "shaders/skybox.frag");
    discoBallShader = LoadShaders("shaders/shader.vert", "shaders/shader.frag");
    geometryShader = LoadShaders("shaders/geometry.vert", "shaders/geometry.frag");
    
    // Check the shader program.
    if (!skyboxShader)
    {
        std::cerr << "Failed to initialize shader program" << std::endl;
        return false;
    }
    
    if (!discoBallShader)
    {
        std::cerr << "Failed to initialize shader program" << std::endl;
        return false;
    }

    return true;
}

bool Window::initializeObjects()
{
    // Create pointLight
    glm::vec3 lightPos = glm::vec3(50,50,0);
    glm::vec3 color = glm::vec3(1, 1, 1);
    glm::vec3 atten = glm::vec3(0.1);
    pointLight = new PointLight(lightPos, color, atten);
    
    //cube = new Cube(5.0f);
    //discoBall = new Sphere();
        
    // Scene graphs
    
    // Initialize world transform
    glm::mat4 worldModel = glm::mat4(1.0f);
    worldModel = glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(1,0,0))*worldModel;
    //worldModel = glm::scale(glm::mat4(1.0f), glm::vec3(2))*worldModel;
    //worldModel = glm::translate(glm::mat4(1.0f), glm::vec3(0,-5,0))*worldModel;
    world = new Transform(worldModel);
    
    /* //brass
    glm::vec3 ambient = glm::vec3(0.329412,    0.223529,    0.027451);
    glm::vec3 diffuse = glm::vec3(0.780392,    0.568627,    0.113725);
    glm::vec3 specular = glm::vec3(0.992157,    0.941176,    0.807843);
    float shininess = 0.21794872;
     */
    
    glm::vec3 ambient = glm::vec3(0.25,    0.20725,    0.20725);
    glm::vec3 diffuse = glm::vec3(1,    0.829,    0.829);
    glm::vec3 specular = glm::vec3(0.296648,    0.296648,    0.296648);
    float shininess = 0.088;
    Materials * silver = new Materials(ambient,diffuse,specular,shininess);
    lobby = new Geometry("/Users/tma2017/Senior/Q1/CSE167/project/CSE167_project1/CSE167_project1/amongus_lobby.obj",silver, pointLight,true);
    
    glm::mat4 astrnt_rdModel = glm::mat4(1.0f);
    astrnt_rdModel = glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(1,0,0))*astrnt_rdModel;
    //astrnt_rdModel = glm::scale(glm::mat4(1.0f), glm::vec3(2))*astrnt_rdModel;
    //astrnt_rdModel = glm::translate(glm::mat4(1.0f), glm::vec3(0,-5,0))*astrnt_rdModel;
    
    ambient = glm::vec3(0.25,    0.20725,    0.20725);
    diffuse = glm::vec3(1,    0.829,    0.829);
    specular = glm::vec3(0.296648,    0.296648,    0.296648);
    shininess = 0.088;
    Materials * red = new Materials(ambient,diffuse,specular,shininess);
    astrnt_rd = new Geometry("/Users/tma2017/Senior/Q1/CSE167/project/CSE167_project1/CSE167_project1/amongus_lobby.obj",red, pointLight,false);
    
    
    // Assign Children
    // level 1
    world->addChild(lobby);
    
    // Set cube to be the first to display
    //currObj = cube;

    return true;
}

void Window::cleanUp()
{
    // Deallcoate the objects.
    delete cube;
    //delete cubePoints;

    // Delete the shader program.
    glDeleteProgram(skyboxShader);
    glDeleteProgram(discoBallShader);
}

GLFWwindow* Window::createWindow(int width, int height)
{
    // Initialize GLFW.
    if (!glfwInit())
    {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return NULL;
    }

    // 4x antialiasing.
    glfwWindowHint(GLFW_SAMPLES, 4);

#ifdef __APPLE__
    // Apple implements its own version of OpenGL and requires special treatments
    // to make it uses modern OpenGL.

    // Ensure that minimum OpenGL version is 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    // Enable forward compatibility and allow a modern OpenGL context
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // Create the GLFW window.
    GLFWwindow* window = glfwCreateWindow(width, height, windowTitle, NULL, NULL);

    // Check if the window could not be created.
    if (!window)
    {
        std::cerr << "Failed to open GLFW window." << std::endl;
        glfwTerminate();
        return NULL;
    }

    // Make the context of the window.
    glfwMakeContextCurrent(window);

#ifndef __APPLE__
    // On Windows and Linux, we need GLEW to provide modern OpenGL functionality.

    // Initialize GLEW.
    if (glewInit())
    {
        std::cerr << "Failed to initialize GLEW" << std::endl;
        return NULL;
    }
#endif

    // Set swap interval to 1.
    glfwSwapInterval(0);

    // Call the resize callback to make sure things get drawn immediately.
    Window::resizeCallback(window, width, height);

    return window;
}

void Window::resizeCallback(GLFWwindow* window, int width, int height)
{
#ifdef __APPLE__
    // In case your Mac has a retina display.
    glfwGetFramebufferSize(window, &width, &height);
#endif
    Window::width = width;
    Window::height = height;
    // Set the viewport size.
    glViewport(0, 0, width, height);

    // Set the projection matrix.
    Window::projection = glm::perspective(glm::radians(60.0),
                                double(width) / (double)height, 1.0, 1000.0);
}

void Window::idleCallback()
{
    // Perform any necessary updates here
    //currObj->update();
}

void Window::displayCallback(GLFWwindow* window)
{
    // Clear the color and depth buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    // Render the objects
    //currObj->draw(view, projection, skyboxShader);
    
    //unsigned int skyboxTexture = ((Cube*)currObj)->getSkyboxTexture();
    //discoBall->draw(view, projection, discoBallShader, skyboxTexture);
    
    // Render the scene graph
    world->draw(geometryShader, glm::mat4(1.0f), true, view, projection);
    
    /*
    glm::mat4 hRotate = glm::rotate(glm::radians(0.2f), glm::vec3(0,0,1));
    glm::mat4 vRotate = glm::rotate(glm::radians(0.2f), glm::vec3(1,0,0));
    glm::mat4 sRotate = glm::rotate(glm::radians(0.2f), glm::vec3(0,1,0));
    
    if (supportSwitch){
        support2world->update(hRotate);
    }
    if (wheelSwitch){
        wheel2support->update(vRotate);
    }
    if (seatSwitch){
        seat2wheel->update(sRotate);
    }*/
    
    // Gets events, including input such as keyboard and mouse or window resizing
    glfwPollEvents();

    // Swap buffers.
    glfwSwapBuffers(window);
}

void Window::mouse_button_callback(GLFWwindow* window, int button, int action, int mods){
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS){
        mousePressed = true;
        glfwGetCursorPos(window, &startPosX, &startPosY);
    }
    
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE){
        mousePressed = false;
    }
}

void Window::cursor_position_callback(GLFWwindow* window, double xpos, double ypos){
    if (!mousePressed){
        return;
    }
    
    glm::vec3 startPoint = trackBallMapping(startPosX, startPosY);
    glm::vec3 nextPoint = trackBallMapping(xpos, ypos);
    
    //cout << "start point is (" << startPosX << ", " << startPosY  << ") " << endl;
    //cout << "next point is (" << xpos << ", " << ypos << ") " << endl;
    //cout << endl;

    glm::vec3 direction = nextPoint - startPoint;
    float velocity = glm::length(direction);
    
    // if cursor movement is very little, do nothing
    if (velocity < 0.001){
        return;
    }
    
    glm::vec3 rotAxis = glm::cross(startPoint, nextPoint);
    float rotAngle = velocity * 1;
    
    //view = glm::rotate(glm::mat4(1.0f), -rotAngle, rotAxis) * view;
    eyePos = glm::vec3(glm::rotate(glm::mat4(1.0f), -rotAngle, rotAxis) * glm::vec4(eyePos,1.0f));
    //view = glm::lookAt(Window::eyePos, Window::lookAtPoint, Window::upVector);
    
    //lookAtPoint = glm::vec3(glm::translate(glm::mat4(1.0f), -eyePos) * glm::vec4(lookAtPoint,1.0f));
    //lookAtPoint = glm::rotate(lookAtPoint, rotAngle, rotAxis);
    //lookAtPoint = glm::vec3(glm::translate(glm::mat4(1.0f), eyePos) * glm::vec4(lookAtPoint,1.0f));
    //cout << "LookAt point after is " << glm::to_string(lookAtPoint) << endl;
    view = glm::lookAt(Window::eyePos, Window::lookAtPoint, Window::upVector);
    
    /*
    lookAtPoint = glm::vec3(glm::translate(glm::mat4(1.0f), eyePos) * glm::vec4(lookAtPoint,1.0f));
    lookAtPoint = glm::vec3(glm::rotate(glm::mat4(1.0f), -rotAngle, rotAxis) * glm::vec4(lookAtPoint,1.0f));
    lookAtPoint = glm::vec3(glm::translate(glm::mat4(1.0f), -eyePos) * glm::vec4(lookAtPoint,1.0f));
    view = glm::lookAt(Window::eyePos, Window::lookAtPoint, Window::upVector);
    */
    //leftLeg->ballRotate(rotAxis, -rotAngle);
    //wheel->ballRotate(rotAxis, -rotAngle);
    
    
    startPosX = xpos;
    startPosY = ypos;
}

glm::vec3 Window::trackBallMapping(double pointX, double pointY){
    glm::vec3 vec;
    float d;
    
    vec.x = (2.0*pointX - width) / width;
    vec.y = (height - 2.0*pointY) / height;
    vec.z = 0.0;
    
    d = glm::length(vec);
    d = (d<1.0) ? d:1.0;
    vec.z = sqrtf(1.001 - d*d);
    vec = glm::normalize(vec);
    
    return vec;
}


void Window::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    /*
     * TODO: Modify below to add your key callbacks.
     */
    float larger = 0.5f;
    float smaller = -0.5f;
    // Check for a key press.
    if (action == GLFW_PRESS)
    {
        switch (key)
        {
            case GLFW_KEY_ESCAPE:
                // Close the window. This causes the program to also terminate.
                glfwSetWindowShouldClose(window, GL_TRUE);
                break;
            
            // Toggle animation of different layers
            case GLFW_KEY_1:
                supportSwitch = !supportSwitch;
                break;
            case GLFW_KEY_2:
                wheelSwitch = !wheelSwitch;
                break;
            case GLFW_KEY_3:
                seatSwitch = !seatSwitch;
                break;
                
            // Adjust viewing position
            // Move Up
            case GLFW_KEY_UP:
                eyePosY++;
                lookAtY++;
                eyePos = glm::vec3(eyePosX, eyePosY, eyePosZ);
                lookAtPoint = glm::vec3(lookAtX, lookAtY, lookAtZ);
                view = glm::lookAt(Window::eyePos, Window::lookAtPoint, Window::upVector);
                break;
            // Move Down
            case GLFW_KEY_DOWN:
                eyePosY--;
                lookAtY--;
                eyePos = glm::vec3(eyePosX, eyePosY, eyePosZ);
                lookAtPoint = glm::vec3(lookAtX, lookAtY, lookAtZ);
                view = glm::lookAt(Window::eyePos, Window::lookAtPoint, Window::upVector);
                break;
            // Move Left
            case GLFW_KEY_LEFT:
                eyePosX--;
                lookAtX--;
                eyePos = glm::vec3(eyePosX, eyePosY, eyePosZ);
                lookAtPoint = glm::vec3(lookAtX, lookAtY, lookAtZ);
                view = glm::lookAt(Window::eyePos, Window::lookAtPoint, Window::upVector);
                break;
            // Move Left
            case GLFW_KEY_RIGHT:
                eyePosX++;
                lookAtX++;
                eyePos = glm::vec3(eyePosX, eyePosY, eyePosZ);
                lookAtPoint = glm::vec3(lookAtX, lookAtY, lookAtZ);
                view = glm::lookAt(Window::eyePos, Window::lookAtPoint, Window::upVector);
                break;
            // Move In
            case GLFW_KEY_W:
                eyePosZ--;
                lookAtZ--;
                eyePos = glm::vec3(eyePosX, eyePosY, eyePosZ);
                lookAtPoint = glm::vec3(lookAtX, lookAtY, lookAtZ);
                view = glm::lookAt(Window::eyePos, Window::lookAtPoint, Window::upVector);
                break;
            // Move Out
            case GLFW_KEY_S:
                eyePosZ++;
                lookAtZ++;
                eyePos = glm::vec3(eyePosX, eyePosY, eyePosZ);
                lookAtPoint = glm::vec3(lookAtX, lookAtY, lookAtZ);
                view = glm::lookAt(Window::eyePos, Window::lookAtPoint, Window::upVector);
                break;
            // Rotate Left
            case GLFW_KEY_A:
                //cout << "LookAt point before is " << glm::to_string(lookAtPoint) << endl;
                lookAtPoint = glm::vec3(glm::translate(glm::mat4(1.0f), -eyePos) * glm::vec4(lookAtPoint,1.0f));
                lookAtPoint = glm::rotate(lookAtPoint, glm::radians(5.0f), glm::vec3(0,1,0));
                lookAtPoint = glm::vec3(glm::translate(glm::mat4(1.0f), eyePos) * glm::vec4(lookAtPoint,1.0f));
                //cout << "LookAt point after is " << glm::to_string(lookAtPoint) << endl;
                view = glm::lookAt(Window::eyePos, Window::lookAtPoint, Window::upVector);
                break;
            // Rotate Right
            case GLFW_KEY_D:
                //cout << "LookAt point is " << glm::to_string(lookAtPoint) << endl;
                lookAtPoint = glm::vec3(glm::translate(glm::mat4(1.0f), -eyePos) * glm::vec4(lookAtPoint,1.0f));
                lookAtPoint = glm::rotate(lookAtPoint, -glm::radians(5.0f), glm::vec3(0,1,0));
                lookAtPoint = glm::vec3(glm::translate(glm::mat4(1.0f), eyePos) * glm::vec4(lookAtPoint,1.0f));
                view = glm::lookAt(Window::eyePos, Window::lookAtPoint, Window::upVector);
                break;
                
                
            default:
                break;
        }
    }
}
