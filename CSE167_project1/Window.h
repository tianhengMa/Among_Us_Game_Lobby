#ifndef _WINDOW_H_
#define _WINDOW_H_

#include "main.h"
#include "shader.h"
#include "Object.h"
#include "Cube.h"
#include "PointCloud.h"
#include "Sphere.h"
#include "PointLight.h"

#include "Transform.h"
#include "Geometry.h"
#include "Node.h"
#include <glm/gtx/string_cast.hpp>
#include <glm/gtx/rotate_vector.hpp>

class Window
{
public:

    // Window Properties
    static int width;
    static int height;
    static const char* windowTitle;

    // Objects to Render
    static Cube* cube;
    static Sphere* discoBall;
    
    // Scene graph components
    static Transform * viewTransform;
    static Transform * projectionTransform;
    static Transform * world;
    static Transform * support2world;
    static Transform * leg2world;
    static Transform * wheel2support;
    static Transform * seat2wheel;
    
    static Geometry * ground;
    static Geometry * wheel;
    static Geometry * support;
    static Geometry * leg;
    static Geometry * seat;
    
    // Animation switch
    static bool supportSwitch;
    static bool wheelSwitch;
    static bool seatSwitch;
    
    // Point light
    static PointLight * pointLight;

    // Camera Matrices
    static glm::mat4 projection;
    static glm::mat4 view;
    static glm::vec3 eyePos, lookAtPoint, upVector;
    static float eyePosX;
    static float eyePosY;
    static float eyePosZ;
    
    static float lookAtX;
    static float lookAtY;
    static float lookAtZ;

    // Shader Program ID
    static GLuint discoBallShader;
    static GLuint skyboxShader;
    static GLuint geometryShader;

    // Constructors and Destructors
    static bool initializeProgram();
    static bool initializeObjects();
    static void cleanUp();
    
    static float nob;

    // Window functions
    static GLFWwindow* createWindow(int width, int height);
    static void resizeCallback(GLFWwindow* window, int width, int height);

    // Draw and Update functions
    static void idleCallback();
    static void displayCallback(GLFWwindow*);

    // Callbacks
    static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
    static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
    static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
    
    // Track Ball
    static glm::vec3 trackBallMapping(double pointX, double pointY);
    
    // Cursor Position when mouse is pressed
    static bool mousePressed;
    static double startPosX;
    static double startPosY;

};

#endif
