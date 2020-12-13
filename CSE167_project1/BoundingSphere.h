//
//  BoundingSphere.hpp
//  CSE167_project1
//
//  Created by Matthew Ma on 12/5/20.
//

#ifndef BoundingSphere_h
#define BoundingSphere_h

#include <stdio.h>
#include "shader.h"
#include "Object.h"
#include "BoundingPlane.h"
#include "BoundingObj.h"


class BoundingSphere: public BoundingObj{
private:

    
public:
    BoundingSphere(glm::vec3 center, float radius);
    bool notTouching(BoundingObj * obj, int type);
    //bool notTouching(BoundingPlane * plane);
    BoundingSphere * simTranslate(glm::vec3 translation);
    
    glm::vec3 center;
    float radius;
};
#endif /* BoundingSphere_hpp */
