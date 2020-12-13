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
    
    static const int MAX_PARTICLES = 100;
    static const int PARTICLE_LIFE = 3;
    
    GLuint VAO, VBO;
    
    glm::vec3 color;
    bool disappear;
    
    std::vector<Particle * > particles;
    std::vector<glm::vec3> position_data;

public:
    ParticleSystem(glm::vec3 origin, bool disappear, float life);
    ~ParticleSystem();
    
    glm::mat4 model;
    float life;
    void update(float deltaTime, glm::vec3 origin);
    void draw(const glm::mat4& view, const glm::mat4& projection, GLuint shader);
};
#endif /* ParticleSystem_h */
