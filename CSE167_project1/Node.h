//
//  Node.hpp
//  CSE167_project1
//
//  Created by Matthew Ma on 11/17/20.
//

#ifndef Node_h
#define Node_h

#ifdef __APPLE__
#include <OpenGL/gl3.h>
#else
#include <GL/glew.h>
#endif


#include "PointLight.h"
#include "Materials.h"
#include "DirecLight.h"
#include "BoundingSphere.h"
#include "BoundingPlane.h"

#include <iostream>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <sstream>

class Node{
public:
    virtual void draw(GLuint shader, glm::mat4 C, bool isRoot, glm::mat4 view, glm::mat4 projection) = 0;
    virtual void update(glm::mat4 C) = 0;
};
#endif

