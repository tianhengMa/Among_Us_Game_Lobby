//
//  DirecLight.h
//  CSE167_project1
//
//  Created by Matthew Ma on 12/2/20.
//

#ifndef DirecLight_h
#define DirecLight_h

#include <stdio.h>
#include "shader.h"
#include "Object.h"

class DirecLight{
private:
    
    glm::vec3 direction;
      
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
    
public:
    //glm::vec3 pos, color, atten;
    DirecLight(glm::vec3 in_direction, glm::vec3 in_ambient, glm::vec3 in_diffuse, glm::vec3 in_specular);
    void sendLightToShader(const int shaderID);
    //glm::vec3 getPos();
    //glm::vec3 getColor();
    //void setPos(glm::vec3 new_pos);
};

#endif /* DirecLight_h */
