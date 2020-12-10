//
//  ParticleSystem.h
//  CSE167_project1
//
//  Created by Matthew Ma on 12/9/20.
//

#ifndef ParticleSystem_h
#define ParticleSystem_h

#include <stdio.h>
#include "shader.h"
#include "Object.h"
#include "Particle.h"
#include <cstdlib>
#include <glm/gtx/string_cast.hpp>

class ParticleSystem {
private:
    
    static const int MAX_PARTICLES = 1;
    static const int PARTICLE_LIFE = 10;
    
    GLuint VAO, VBO;
    
    glm::vec3 color;
    glm::mat4 model;
    
    Particle * particles[MAX_PARTICLES];
    std::vector<glm::vec3> position_data;

public:
    ParticleSystem(glm::vec3 origin);
    ~ParticleSystem();
    
    void update(float deltaTime);
    void draw(const glm::mat4& view, const glm::mat4& projection, GLuint shader);
};
#endif /* ParticleSystem_h */
