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
}

bool BoundingSphere::notTouching(BoundingSphere * other){
    float dist = glm::distance(center, other->center);
    return (dist > (radius + other->radius));
}

bool BoundingSphere::notTouching(BoundingPlane * plane){
    // distance from sphere to plane = dot((center-point),normal)
    glm::vec3 diff = center - plane->point;
    float dist = glm::dot(diff, plane->normal);
    return (dist > radius);
}

BoundingSphere * BoundingSphere::simTranslate(glm::vec3 translation){
    glm::vec3 new_center = glm::vec3(glm::translate(glm::mat4(1.0f), translation) * glm::vec4(center ,1.0f));
    return new BoundingSphere(new_center,radius);
}
