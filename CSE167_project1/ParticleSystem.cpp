//
//  ParticleSystem.cpp
//  CSE167_project1
//
//  Created by Matthew Ma on 12/9/20.
//

#include "ParticleSystem.h"
using namespace std;

ParticleSystem::ParticleSystem(glm::vec3 origin, bool disappear, float life){
    for (int i = 0; i < MAX_PARTICLES; i++){
        float x = (float)rand()/RAND_MAX;
        float y = (float)rand()/RAND_MAX;
        float z = (float)rand()/RAND_MAX;
        glm::vec3 velocity = glm::vec3(x,y,z);
        glm::vec3 position = origin;
        particles.push_back(new Particle(position,velocity, PARTICLE_LIFE));
        position_data.push_back(position);
    }
    
    // Set the model matrix to an identity matrix.
    model = glm::mat4(1);
    
    this->disappear = disappear;
    this->life = life;
    
    // Set the color.
    color = glm::vec3(1, 0, 0);
    if (disappear){
        color = glm::vec3(1, 0, 0);
    }

    // Generate a Vertex Array (VAO) and Vertex Buffer Object (VBO)
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    // Bind VAO
    glBindVertexArray(VAO);

    // Bind VBO to the bound VAO, and store the point data
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * position_data.size(), position_data.data(), GL_STATIC_DRAW);
    // Enable Vertex Attribute 0 to pass point data through to the shader
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);

    // Unbind the VBO/VAO
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

ParticleSystem::~ParticleSystem(){
    // Delete the VBO and the VAO.
    glDeleteBuffers(1, &VBO);
    glDeleteVertexArrays(1, &VAO);
}

void ParticleSystem::update(float deltaTime, glm::vec3 origin){
    // Update particle position
    if (!disappear){
        for (int i = 0; i < MAX_PARTICLES; i++){
            position_data[i] = particles[i]->update(deltaTime);
        }
        
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(glm::vec3) * position_data.size(), position_data.data());
        // Unbind the VBO
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    } else {
        life -= deltaTime;
        cout << "vanish PS life is " << life << endl;
        if (life < 0){
            cout << "vanish PS life goes below zero!!!" << endl;
            particles.clear();
            position_data.clear();
            
            for (int i = 0; i < MAX_PARTICLES; i++){
                float x = (float)rand()/RAND_MAX;
                float y = (float)rand()/RAND_MAX;
                float z = (float)rand()/RAND_MAX;
                glm::vec3 velocity = glm::vec3(x,y,z);
                glm::vec3 position = origin;
                cout << "vanish particle position is " << glm::to_string(position) << endl;
                Particle * vanishParticle =new Particle(position,velocity, PARTICLE_LIFE);
                particles.push_back(vanishParticle);
                position_data.push_back(position);
            }
            for (int i = 0; i < MAX_PARTICLES; i++){
                position_data[i] = particles[i]->update(deltaTime);
            }
            
            glBindBuffer(GL_ARRAY_BUFFER, VBO);
            glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(glm::vec3) * position_data.size(), position_data.data());
            // Unbind the VBO
            glBindBuffer(GL_ARRAY_BUFFER, 0);
        }
    }
}

void ParticleSystem::draw(const glm::mat4& view, const glm::mat4& projection, GLuint shader){
    if (disappear){
        cout << "drawing vanish particle system!!!" << endl;
    }
    
    // Actiavte the shader program
    glUseProgram(shader);

    // Get the shader variable locations and send the uniform data to the shader
    glUniformMatrix4fv(glGetUniformLocation(shader, "view"), 1, false, glm::value_ptr(view));
    glUniformMatrix4fv(glGetUniformLocation(shader, "projection"), 1, false, glm::value_ptr(projection));
    glUniformMatrix4fv(glGetUniformLocation(shader, "model"), 1, GL_FALSE, glm::value_ptr(model));
    glUniform3fv(glGetUniformLocation(shader, "color"), 1, glm::value_ptr(color));

    // Bind the VAO
    glBindVertexArray(VAO);

    // Set point size
    glPointSize(3.0f);

    // Draw the points
    glDrawArrays(GL_POINTS, 0, position_data.size());

    // Unbind the VAO and shader program
    glBindVertexArray(0);
    glUseProgram(0);
}
