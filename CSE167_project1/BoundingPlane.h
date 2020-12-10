//
//  BoundingPlane.h
//  CSE167_project1
//
//  Created by Matthew Ma on 12/8/20.
//

#ifndef BoundingPlane_h
#define BoundingPlane_h

#include <stdio.h>
#include "shader.h"
#include "Object.h"

class BoundingPlane{
private:

    
public:
    BoundingPlane(glm::vec3 point, glm::vec3 normal);
    //bool notTouching(BoundingPlane * other);
    //BoundingPlane * simTranslate(glm::vec3 translation);
    
    glm::vec3 point;
    glm::vec3 normal;
};

#endif /* BoundingPlane_h */
