//
//  Particle.hpp
//  CSE167_project1
//
//  Created by Matthew Ma on 12/10/20.
//

#ifndef Particle_h
#define Particle_h

#include <stdio.h>
#include "shader.h"
#include "Object.h"
#include <cstdlib>
#include <glm/gtx/string_cast.hpp>

class Particle {
private:
    
    glm::vec3 position, velocity;
    float life;

public:
    Particle(glm::vec3 position, glm::vec3 velocity, int life);
    glm::vec3 update(float deltaTime);
};

#endif /* Particle_h */
