//
//  BoundingSphere.cpp
//  CSE167_project1
//
//  Created by Matthew Ma on 12/5/20.
//

#include "BoundingSphere.h"
BoundingSphere::BoundingSphere(glm::vec3 center, float radius){
    this->center = center;
    this->radius = radius;
    index = -1;
}

bool BoundingSphere::notTouching(BoundingObj * obj, int type){
    // If type is bounding sphere
    if (type == 0){
        float dist = glm::distance(center, ((BoundingSphere*)obj)->center);
        return (dist > (radius + ((BoundingSphere*)obj)->radius));
    }
    // If type is bounding plane
    else {
        // distance from sphere to plane = dot((center-point),normal)
        glm::vec3 diff = center - ((BoundingPlane*)obj)->point;
        float dist = glm::dot(diff, ((BoundingPlane*)obj)->normal);
        return (dist > radius);
    }
    return true;
}

/*
bool BoundingSphere::notTouching(BoundingPlane * plane){
    // distance from sphere to plane = dot((center-point),normal)
    glm::vec3 diff = center - plane->point;
    float dist = glm::dot(diff, plane->normal);
    return (dist > radius);
}*/

BoundingSphere * BoundingSphere::simTranslate(glm::vec3 translation){
    glm::vec3 new_center = glm::vec3(glm::translate(glm::mat4(1.0f), translation) * glm::vec4(center ,1.0f));
    return new BoundingSphere(new_center,radius);
}
