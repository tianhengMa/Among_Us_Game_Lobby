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
    //glfwGetTime();
    std::cout << "Updating particle ";
    life -= deltaTime;
    //if (life > 0){
        //glm::vec3 velocity = glm::vec3(rand()/RAND_MAX);
        //position = glm::vec3(glm::translate(glm::mat4(1.0f), velocity) * glm::vec4(position ,1.0f));
        position += deltaTime*velocity;
    //} else {
        //position = glm::vec3 (1000,1000,1000);
    //}
    std::cout << " life is " << life << " position is " << glm::to_string(position) << endl;
    
    return position;
}
