//
//  BoundingPlane.cpp
//  CSE167_project1
//
//  Created by Matthew Ma on 12/8/20.
//

#include "BoundingPlane.h"
BoundingPlane::BoundingPlane(glm::vec3 point, glm::vec3 normal){
    this->point = point;
    this->normal = normal;
}
