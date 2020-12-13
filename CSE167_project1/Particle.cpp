//
//  Particle.cpp
//  CSE167_project1
//
//  Created by Matthew Ma on 12/10/20.
//

#include "Particle.h"
using namespace std;
Particle::Particle(glm::vec3 position, glm::vec3 velocity, int life){
    this->position = position;
    this->velocity = velocity;
    this->life = life;
}
glm::vec3 Particle::update(float deltaTime){
    //std::cout << "Updating particle ";
    life -= deltaTime;
    if (life > 0){
        // Update position
        position += 10*deltaTime*velocity;
    } else {
        // Move position to somewhere viewer can't see
        position = glm::vec3 (-10000,-10000,-10000);
    }
    //std::cout << " life is " << life << " position is " << glm::to_string(position) << endl;
    
    return position;
}
